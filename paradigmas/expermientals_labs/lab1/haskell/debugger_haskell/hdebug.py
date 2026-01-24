import curses
import subprocess
import select
import sys
import re
import os
import fcntl
import pty
import time

class HaskellDebuggerUI:
    def __init__(self, stdscr, file_to_debug):
        self.stdscr = stdscr
        # Immediate UI setup to avoid scroll glitch
        curses.curs_set(0) # Hide cursor
        self.stdscr.clear()
        self.stdscr.refresh()
        
        self.file_to_debug = os.path.abspath(file_to_debug)
        self.log_file = "ghci_output.log"
        self.var_file = "ghci_vars.log"
        
        # Clear logs
        for f in [self.log_file, self.var_file]:
            with open(f, "w", encoding='utf-8') as tmp: tmp.write("")

        self.shortcuts = {
            "s": ":step", "n": ":steplocal", "c": ":continue", "f": ":force", "b": ":break", 
            "r": ":reload", "main": "main", "clear": "clear", "help": "help",
            "q": "quit"
        }
        
        # Create PTY
        self.master_fd, self.slave_fd = pty.openpty()
        
        # Disable echo on PTY to avoid seeing commands in output
        import termios
        attrs = termios.tcgetattr(self.master_fd)
        attrs[3] = attrs[3] & ~termios.ECHO
        termios.tcsetattr(self.master_fd, termios.TCSANOW, attrs)

        # Launch GHCi with PTY
        # Added -O0 to ensure optimization doesn't skip steps
        self.process = subprocess.Popen(
            ['ghci', '-O0', '-fno-diagnostics-show-caret', '-fprint-evld-with-show', self.file_to_debug],
            stdin=self.slave_fd, stdout=self.slave_fd, stderr=self.slave_fd,
            text=True, bufsize=0, close_fds=True
        )
        os.close(self.slave_fd) # Close slave in parent

        curses.start_color()
        curses.use_default_colors()
        # Colors: 1=Current Line (White on Blue), 2=Breakpoint (White on Red)
        curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLUE)
        curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_RED)
        
        self.input_buffer = ""
        self.current_line = 1
        self.scroll_top = 0
        self.breakpoints = set() 
        self.file_lines = []
        
        # Layout Calculation
        h, w = self.stdscr.getmaxyx()
        self.code_h = int(h * 0.5)
        self.bottom_h = h - self.code_h - 3 # -3 for prompt
        self.term_w = int(w * 0.5)
        self.var_w = w - self.term_w
        
        # Windows
        self.win_code   = curses.newwin(self.code_h, w, 0, 0)
        self.win_term   = curses.newwin(self.bottom_h, self.term_w, self.code_h, 0)
        self.win_var    = curses.newwin(self.bottom_h, self.var_w, self.code_h, self.term_w)
        self.win_prompt = curses.newwin(3, w, h - 3, 0)
        
        self.stdscr.nodelay(True)
        self.win_prompt.keypad(True)
        
        self.load_file()
        self.init_ghci()

    def init_ghci(self):
        # Set prompt to empty to avoid clutter
        self.execute_command(":set prompt \"\"")
        self.execute_command(":set prompt-cont \"\"")
        # Initial read to clear banner
        self.read_all_available(0.5)

    def load_file(self):
        if os.path.exists(self.file_to_debug):
            with open(self.file_to_debug, 'r', encoding='utf-8') as f:
                self.file_lines = f.readlines()
        else:
            self.file_lines = ["Error: File not found"]

    def read_all_available(self, timeout=0.1):
        full_output = ""
        while True:
            r, _, _ = select.select([self.master_fd], [], [], timeout)
            if not r: break
            try:
                # Read raw bytes from PTY
                chunk = os.read(self.master_fd, 4096).decode('utf-8', errors='ignore')
                if not chunk: break
                full_output += chunk
                timeout = 0.05 
            except OSError:
                break
        return full_output

    def execute_command(self, cmd):
        if self.process.poll() is not None: return "GHCi OFF"
        
        # Send command to PTY
        os.write(self.master_fd, (cmd + "\n").encode('utf-8'))
        
        # Read response
        time.sleep(0.1)
        raw = self.read_all_available(0.3)
        
        # Clean escape codes
        clean = re.sub(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])', '', raw)
        
        # Filter out the command echo if it appears (should be handled by no-echo, but just in case)
        lines = clean.splitlines()
        filtered_lines = []
        for l in lines:
            # Filter prompt lines like [file.hs:1:1] or command echo
            if l.strip() == cmd.strip(): continue
            if l.strip().startswith("[") and l.strip().endswith("]"): continue # GHCi prompt
            filtered_lines.append(l)
        
        clean_output = "\n".join(filtered_lines)

        # Check for position update ONLY if we see "Stopped" or similar
        if any(x in clean_output for x in ["Stopped in", "line", ".hs:"]):
             self.update_position(clean_output)
             
             # If we didn't update (maybe the output was just "Stopped in Main"), ask :where
             # But we need to be careful not to spam :where
             pass

        # Always ask :where if we ran a movement command
        if any(x in cmd for x in [":step", ":steplocal", ":continue", "main", ":back", ":trace"]):
             os.write(self.master_fd, b":where\n")
             time.sleep(0.1)
             extra = self.read_all_available(0.2)
             clean_extra = re.sub(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])', '', extra)
             clean_output += "\n" + clean_extra
             self.update_position(clean_extra)

        return clean_output

    def update_position(self, text):
        # Strict patterns to find current position
        # We want to avoid matching "Breakpoint activated at ... line 6"
        # We look for "Stopped in" OR ":list" output OR ":where" output
        
        # Pattern 1: Stopped in ... at file.hs:Line:Col
        # Pattern 2: file.hs:Line:Col ... (from :where)
        
        # We iterate lines to find the best match
        lines = text.splitlines()
        for line in lines:
            if "Breakpoint" in line and "activated" in line: continue # Ignore activation
            
            # Match: test.hs:6:5-17
            m = re.search(r'(\S+\.hs):(\d+):', line)
            if m:
                try:
                    self.current_line = int(m.group(2))
                    half = (self.code_h - 2) // 2
                    self.scroll_top = max(0, self.current_line - half - 1)
                    return # Found it
                except: pass
            
            # Match: Stopped in ... line 6
            m = re.search(r'line (\d+)', line)
            if m and "Stopped" in line:
                try:
                    self.current_line = int(m.group(1))
                    half = (self.code_h - 2) // 2
                    self.scroll_top = max(0, self.current_line - half - 1)
                    return
                except: pass

    def refresh_ui(self):
        h_ui, w_ui = self.stdscr.getmaxyx()
        
        # --- CODE VIEW ---
        self.win_code.erase()
        self.win_code.border()
        self.win_code.addstr(0, 2, f" CODE VIEW: {os.path.basename(self.file_to_debug)} ", curses.A_REVERSE)
        
        max_lines_display = self.code_h - 2
        for i in range(max_lines_display):
            idx = self.scroll_top + i
            if idx < len(self.file_lines):
                ln = idx + 1
                is_curr = (ln == self.current_line)
                is_break = ln in self.breakpoints
                
                prefix = " -> " if is_curr else (" BB " if is_break else "    ")
                
                # Determine attributes
                attr = curses.A_NORMAL
                if is_curr:
                    attr = curses.color_pair(1) | curses.A_BOLD
                elif is_break:
                    attr = curses.color_pair(2) | curses.A_BOLD
                
                line_content = self.file_lines[idx].rstrip().replace('\t', '    ')
                display_str = f"{prefix}{ln:3} | {line_content}"
                
                # Truncate to fit window width
                display_str = display_str[:w_ui-3]
                
                try:
                    self.win_code.addstr(i+1, 1, display_str, attr)
                    # Fill the rest of the line with the background color if current
                    if is_curr:
                        self.win_code.chgat(i+1, 1, w_ui-2, attr)
                except: pass

        # --- TERMINAL ---
        self.win_term.erase()
        self.win_term.border()
        self.win_term.addstr(0, 2, " TERMINAL (LOGS) ", curses.A_REVERSE)
        
        term_lines = self.read_log(self.log_file)
        max_term_lines = self.bottom_h - 2
        visible_term = term_lines[-max_term_lines:]
        for i, l in enumerate(visible_term):
            try: self.win_term.addstr(i+1, 1, l.strip()[:self.term_w-3])
            except: pass

        # --- VARIABLES ---
        self.win_var.erase()
        self.win_var.border()
        self.win_var.addstr(0, 2, " VARIABLES ", curses.A_REVERSE)
        
        var_lines = self.read_log(self.var_file)
        max_var_lines = self.bottom_h - 2
        visible_var = var_lines[-max_var_lines:]
        for i, l in enumerate(visible_var):
            try: self.win_var.addstr(i+1, 1, l.strip()[:self.var_w-3])
            except: pass

        # --- PROMPT ---
        self.win_prompt.erase()
        self.win_prompt.border()
        self.win_prompt.addstr(1, 2, f"CMD> {self.input_buffer}", curses.A_BOLD)
        
        # Refresh all
        self.win_code.noutrefresh()
        self.win_term.noutrefresh()
        self.win_var.noutrefresh()
        self.win_prompt.noutrefresh()
        curses.doupdate()

    def read_log(self, filename):
        try:
            with open(filename, "r", encoding='utf-8') as f: return f.readlines()
        except: return []

    def show_help(self):
        help_text = [
            "--- HELP MANUAL ---",
            "Available Commands:",
            "  b <line>  : Set Breakpoint",
            "  clear     : Remove ALL breakpoints",
            "  main      : Run main function",
            "  s (or n)  : Step (Next line / Local step)",
            "  c         : Continue",
            "  f <var>   : Force (Inspect variable)",
            "  r         : Reload (Reset and reload file)",
            "  q         : Quit",
            "  F10       : Quick Exit",
            "-------------------"
        ]
        with open(self.log_file, "a", encoding='utf-8') as f:
            for l in help_text: f.write(l + "\n")

    def run(self):
        self.refresh_ui()
        
        while True:
            if self.process.poll() is not None:
                self.input_buffer = "GHCi Process Ended. Press q to quit."
                self.refresh_ui()
                if self.stdscr.getch() == ord('q'): break
                continue

            key = self.stdscr.getch()
            if key == -1:
                curses.napms(50)
                continue
            
            if key == curses.KEY_UP:
                self.scroll_top = max(0, self.scroll_top - 1)
            elif key == curses.KEY_DOWN:
                self.scroll_top = min(len(self.file_lines)-1, self.scroll_top + 1)
            elif key == curses.KEY_PPAGE: # Page Up
                self.scroll_top = max(0, self.scroll_top - 10)
            elif key == curses.KEY_NPAGE: # Page Down
                self.scroll_top = min(len(self.file_lines)-1, self.scroll_top + 10)
            elif key == curses.KEY_F10: # Quick Exit
                break
            elif key in (10, 13): # Enter
                cmd_raw = self.input_buffer.strip()
                if cmd_raw:
                    if cmd_raw.lower() in ("quit", ":q"): break
                    
                    # Handle breakpoints locally for UI
                    if cmd_raw.startswith("b "):
                        try:
                            parts = cmd_raw.split()
                            if len(parts) > 1:
                                self.breakpoints.add(int(parts[1]))
                        except: pass
                    
                    # Expand shortcuts
                    parts = cmd_raw.split()
                    cmd_key = parts[0]
                    
                    # Special commands
                    if cmd_key == "clear":
                        self.breakpoints.clear()
                        self.execute_command(":delete *")
                        with open(self.log_file, "a", encoding='utf-8') as f:
                            f.write("> Breakpoints cleared.\n")
                        self.input_buffer = ""
                        self.refresh_ui()
                        continue
                        
                    if cmd_key == "help":
                        self.show_help()
                        self.input_buffer = ""
                        self.refresh_ui()
                        continue

                    if cmd_key == "r" or cmd_key == ":reload":
                        self.breakpoints.clear()
                        self.current_line = 1
                        self.execute_command(":reload")
                        with open(self.log_file, "a", encoding='utf-8') as f:
                            f.write("> File reloaded. State reset.\n")
                        self.input_buffer = ""
                        self.refresh_ui()
                        continue

                    if cmd_key in self.shortcuts:
                        parts[0] = self.shortcuts[cmd_key]
                    
                    final_cmd = " ".join(parts)
                    
                    # Execute
                    response = self.execute_command(final_cmd)
                    
                    # Filter output
                    # Remove the :where output lines (usually contain line numbers)
                    # But keep useful info.
                    lines = response.splitlines()
                    filtered_lines = []
                    for l in lines:
                        # Simple heuristic to remove prompt/location noise if needed
                        # For now, keep most, just filter empty
                        if l.strip(): filtered_lines.append(l)

                    # Route Output
                    # If command was explicit variable inspection (starts with :force or f)
                    is_var_request = final_cmd.startswith(":force") or (cmd_key == "f")
                    
                    target_file = self.var_file if is_var_request else self.log_file
                    
                    with open(target_file, "a" if not is_var_request else "w", encoding='utf-8') as f:
                        if not is_var_request:
                            f.write(f"> {cmd_raw}\n")
                        for l in filtered_lines:
                            f.write(l + "\n")
                    
                    self.input_buffer = ""
            elif key in (curses.KEY_BACKSPACE, 127, 8):
                self.input_buffer = self.input_buffer[:-1]
            elif 32 <= key <= 126:
                self.input_buffer += chr(key)
            
            self.refresh_ui()

if __name__ == "__main__":
    if len(sys.argv) > 1:
        # Ensure terminal is large enough or handle resize? 
        # Curses wrapper handles basic setup
        os.environ.setdefault('ESCDELAY', '25') # Fix escape key delay
        curses.wrapper(lambda stdscr: HaskellDebuggerUI(stdscr, sys.argv[1]).run())
    else:
        print("Usage: python3 hdebug.py <file.hs>")