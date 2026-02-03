--Ejercicio 6:

--a) Definir un tipo "BinTree" que permita representar un arbol binario
--genérico, en cuyos nodos se almacenen valores de un tipo arbitrario.

--b) Definir una función de _folding_ que recorra los elementos del arbol en
--alguna de los tres ordenes posibles (preorder,inorder o posorder).
--Ayuda: devolver una lista con los elementos del arbol en el orden en el que 
--fueron visitados.

--c) Definir una función que devuelva la profundidad de un arbol binario. Luego,
--redefinirla en terminos de una funcion fold que opera sobre arboles binarios.


--Inciso (a)

    --Primeramente deberíamos revisar que debe contener un tipo Árbol Binario:
    -- Debe tener nodos
        -- Cada nodo tiene un máximo de dos hijos (Izquierdo y Derecho)
            -- Puede tener uno o ninguno (en ese caso llegamos al ultimo nodo de esa rama)
                -- El contenido del nodo puede ser de cualquier tipo arbitrario
                -- Se intuye que todos los nodos deben ser del mismo tipo

    -- Caso base: Un nodo sin hijos (Hoja)

    -- Caso recursivo 1: Un nodo con un solo hijo (Rama)

    -- Caso recursivo 2: Un nodo con dos hijos (Rama binaria)

    -- Los 3 casos con un tipo arbitrario a

    data BinTree a = Leaf a 
                   | UnaryNode a (BinTree a)
                   | BinaryNode a (BinTree a) (BinTree a)
                   deriving(Eq, Show) 

    --Ejemplo de función que utilice este tipo:

    unaryCount :: BinTree a -> Int
    unaryCount (Leaf a) = 0
    unaryCount (UnaryNode a subTree) = 1 + unaryCount subTree
    unaryCount (BinaryNode a izq der) = unaryCount izq + unaryCount der

    
    --Impresión del Árbol para mayor comodidad:
    --La idea es que imprimamos según el Nodo diferentes referencias gráficas
    --putStrLn() = put String Line, imprime una string por terminal y 
    --             añade un salto de linea
    --IO es una acción de Input/Output (Interactúa con el exterior)
    --() tipo vacío, no devuelve nada, solo ejecuta la acción
    --where es mas por organización y crear funciones auxiliares
    printTree :: (Show a) => BinTree a -> IO ()
    printTree tree = printRecursive "" tree
        where
            printRecursive pref (Leaf x) = 
                putStrLn (pref ++ "├──[Leaf: " ++ show x ++ "]")
            
            printRecursive pref (UnaryNode x sub) = do -- do ejecuta varias acciones una tras otra
                putStrLn (pref ++ "├──[Unary: " ++ show x ++ "]")
                printRecursive (pref ++ "├───") sub
            
            printRecursive pref (BinaryNode x izq der) = do
                putStrLn (pref ++ "├──[Binary: " ++ show x ++ "]")
                printRecursive (pref ++ "│   ") izq  -- Esta barra "|" ayuda a ver la conexión
                printRecursive (pref ++ "├───") der

--Inciso (b):

    --Primero definamos los recorridos que hay que hacer en el arbol según:

        --Preorder:
            --Recorro la raíz, luego izq y der (si tiene)
            --Casos: Hoja, solo la hoja.
            --       Unario, Primero el unario luego recorro el 
            --       hijo recursivo.
            --       Binario, Primero el Binario, luego izq recursivo, luego 
            --       der recursivo.
        
        --Inorder:
            --Recorro la izq, luego la raíz, luego la der (si tiene)
            --Casos: Hoja, solo la hoja
            --       Unario, Primero el hijo recursivo, luego el Unario
            --       Binario, Primero izq recursivo, luego Binario, luego
            --       der recursivo
        
        --Posorder:
            --Recorro izq, luego der, luego raiz
            --Casos: Hoja, solo la hoja
            --       Unario, Primero el hijo recursivo, luego el Unario 
            --       Binario, Primero izq recursivo, luego der recursivo
            --       finalmente el Binario
    
    --Una vez aclarado los algoritmos, hay que ver cómo se muestra el 
    --recorrido; El ejercicio recomienda una lista de BinTrees

    --Entonces la idea es ir construyendo la lista según los diferentes 
    --casos.


    --Preorder:
    --Recorro la raíz, luego izq y der (si tiene)
    runPre :: BinTree a -> [BinTree a]
    runPre (Leaf a) = [(Leaf a)] 
    runPre (UnaryNode a subTree) = [(UnaryNode a subTree)] ++ runPre subTree
    runPre (BinaryNode a izq der) = [(BinaryNode a izq der)] ++ runPre izq ++ runPre der

    --Inorder:
    --Recorro la izq, luego la raíz, luego la der (si tiene)
    runIn :: BinTree a -> [BinTree a]
    runIn (Leaf a) = [(Leaf a)] 
    runIn (UnaryNode a subTree) = runIn subTree ++  [(UnaryNode a subTree)] 
    runIn (BinaryNode a izq der) = runIn izq ++ [(BinaryNode a izq der)] ++ runIn der

    --Posorder:
    --Recorro izq, luego der, luego raiz
    runPos :: BinTree a -> [BinTree a]
    runPos (Leaf a) = [(Leaf a)] 
    runPos (UnaryNode a subTree) = runPos subTree ++  [(UnaryNode a subTree)] 
    runPos (BinaryNode a izq der) = runPos izq ++ runPos der ++ [(BinaryNode a izq der)] 

