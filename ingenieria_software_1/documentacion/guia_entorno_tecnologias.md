# Ingeniería del Software I — Guía de Inicio y Entorno

¡Buenas gente! Dejo este resumen técnico enfocado en **IS1** para que tengamos todo alineado antes del inicio de cursada y facilitemos la organización del proyecto grupal.

---

## ¿Qué vamos a aprender? (Puntos Clave del Programa)

En IS1 el objetivo es abarcar el ciclo de vida completo del desarrollo de software orientado a objetos y metodologías modernas:

* **Requerimientos y Casos de Uso:** Análisis del problema y especificación funcional.
* **Diseño Orientado a Objetos (OO):** Modelado en **UML** (Casos de Uso, Secuencia, Clases) y principios de acoplamiento/cohesión.
* **Arquitectura de Software:** Patrones arquitectónicos, API REST y comunicación de servicios.
* **Calidad & Testing:** Prácticas de TDD, pruebas unitarias (caja negra y caja blanca) y refactorización.

## Stack Tecnológico Recomendado

Para el desarrollo del proyecto y los laboratorios, nos conviene manejar este stack:

**Backend:** Python (`FastAPI` o `Flask`) | Desarrollo ágil, excelente sintaxis y cumple normas PEP 8.

**ORM:**  `SQLAlchemy` | Para mapear objetos a la BD relacional. 

**Testing:**  `Pytest` | Estándar para escribir unit tests y aplicar TDD.

**Diagramado UML:**  `Mermaid.js / Draw.io / PlantUML` | Para crear diagramas de secuencia, clases y casos de uso.

**Control de Versiones:** | `Git + GitHub / GitLab` | Flujo de trabajo colaborativo (`Gitflow`) y Pull Requests. |

## Instalación del Entorno (Nativo vs. Docker)

### Opción A: Instalación Nativa (Desarrollo Local)
1. **Python 3.10+:** Asegurate de tener Python actualizado y verificarlo en la consola con `python --version`.

2. **Entorno Virtual (`venv`):**
   ```bash
   python -m venv venv
   source venv/bin/activate  # En Linux/Mac
   # venv\Scripts\activate   # En Windows
   ```
3. **Dependencias del Proyecto:**
   ```bash
   pip install fastapi uvicorn sqlalchemy pytest
   ```

### Opción B: Entorno Contenedorizado (Docker) | RECOMENDADA
Si preferís aislar el entorno de desarrollo del backend para que corra igual en todas las computadoras del equipo, podés usar este Dockerfile básico para el proyecto:

    ```Dockerfile
    FROM python:3.10-slim

    WORKDIR /app

    COPY requirements.txt .
    RUN pip install --no-cache-dir -r requirements.txt

    COPY . .

    CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000", "--reload"]
    ```
 