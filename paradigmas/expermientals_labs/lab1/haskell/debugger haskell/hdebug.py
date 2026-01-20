import subprocess
import sys
import os
import select
import time
import re

# --- ESTILOS Y COLORES ---
BLUE, GREEN, RED, CYAN, RESET, GRAY, BOLD = '\033[1;44m', '\033[1;42m', '\033[1;41m', '\033[1;36m', '\033[0m', '\033[90m', '\033[1m'

def draw_box(title, content, color, width=90):
    print(f"{color}{BOLD} {title.center(width)} {RESET}")
    print(f"{CYAN}┌" + "─" * (width-2) + "┐" + RESET)
    # Si no hay contenido, mostramos un placeholder elegante
    display_lines = content if content else [" (Sin datos en esta sección) "]
    for line in display_lines:
        # Limpiar caracteres de control y truncar
        clean_line = line.strip()[:width-4]
        print(f"{CYAN}│{RESET} {clean_line:<{width-4}} {CYAN}│{RESET}")
    print(f"{CYAN}└" + "─" * (width-2) + "┘" + RESET)

def run_debugger(filename):
    # Iniciamos GHCi con flags de estabilidad (evita errores de Linker/Maybe)
    proc = subprocess.Popen(
        ['ghci', '-fbyte-code', '-fno-break-on-exception', filename],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
        text=True, bufsize=0
    )

    print(f"{CYAN}Sincronizando con GHCi...{RESET}")
    time.sleep(1.2) # Espera técnica para carga de módulos
    
    # Comandos iniciales de configuración
    proc.stdin.write(":set prompt \"hdebug_sync> \"\n")
    proc.stdin.write(":step main\n") # Iniciamos el flujo inmediatamente
    proc.stdin.flush()

    def get_ghci_data():
        """Pide lista y variables, devuelve el output crudo."""
        proc.stdin.write(":list\n:force\n")
        proc.stdin.flush()
        
        lines = []
        stop_time = time.time() + 0.4
        while time.time() < stop_time:
            if select.select([proc.stdout], [], [], 0.05)[0]:
                line = proc.stdout.readline()
                if "hdebug_sync>" in line: break
                if line.strip(): lines.append(line.strip())
        return lines

    try:
        while True:
            raw_data = get_ghci_data()

            # --- FILTRADO INTELIGENTE ---
            # 1. CODE VIEW: Líneas que empiezan con número (el código fuente)
            code_view = [l for l in raw_data if re.match(r'^\d+\s+', l)]
            
            # 2. VARIABLES: Líneas que contienen '=' pero no son el prompt ni código
            var_view = [l for l in raw_data if "=" in l and not re.match(r'^\d+\s+', l) and "hdebug_sync" not in l]
            
            # 3. OUTPUT/STATUS: Todo lo demás (Errores, resultados de comandos, etc.)
            output_view = [l for l in raw_data if l not in code_view and l not in var_view and "hdebug_sync" not in l]

            # --- DIBUJAR INTERFAZ ---
            os.system('clear')
            
            # Sección de Código (Caja Azul)
            draw_box("CODE VIEW", code_view[:12], BLUE)
            
            # Sección de Variables (Caja Verde)
            if var_view:
                print()
                draw_box("VARIABLES (FORCED)", var_view[-6:], GREEN)
            
            # Sección de Consola / Errores (Caja Roja si hay algo importante)
            if output_view:
                print()
                draw_box("GHCi CONSOLE / STATUS", output_view[-5:], GRAY)

            # --- PROMPT ---
            print(f"\n{BOLD}{CYAN}hdebug (ENTER: step | q: salir | <comando ghci>){RESET}")
            user_input = input(f"{BOLD}>> {RESET}")

            if user_input.lower() == 'q':
                break
            
            # Si es enter vacío enviamos :step, sino enviamos el comando tal cual
            cmd = ":step" if user_input == "" else user_input
            proc.stdin.write(f"{cmd}\n")
            proc.stdin.flush()
            
            # Pequeña pausa si fue un comando manual para que dé tiempo a procesar
            if user_input != "": time.sleep(0.3)
                
    except KeyboardInterrupt:
        pass
    finally:
        print(f"\n{CYAN}Cerrando debugger...{RESET}")
        proc.terminate()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python3 hview.py archivo.hs")
    else:
        run_debugger(sys.argv[1])