--Inciso (c):

    --La profundidad de un árbol se define a la cantidad de niveles que tiene como MÁXIMO un árbol
    --en alguna de sus ramas, por ende si se encuentra una cantidad mayor, esa será la nueva profundidad
    --parcial hasta encontrar otra más grande

    --La lógica será ir recorriendo el arbol e ir sumando los niveles que vayamos encontrando:

    --Casos:  Hoja, solo es 1
    --        Unario, suma 1 y calcula la profundidad del hijo 
    --        Binario, suma 1 y calcula el maximo de la profundidad de izq y der

    --Existe la función max incluida en el prelude de haskell, por ende nos omitimos ese calculo.

    --Calculo de profundidad de un arbol:
    levelTree :: BinTree a -> Int 
    levelTree (Leaf a) = 1
    levelTree (UnaryNode a subTree) = 1 + levelTree subTree 
    levelTree (BinaryNode a izq der) = 1 + max (levelTree izq) (levelTree der)

    --Ahora para generalizar un folder foldTree para realizar diferentes acciones, debemos tener en
    --cuenta que:

    --La función se le agrega a foldTree, por ejemplo: foldTree arbol Funcion:

    --      Las funciones pueden ser: countNodes, levelTree, existUnary, etc

    --Lógica del folder (dificil, rompiendome el coco tratando de entenderlo):
    --   Necesitamos, que un folder sea lo más general posible, de forma tal que:
    --   El folder automáticamente sepa como recorrer en este caso el árbol, irá recolectando los 
    --   valores de manera recursiva
    --   Y luego tener una función que se encargue de operar los datos según el caso concreto

    -- Tampoco lo entendí a la primera, asi que es normal que no quede claro.

    --MEJOR EXPLICACIÓN (Acá entiendo mejor):
    --Cada foldTree solo devuelve un b, lo que hacemos una vez tenemos ese b, es armar la lista
    --con cada valor de b en cada llamada a foldTree, de forma recursiva, ejemplo:
    -- f BinaryNode (x izq der) [foldTree izq, foldTree der] <- Esta es la lista
    -- Y luego F esta recibiendo justamente el arbol BinTree a y la lista [b]

    --Esta técnica es conocida como "Catamorfismo" en funcional (dando forma de abajo hacia arriba)

    foldTree :: (BinTree a -> [b] -> b) -> BinTree a -> b
    foldTree f (Leaf a) = f (Leaf a) []
    foldTree f (UnaryNode a subTree) = f (UnaryNode a subTree) [foldTree f subTree]
    foldTree f (BinaryNode a izq der) = f (BinaryNode a izq der) [foldTree f izq, foldTree f der]
    

    --levelTree en términos del folder (NO se hace recursión, de eso se encarga el folder para ir llamando la función):
    --Tener en cuenta el caso de sumatoria
    --En este caso, se la llama para un solo elemento del árbol
    --El folder va a ir armando la lista haciendo llamadas recursivas por elemento de arbol 
    levelTreeF :: BinTree a -> [Int] -> Int
    levelTreeF (Leaf a) [] = 1
    levelTreeF (UnaryNode a subTree) [elem] = 1 + elem
    levelTreeF (BinaryNode a izq der) [elem1, elem2] = 1 + max (elem1) (elem2)

    --Ejecución paso a paso por ejemplo de levelTreeF con un arbol con una raiz, un hijo izq y un hijo der:

    --      1. Llamamos a foldTree con la orden levelTreeF a la raiz
    --      2. Para la raiz, como es un BinaryNode, la lista a pasar es de 2 elementos
    --      3. Dichos elementos están dados por: foldTree levelTreeF izq y foldTree levelTreeF der 
    --      4. Se hace el de la izquierda, entramos a levelTreeF, como izq es una hoja, da simplemente 1
    --         Output parcial de la lista: [1, foldTree levelTreeF der]
    --      5. Se hace lo mismo con la derecha, y el resultado es:
    --         Output parcial de la lista: [1, 1]
    --      6. Una vez recolectado lo de los hijos, ahora podemos ir al caso del BinaryNode que ordena:
    --         1 + max (1) (1)
    --         = 1 + 1 = 2
    --      => La salida final indica que el arbol tiene profundidad 2.


    --Otro ejemplo adaptado al folder, contarNodos:
    countNodes :: BinTree a -> [Int] -> Int
    countNodes (Leaf a) [] = 1
    countNodes (UnaryNode a subTree) [elem] = 1 + elem
    countNodes (BinaryNode a izq der) [elem1, elem2] = 1 + elem1 + elem2