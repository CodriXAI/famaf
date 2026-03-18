# HDebug: Visual Haskell Debugger (v0.1 Beta) **Autor:** CodriXAI ## 📋 Descripción del Proyecto HDebug es una herramienta de depuración visual para programas escritos en **Haskell**.  Su objetivo es proporcionar una interfaz amigable en terminal (TUI) que permita ejecutar código paso a paso, visualizar el código fuente con resaltado de sintaxis básico, inspeccionar variables y gestionar puntos de interrupción (breakpoints), todo ello aprovechando la potencia de GHCi en segundo plano.  Este proyecto actúa como un "wrapper" o envoltorio gráfico sobre el intérprete estándar de Haskell (GHCi), facilitando el aprendizaje y la depuración sin necesidad de memorizar comandos complejos.  ## 🚀 Tecnologías Utilizadas Este proyecto ha sido desarrollado utilizando tecnologías estándar de Python y Linux, sin dependencias externas pesadas: *   **Python 3**: Lenguaje principal de la aplicación.  *   **Curses**: Librería estándar para la creación de interfaces de usuario en terminal (TUI). Maneja ventanas, colores y eventos de teclado.  *   **PTY (Pseudo-Terminal Utilities)**: Permite lanzar GHCi en un entorno controlado, simulando una terminal real para capturar su salida y enviarle comandos.  *   **Subprocess**: Para la gestión del proceso hijo de GHCi.  *   **GHCi**: El intérprete interactivo de Glasgow Haskell Compiler, que realiza la ejecución real del código.  ## 📂 Estructura del Proyecto El proyecto se mantiene simple y directo: ```text .  ├── hdebug.py          # Código fuente principal del depurador (Python) ├── test.hs            # Archivo de ejemplo en Haskell para probar la herramienta ├── ghci_output.log    # (Generado) Historial de salida de la terminal ├── ghci_vars.log      # (Generado) Historial de inspección de variables └── README.md          # Este archivo de documentación ```

## ⚙️ Cómo Funciona
1.  **Inicialización**: HDebug lanza una instancia oculta de `ghci`.
2.  **Interfaz**: Se divide la pantalla en tres secciones:
    *   **Code View**: Muestra el código fuente, resaltando la línea actual y los breakpoints.
    *   **Terminal (Logs)**: Muestra la salida del programa y mensajes del sistema.
    *   **Variables**: Muestra el resultado de inspecciones de variables.
3.  **Interacción**: Al pulsar teclas o ingresar comandos, Python traduce estas acciones a comandos de GHCi (ej. `s` -> `:step`), los envía al proceso oculto, y procesa la respuesta para actualizar la interfaz gráfica.

## 📖 Guía de Uso Paso a Paso

### 1. Requisitos Previos
Asegúrate de tener instalado en tu sistema Linux:
*   Python 3
*   GHC (Glasgow Haskell Compiler) que incluye `ghci`.

```bash
sudo apt install python3 ghc
```

### 2. Ejecución
Para iniciar el depurador con un archivo Haskell (por ejemplo, `test.hs`):

```bash
python3 hdebug.py test.hs
```

### 3. Comandos Disponibles
Una vez dentro de la interfaz, puedes usar los siguientes atajos de teclado o comandos en el prompt `CMD>`:

| Tecla / Comando | Acción | Descripción |
| :--- | :--- | :--- |
| **s** o **n** | Step | Ejecuta la siguiente línea de código. |
| **c** | Continue | Continúa la ejecución hasta el siguiente breakpoint o el final. |
| **b <línea>** | Breakpoint | Establece un punto de interrupción en la línea indicada (ej. `b 5`). |
| **f <var>** | Force | Inspecciona el valor de una variable (ej. `f x`). |
| **r** | Reload | Recarga el archivo y reinicia la sesión (útil si editaste el código). |
| **clear** | Clear | Elimina todos los breakpoints. |
| **main** | Main | Ejecuta la función `main` (necesario para iniciar si no lo hace auto). |
| **help** | Ayuda | Muestra este manual en la ventana de logs. |
| **q** | Quit | Cierra el depurador. |
| **F10** | Salida Rápida | Cierra inmediatamente la aplicación. |

### 4. Navegación
*   **Flechas Arriba/Abajo**: Desplaza la vista del código fuente (scroll).
*   **Re Pág / Av Pág**: Desplaza el código más rápido.

## AVISOS
Este proyecto puede contener fallos, errores en comandos o de ejecución, se recomienda
discresión al momento de utilizarlo.

---
*Hecho con ❤️ para la cátedra de Paradigmas de Programación.*
