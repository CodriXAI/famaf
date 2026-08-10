import time
# pyrefly: ignore [missing-import]
from qiskit import QuantumCircuit, transpile

def print_step(title, description):
    print(f"\n\033[1;36m>> {title}\033[0m")
    print(f"\033[3m{description}\033[0m")
    time.sleep(2)

def main():
    print("\033[1;35m=====================================================\033[0m")
    print("\033[1;35m🌟 TALLER DE COMPUTACIÓN CUÁNTICA: ESTADO DE BELL 🌟\033[0m")
    print("\033[1;35m=====================================================\033[0m\n")
    time.sleep(1)

    print_step("Paso 1: Inicialización", 
               "Creamos un circuito cuántico con 2 Qubits y 2 Bits Clásicos para medir.\n"
               "Inicialmente, todos los qubits están en el estado base |0>.")
    qc = QuantumCircuit(2, 2)
    print("\n[Circuito Actual]")
    print(qc.draw())

    print_step("Paso 2: Superposición (Puerta Hadamard)", 
               "Aplicamos la puerta Hadamard (H) al Qubit 0.\n"
               "Esto pone al Qubit 0 en una superposición de |0> y |1> con igual probabilidad.")
    qc.h(0)
    print("\n[Circuito Actual]")
    print(qc.draw())

    print_step("Paso 3: Entrelazamiento (Puerta CNOT)", 
               "Aplicamos una puerta CNOT (CX) usando el Qubit 0 como control y el Qubit 1 como objetivo.\n"
               "Si el control es |1>, invierte el estado del objetivo.\n"
               "Como el control está en superposición, ¡ambos quedan entrelazados! (Estado de Bell)")
    qc.cx(0, 1)
    print("\n[Circuito Actual]")
    print(qc.draw())

    print_step("Paso 4: Medición", 
               "Colocamos medidores. Esto forzará a la superposición cuántica a colapsar\n"
               "en estados clásicos definidos (0 o 1) que guardamos en los bits clásicos.")
    qc.measure([0, 1], [0, 1])
    print("\n[Circuito Final]")
    print(qc.draw())

    print_step("Paso 5: Ejecución y Simulación", 
               "Ejecutamos nuestro circuito en un simulador local 1000 veces (shots)\n"
               "para comprobar de manera estadística el comportamiento del entrelazamiento.")
    
    # Compatibilidad para diferentes versiones de Qiskit
    try:
        # Qiskit 1.0+
        # pyrefly: ignore [missing-import]
        from qiskit.providers.basic_provider import BasicSimulator
        backend = BasicSimulator()
    except ImportError:
        # Qiskit < 1.0
        # pyrefly: ignore [missing-import]
        from qiskit import BasicAer
        backend = BasicAer.get_backend('qasm_simulator')

    compiled_circuit = transpile(qc, backend)
    job = backend.run(compiled_circuit, shots=1000)
    result = job.result()
    counts = result.get_counts(compiled_circuit)

    print("\n\033[1;32m=== RESULTADOS DE LA SIMULACIÓN ===\033[0m")
    
    # Asegurar que ambos estados esten presentes visualmente, incluso si hay algo raro
    for state in ['00', '01', '10', '11']:
        if state in counts:
            count = counts[state]
            prob = count / 1000.0
            bar = "█" * int(prob * 50)
            print(f"Estado |{state}>: {count:4d} veces | {bar} ({prob*100:.1f}%)")
        else:
            print(f"Estado |{state}>:    0 veces |  (0.0%)")

    print("\n\033[1;33m💡 CONCLUSIÓN:\033[0m")
    print("A pesar de la aleatoriedad intrínseca (tenemos 50% de que el Qubit 0 sea 0 o 1),")
    print("el \033[4mentrelazamiento cuántico\033[0m asegura que ambos resultados **siempre coinciden**.")
    print("Por ello, siempre medimos o bien |00> o bien |11>, demostrando que la información")
    print("del estado de un qubit determina instantáneamente el del otro.")
    print("\033[1;35m=====================================================\033[0m\n")

if __name__ == "__main__":
    main()
