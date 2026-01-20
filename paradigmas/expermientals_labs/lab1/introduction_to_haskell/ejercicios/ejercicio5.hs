--Ejercicio 5:

--a) Asi como definimos el tipo "Figura" en el ejercicio anterior, ahora definir
--un tipo "Expr" que permita representar una expresión aritmética sobre enteros
--(sin variables) con nuestros propios operadores :+:, :-:, :*: 
--Por ejemplo: (5 :*: 3) :+: 10 :-: 2 es una "Expr"

--b)Luego, definir su semántica, i.e., definir una función que evalúa (en forma
--natural) una expresión aritmética "Expr". Por ejemplo: 
--
--evaluar ((5 :*: 3) :+: 10 :-: 2) = 5*3 + 10 - 2 = 23
--

--Inciso (a):

    type Termino = Int  

    data Expr = N Int               --Caso Base (Un solo numero)
            | Expr :+: Expr         --Suma (con caso anidado)
            | Expr :-: Expr         --Resta (con caso anidado)
            | Expr :*: Expr         --Multiplicación (con caso anidado)
            deriving(Eq, Show)

    --Ejemplo: (N 5) :+: ((N 5) :*: (N 7))

--Inciso (b):

    --Para ello crearemos 3 funciones:

        --Una para leer la expresión y transformarla a lenguaje natural.
        --Una de evaluación para convertir la semantica.
        --La última muestra el resultado

    --Leer la expresión:
    traducir :: Expr -> String
    traducir (N x) = show x
    traducir (exp1 :+: exp2) = "(" ++ traducir exp1 ++ " + " ++ traducir exp2 ++ ")"
    traducir (exp1 :-: exp2) = "(" ++ traducir exp1 ++ " - " ++ traducir exp2 ++ ")"
    traducir (exp1 :*: exp2) = "(" ++ traducir exp1 ++ " x " ++ traducir exp2 ++ ")"

    --Procesar su semántica:
    semantica :: Expr -> Int 
    semantica (N x) = x
    semantica (exp1 :+: exp2) = (semantica exp1) + (semantica exp2)
    semantica (exp1 :-: exp2) = (semantica exp1) - (semantica exp2)
    semantica (exp1 :*: exp2) = (semantica exp1) * (semantica exp2)

    --Mostrar el resultado:
    procesar :: Expr -> String 
    procesar e = "La expresion: " ++ (traducir e) ++ " es igual a: " ++ show(semantica e)

