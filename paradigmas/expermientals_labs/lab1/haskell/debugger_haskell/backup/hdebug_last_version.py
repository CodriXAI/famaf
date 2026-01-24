import curses
import subprocess
import select
import sys
import re
import os

class HaskellDebuggerUI:
    def __init__(self, stdscr, file_to_debug):
        self.stdscr = stdscr
        self.file_to_debug = file_to_debug
        self.log_file = "ghci_output.log"
        self.var_file = "ghci_vars.log"
        self.START_MARK = "---BEGIN---"
        self.END_MARK = "---END---"

        # Limpiar logs
        for f in [self.log_file, self.var_file]:
            with open(f, "w") as tmp: tmp.write("")

        self.shortcuts = {"s": ":step", "c": ":continue", "f": ":force", "b": ":break", "r": ":reload", "main": "main"}

        self.process = subprocess.Popen(
            ['ghci', '-fprint-evld-with-show', file_to_debug],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, bufsize=0
        )

        curses.use_default_colors()
        curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_CYAN) # Línea Ejecución
        curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)   # Breakpoints
        
        h, w = stdscr.getmaxyx()
        code_h = h // 2
        events_h = h // 4
        vals_h = h - code_h - events_h - 3
        
        self.win_code   = curses.newwin(code_h, w, 0, 0)
        self.win_term   = curses.newwin(events_h, w, code_h, 0)
        self.win_var    = curses.newwin(vals_h, w, code_h + events_h, 0)
        self.win_prompt = curses.newwin(3, w, h - 3, 0)
        self.stdscr.nodelay(True)
        
        self.input_buffer = ""
        self.current_line = -1
        self.breakpoints = {} 
        self.file_lines = []
        self.load_file()
        self.init_ghci()

    def init_ghci(self):
        self.process.stdin.write(":set width 1000\n:set prompt \"\"\n")
        self.process.stdin.flush()
        select.select([self.process.stdout], [], [], 0.5)

    def load_file(self):
        try:
            with open(self.file_to_debug, 'r', encoding='utf-8') as f:
                self.file_lines = f.readlines()
        except: self.file_lines = ["Error leyendo archivo."]

    def get_ghci_response(self):
        full_res = ""
        while True:
            r, _, _ = select.select([self.process.stdout], [], [], 0.3)
            if r:
                chunk = self.process.stdout.read(1)
                if not chunk: break
                full_res += chunk
                if self.END_MARK in full_res: break
            else: break
        return full_res

    def extract_clean_content(self, raw_text):
        pattern = f"{self.START_MARK}(.*?){self.END_MARK}"
        match = re.search(pattern, raw_text, re.DOTALL)
        if match:
            lines = match.group(1).strip().splitlines()
            return [l.strip() for l in lines if l.strip() and self.START_MARK not in l]
        return []

    def update_status(self, raw_text):
        """Busca patrones de ubicación como 'test.hs:5:1' o 'line 5'."""
        match = re.search(r':(\d+):\d+', raw_text)
        if not match: match = re.search(r'line (\d+)', raw_text)
        if match:
            self.current_line = int(match.group(1))

    def refresh_ui(self):
        h_ui, w_ui = self.stdscr.getmaxyx()
        for w in [self.win_code, self.win_term, self.win_var]:
            w.erase()
            w.border()
        
        # CODE VIEW
        self.win_code.addstr(0, 2, " CODE VIEW ", curses.A_REVERSE)
        max_c_lines = self.win_code.getmaxyx()[0] - 2
        start_idx = max(0, self.current_line - (max_c_lines // 2))
        for i, line in enumerate(self.file_lines[start_idx:], start=start_idx):
            ln = i + 1
            if (i - start_idx) < max_c_lines:
                is_curr = (ln == self.current_line)
                is_break = ln in self.breakpoints
                prefix = "---> " if is_curr else (" [B] " if is_break else "     ")
                attr = curses.color_pair(1) if is_curr else (curses.color_pair(2) if is_break else 0)
                self.win_code.addstr(i - start_idx + 1, 2, f"{prefix}{ln:3} | {line.rstrip()}"[:w_ui-5], attr)

        # EVENTOS
        self.win_term.addstr(0, 2, " BITÁCORA DE EJECUCIÓN ", curses.A_REVERSE)
        logs = self.read_log(self.log_file)
        for i, l in enumerate(logs[-(self.win_term.getmaxyx()[0]-2):]):
            self.win_term.addstr(i+1, 2, f" {l.strip()}"[:w_ui-4])

        # VALORES
        self.win_var.addstr(0, 2, " INSPECCIÓN ", curses.A_REVERSE)
        vars_l = self.read_log(self.var_file)
        for i, l in enumerate(vars_l):
            if i + 1 < self.win_var.getmaxyx()[0] - 1:
                self.win_var.addstr(i+1, 2, f" » {l.strip()}"[:w_ui-4])

        self.win_prompt.erase()
        self.win_prompt.border()
        self.win_prompt.addstr(1, 2, f" COMMAND> {self.input_buffer}", curses.A_BOLD)
        
        for w in [self.win_code, self.win_term, self.win_var, self.win_prompt]:
            w.noutrefresh()
        curses.doupdate()

    def read_log(self, filename):
        if not os.path.exists(filename): return []
        with open(filename, "r", encoding='utf-8') as f: return f.readlines()

    def run(self):
        while True:
            self.refresh_ui()
            key = self.stdscr.getch()
            if key == -1: continue

            if key in (10, 13):
                cmd_raw = self.input_buffer.strip()
                if not cmd_raw: continue
                if cmd_raw.lower() in ("quit", ":q"): break
                
                is_inspect = any(x in cmd_raw for x in ["f ", "t ", ":force", ":type", ":print"])
                parts = cmd_raw.split()
                orig_cmd = parts[0]
                if parts[0] in self.shortcuts: parts[0] = self.shortcuts[parts[0]]
                final_cmd = " ".join(parts)

                # Envío de comando con centinelas
                full_cmd = f'putStrLn "{self.START_MARK}"\n{final_cmd}\nputStrLn "{self.END_MARK}"\n'
                self.process.stdin.write(full_cmd)
                self.process.stdin.flush()
                
                raw = self.get_ghci_response()
                self.update_status(raw)
                clean_lines = self.extract_clean_content(raw)
                
                # --- LÓGICA DE BITÁCORA INTELIGENTE ---
                event_msg = None
                if final_cmd.startswith(":break"):
                    b_match = re.search(r'line (\d+)', raw)
                    if b_match:
                        line_num = int(b_match.group(1))
                        self.breakpoints[line_num] = True
                        event_msg = f"[BREAK] Punto de interrupción fijado en línea {line_num}"
                elif final_cmd == ":step" or orig_cmd == "s":
                    event_msg = f"[STEP] Avanzando a línea {self.current_line}..."
                elif final_cmd == ":continue" or orig_cmd == "c":
                    event_msg = f"[CONT] Buscando siguiente breakpoint... (Llegó a: {self.current_line})"
                elif not clean_lines:
                    event_msg = f"[OK] Ejecutado: {final_cmd}"

                # Guardar en logs
                target = self.var_file if is_inspect else self.log_file
                mode = "w" if is_inspect else "a"
                with open(target, mode, encoding='utf-8') as f:
                    if event_msg: f.write(event_msg + "\n")
                    for line in clean_lines: f.write(line + "\n")
                
                self.input_buffer = ""
            elif key in (curses.KEY_BACKSPACE, 127, 8):
                self.input_buffer = self.input_buffer[:-1]
            elif 32 <= key <= 126:
                self.input_buffer += chr(key)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        curses.wrapper(lambda stdscr: HaskellDebuggerUI(stdscr, sys.argv[1]).run())