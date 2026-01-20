--Ejercicio 2: 
--a) generalizar la funciones de tipo "FILTER" sobre lista de enteros.
--b) dar una versión polimorfica de la misma.
--c) redefinir la función "soloPares" en términos de dicha generalización.


--Funciones de prueba (funcionan para ambas):
    esPar :: Int -> Bool 
    esPar x = mod x 2 == 0

    menor10 :: Int -> Bool 
    menor10 x = x < 10

--Funciones de prueba para polimorfismo (solo para la polimórfica):
    charA :: Char -> Bool 
    charA w = w == 'a'

    palabraClave :: [Char] -> Bool 
    palabraClave w = w == "clave"

    verdad :: Bool -> Bool 
    verdad b = b == True

--Inciso (a):

    --Funcion filterGeneral:
    filterGeneralInt :: [Int] -> (Int -> Bool) -> [Int]
    filterGeneralInt [] f = []
    filterGeneralInt (x : xs) f | f x == True = x : filterGeneralInt xs f 
                                | f x == False = filterGeneralInt xs f


--Inciso (b):
    --Funcion polFilterGeneral Polimórfica:
    polFilterGeneral :: [a] -> (a -> Bool) -> [a]
    polFilterGeneral [] f = []
    polFilterGeneral (x : xs) f | f x == True = x : polFilterGeneral xs f 
                                | f x == False = polFilterGeneral xs f

--Inciso (c):
    --Función soloPares redefinida en términos de polFilterGeneral:
    soloPares :: [Int] -> [Int]
    soloPares xs = polFilterGeneral xs esPar

    
