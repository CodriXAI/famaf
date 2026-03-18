--Ejercicio 3: 
--a) generalizar la funciones de tipo "FOLD" sobre lista de enteros.
--b) dar una versión polimorfica de la misma.
--c) redefinir la función "sumatoria" en términos de dicha generalización.

--Inciso (a):

    --Funcion general foldInt (Para lista de enteros):

    foldInt :: [Int] -> (Int -> Int -> Int) -> Int 
    --La función f será como nuestro operador basicamente, como un :+: o :*:, etc.
    --El caso base es muy relativo de cada funcion (productoria, sumatoria, etc)
    foldInt [] f = error "No es posible tener lista vacía, rompe casos base"
    foldInt [x] f = x 
    --f funciona como el operador, en este caso entre x y el resto (foldInt xs f)
    --Como si dijieramos x 'f' (foldInt xs f)
    foldInt (x : xs) f = f x (foldInt xs f)

    --Ejemplos en base a foldInt

    suma :: Int -> Int -> Int 
    suma x y = x + y

    mult :: Int -> Int -> Int
    mult x y = x * y 

    sumatoria :: [Int] -> Int 
    sumatoria xs = foldInt xs suma

    productoria :: [Int] -> Int 
    productoria xs = foldInt xs mult


--Inciso (b) y (c) ya incluido:

    --Funcion general polFold (Para lista de cualquier cosa):

    --Ventajas: Si queremos "colapsar" todos los elementos de una lista, entonces
    --tienen que ser del mismo tipo.

    polFold :: [a] -> (a -> a -> a) -> a 
    --La función f será como nuestro operador basicamente, como un :+: o :*:, etc.
    --El caso base es muy relativo de cada funcion (productoria, sumatoria, AND, OR, etc)
    polFold [] f = error "No es posible tener lista vacía, rompe casos base"
    polFold [x] f = x 
    polFold (x : xs) f = f x (polFold xs f)

    --Ejemplos:

    --Auxiliares:
    andAux :: Bool -> Bool -> Bool 
    andAux a b = a && b

    orAux :: Bool -> Bool -> Bool 
    orAux a b = a || b

    --AND anidado (andtoria xd)
    andAnidado :: [Bool] -> Bool
    andAnidado xs = polFold xs andAux 

    --OR anidado (... no voy a decir como se pronuncia con toria)
    orAnidado :: [Bool] -> Bool 
    orAnidado xs = polFold xs orAux

    --Mismos que el inciso (a):
    sumatoriaP :: [Int] -> Int 
    sumatoriaP xs = polFold xs suma

    productoriaP :: [Int] -> Int 
    productoriaP xs = polFold xs mult

    --Recordando las Funciones Lambda:

    --AND anidado (andtoria xd) con Lambda de ejemplo
    --Donde: x elemento, acc acumulado
    andAnidadoLambda :: [Bool] -> Bool
    andAnidadoLambda xs = polFold xs (\x acc -> x && acc )  




    
    