--Ejercicio 1: 
--a) redefinir la función "duplica" y "mas1" en términos de "generalMap" y 
--"polGeneralMap".

--b) definir la función esPar:: [Int] -> [Bool] en términos de "morePolGeneralMap". 
--Donde la función "esPar" mapea cada elemento de la lista a un booleano que indica si 
--el mismo es un numero par. 
--Por ejemplo, esPar [2,9,4,5] = [True, False, True,False]. 

--Incisco (a)
    --Cuando nos piden redefinir una función A en términos de una funcion B
    --Nos están pidiendo que utilicemos B para construir A

    --Funciones para construir duplica y mas1:
    generalMap:: [Int] -> (Int -> Int) ->  [Int]
    generalMap [] f = []
    generalMap (x:xs) f = f x : generalMap xs f

    polGeneralMap :: [a] -> (a -> a) -> [a]
    polGeneralMap [] f = []
    polGeneralMap (x:xs) f = f x : polGeneralMap xs f

    --redefinición de duplica para generalMap:

    --auxiliar:
    duplicaAuxG :: Int -> Int
    duplicaAuxG  x = x * 2

    --implementación:
    duplicaG :: [Int] -> [Int]
    duplicaG xs = generalMap xs duplicaAuxG             --Caso base no necesario por estar en
                                                    --generalMap

    --redefinición de mas1 para generalMap:

    --auxiliar:
    mas1AuxG :: Int -> Int
    mas1AuxG x = x + 1

    --implementación:
    mas1G :: [Int] -> [Int]
    mas1G xs = generalMap xs mas1AuxG

    --redefinición de duplica para polGeneralMap:

    --auxiliar:
    duplicaAuxP :: (Num a) => a -> a
    duplicaAuxP x = x * 2

    --implementación:
    duplicaP :: (Num a) => [a] -> [a]
    duplicaP xs = polGeneralMap xs duplicaAuxP

    --redefinición de mas1 para polGeneralMap:

    --auxiliar:
    mas1AuxP :: (Num a) => a -> a
    mas1AuxP x = x * 1

    --implementación:
    mas1P :: (Num a) => [a] -> [a]
    mas1P xs = polGeneralMap xs mas1AuxP

    --ALTERNATIVAS:
    --En vez de utilizar funciones auxiliares para cada elemento, se pueden utilizar
    --Las famosas "FUNCIONES LAMBDA" tq así:
    --duplicaG :: [Int] -> [Int]
    --duplicaG xs = generalMap xs (\x -> x * 2) 

--Inciso (b):
    
    --Función para construir esPar:
    morePolGeneralMap :: [a] -> (a -> b) -> [b]
    morePolGeneralMap [] f = []
    morePolGeneralMap (x:xs) f = f x : morePolGeneralMap xs f

    --Función auxiliar:
    esParAuxM :: Int -> Bool
    esParAuxM x = x `mod` 2 == 0

    --Función esPar:
    esPar :: [Int] -> [Bool]
    esPar xs = morePolGeneralMap xs esParAuxM

    --ALTERNATIVA CON LAMBDA:
    --esPar :: [Int] -> [Bool]
    --esPar xs = morePolGeneralMap xs (\x -> x `mod` 2 == 0)

    --Explicación:
    --morePolGeneralMap tiene incluida en sí muchos casos posibles (gracias al 
    --polimorfismo), con a y b, en este caso siendo reemplazados a = Int , b = Bool.
    
