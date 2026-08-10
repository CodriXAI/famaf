# Take Home | Recomendaciones
>Basado en el Take Home **Agatha Criestie. Death on the cards**

Podemos dividir el esfuerzo de un Take Home de IS1 de la siguiente manera:

    ┌────────────────────────────────────────────────────────┐
    │  60% — MODELADO, ARQUITECTURA Y DOCUMENTACIÓN          │
    │  (Casos de Uso, Diagramas UML, Justificaciones)        │
    ├────────────────────────────────────────────────────────┤
    │  30% — CÓDIGO & TESTING                                │
    │  (Backend/Lógica, Tests Unitarios con Pytest, PEP 8)   │
    ├────────────────────────────────────────────────────────┤
    │  10% — GESTIÓN DEL PROYECTO                            │
    │  (Commits prolijos, Kanban/Trello, Readme, etc.)       │
    └────────────────────────────────────────────────────────┘

## Posibles formas de evaluación:

## Diagramación y Análisis

Acá está la nota más pesada. 

Pueden pedir extraer el **dominio del problema** (reglas del juego de cartas, acciones de los jugadores, turnos, victoria/derrota) y lo plasmes en:

* **Especificación de Requerimientos:** 

    Documentar los casos de uso principales con sus precondiciones, postcondiciones y flujos principales/alternativos. 

* **Diagrama de Casos de Uso:** 

    Identificar los actores (ej. Jugador, Sistema/Servidor) y las acciones.

* **Diagrama de Clases (UML):** 

    Diseñar la estructura Orientada a Objetos (Mazo, Carta, Mano, Jugador, Tablero). Cuidar mucho el acoplamiento y la cohesión. 

* **Diagramas de Secuencia:** 

    Mostrar cómo interactúan los objetos en un flujo crítico (por ejemplo, cuando un jugador juega una carta especial o se desencadena la fase de votación/acusación).

>**La trampa habitual:** Si el código funciona perfecto pero los diagramas UML están mal hechos o no coinciden exactamente con lo implementado en el código, pueden desaprobar o mandar a rehacer. La consistencia entre diagramas y código es clave.

## El Código | La implementación

No te piden un sistema gigante con interfaz gráfica 3D ultra compleja; la interfaz suele ser una **API REST (FastAPI/Flask) o una consola prolija**. 

Lo que miran en el código es:

* **Adhesión al diseño:** 

    Que tus clases de Python reflejen fielmente el Diagrama de Clases que entregaste.

* **Principios de Diseño:** 

    Que apliques separación de responsabilidades, encapsulation y patrones si aplican.

* **Testing:** 
    
    Presencia de **tests unitarios (Pytest)**. Probar las reglas complejas del juego **(caja negra y caja blanca)** suma muchísimos puntos. 

* **Calidad de Código:** 

    Limpieza, nombres claros de variables/métodos y cumplir los estándares de la cátedra.

## Estrategia para el Take Home

1. **No empezar codeando:** 

    Es el error N° 1. 
    * Leer las reglas del problema
    * Identificar los objetos/entidades 
    * Hacer los diagramas primero (en borrador en Mermaid o Draw.io).

2. **Escribir el código respetando los diagramas:** 

    A medida que se programa, si hay que cambiar un método o agregar una clase, ir inmediatamente a actualizar el diagrama UML.

3. **Usar Mermaid.js en el README:** 

    Entregar los diagramas en Markdown con Mermaid hace que los profesores puedan ver los diagramas renderizados directamente en GitHub/GitLab sin tener que andar descargando archivos extra. 

    **ALTERNATIVA:** Usar draw.io y exportarlos como PDF o Imágenes en el mismo markdown    