# TEOREMA 3-COLOR ES NP-COMPLETO

## Divisiones:

### 1RA FASE: Definiciones y Grafo

1) **Preparación y Contexto:** Definir por qué 3-COLOR $\in$ NP (verificación en tiempo polinomial de los lados), plantear el objetivo de la reducción ($3\text{-SAT} \propto 3\text{-COLOR}$) y setear formalmente la notación de las variables y literales de $B$.

2) **Diseño del Grafo (Gadget):** Enumerar el conjunto de vértices ($V$) y el conjunto de lados ($E$). Aclarar explícitamente que el tamaño total del grafo es $|V| = 2 + 2n + 6m$, justificando que la construcción es polinomial.

### 2DA FASE: B es satisfacible <=> X(G) = 3

3) **La Ida ($\Rightarrow$):** Asumir que $B$ es satisfacible ($B(b)=1$). Mostrar cómo el bit de cada variable define el color de su vértice ($0$ o $1$) y usar el pararrayos $k_j$ para absorber el color $0$ en la garra, logrando un 3-coloreo propio y feliz.

4) **La Vuelta ($\Leftarrow$):** Asumir que el grafo se puede pintar con 3 colores. Definir el vector de verdad $b$ en base a qué literales tienen el color de $\text{UNO}$. Aplicar el absurdo (suponer $B(b)=0$), lo que asfixia a la garra, obliga a las $a_{jk}$ a pintarse con solo 2 colores y hace colapsar el triángulo.
