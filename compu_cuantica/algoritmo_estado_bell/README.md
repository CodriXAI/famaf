# 🌌 Estado de Bell: Taller de Computación Cuántica

![Python](https://img.shields.io/badge/Python-3.x-blue.svg)
![Qiskit](https://img.shields.io/badge/Qiskit-Quantum-purple.svg)

## 📌 Descripción del Proyecto

Este proyecto es una demostración educativa sobre cómo crear y medir un **Estado de Bell** (entrelazamiento cuántico) utilizando [Qiskit](https://qiskit.org/), el framework de computación cuántica de IBM.

Ha sido diseñado como parte de un **Taller de Computación Cuántica**, proporcionando una experiencia interactiva paso a paso en la terminal. El programa explica y construye de manera progresiva el circuito cuántico, aplicando las compuertas necesarias y simulando las mediciones finales para ilustrar visualmente el concepto de entrelazamiento cuántico.

Ideal para la sección de portfolio dedicada a tecnología cuántica y programación científica.

## ✨ Características

- **Ejecución Paso a Paso:** El script pausa y explica cada etapa del proceso (Inicialización, Superposición, Entrelazamiento, Medición).
- **Visualización en Terminal:** Imprime representaciones visuales del circuito cuántico en la consola en tiempo real.
- **Simulación Estadística:** Ejecuta el circuito 1000 veces (`shots`) en un simulador local para demostrar de forma empírica y probabilística el entrelazamiento.
- **Compatibilidad:** Diseñado para funcionar de manera estable con diferentes versiones de Qiskit (incluyendo retrocompatibilidad con < 1.0).

## 🧠 Conceptos Clave

1. **Superposición (Compuerta Hadamard - H):** Pone a un qubit en un estado donde es 0 y 1 al mismo tiempo, con igual probabilidad.
2. **Entrelazamiento (Compuerta CNOT):** Condiciona el estado de un qubit objetivo al estado de un qubit de control. Si el primero está en superposición, ambos qubits quedan entrelazados.
3. **Estado de Bell:** Un tipo específico de estado cuántico con entrelazamiento máximo entre dos qubits. Al medir uno, el estado del otro colapsa instantáneamente de manera correlacionada.

## 🚀 Requisitos e Instalación

Para ejecutar este proyecto de manera local, asegúrate de tener instalado Python 3.x. Se recomienda utilizar un entorno virtual.

### 1. Clonar el repositorio
```bash
git clone git@github.com:CodriXAI/quantum-bell-state.git
cd quantum-bell-state
```

### 2. Crear y activar un entorno virtual
```bash
python3 -m venv .venv
source .venv/bin/activate  # En Linux/Mac
# En Windows: .venv\Scripts\activate
```

### 3. Instalar Qiskit
```bash
pip install qiskit
```

## 🎮 Ejecución

Una vez configurado el entorno, puedes ejecutar la demostración interactiva con el siguiente comando:

```bash
python3 estado_bell.py
```

### Ejemplo de Salida (Resultados)
Al finalizar los pasos, el programa mostrará estadísticas como las siguientes, demostrando que ambos qubits siempre colapsan en el mismo estado (`|00>` o `|11>`), debido al entrelazamiento cuántico:
```text
=== RESULTADOS DE LA SIMULACIÓN ===
Estado |00>:  508 veces | █████████████████████████ (50.8%)
Estado |01>:    0 veces |  (0.0%)
Estado |10>:    0 veces |  (0.0%)
Estado |11>:  492 veces | ████████████████████████ (49.2%)
```

## 🤝 Contribuciones y Contacto

¡Las contribuciones son bienvenidas! Si deseas mejorar este taller o agregar nuevos algoritmos, siéntete libre de abrir un *Pull Request* o un *Issue*.