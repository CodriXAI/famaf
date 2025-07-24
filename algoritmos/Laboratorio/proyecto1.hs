--Ejercicio 1
--a)
esCero::Int->Bool
esCero x = x == 0

--b)
esPositivo :: Int -> Bool
esPositivo x = x > 0

--c)
esVocal :: Char -> Bool
esVocal x = (x == 'a' || x == 'e' || x == 'i' ||  x == 'o' || x == 'u')

--d)
valorAbsoluto :: Int -> Int
valorAbsoluto x = abs x

--Ejercicio 2
--a)
paraTodo :: [Bool] -> Bool
paraTodo [] = True
paraTodo (x:xs) = x == True && paraTodo xs
--b)
sumatoria :: [Int] -> Int
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria xs
--c)
productoria :: [Int] -> Int
productoria [] = 1
productoria (x:xs) = x * productoria xs
--d)
factorial :: Int -> Int
factorial 0 = 1
factorial x = x * factorial (x-1)
--e)
promedio :: [Int] -> Int
promedio xs = div (sumatoria xs) (length xs) 

--Ejercicio 3
pertenece :: Int -> [Int] -> Bool
pertenece x [] = False
pertenece x (y:ys) = x == y || pertenece x ys 

--Ejercicio 4
paraTodo' :: (Eq a, Num a) => [a] -> (a -> Bool) -> Bool
paraTodo' [] t = True
paraTodo' (x:xs) t = t x && (paraTodo' xs t)

existe' :: Eq a => [a] -> (a -> Bool) -> Bool
existe' [] t = False
existe' (x:xs) t = t x || existe' xs t

sumatoria' ::Eq a => [a] -> (a -> Int) -> Int
sumatoria' [] t = 0
sumatoria' (x:xs) t = t x + sumatoria' xs t

productoria' :: Eq a => [a] -> (a -> Int) -> Int
productoria' [] t = 1
productoria' (x:xs) t = t x * productoria' xs t

--Ejercicio 5
paraTodo'' :: (Eq a, Num a) => [a] -> (a -> Bool) -> Bool
paraTodo'' xs t = paraTodo' xs t

--Ejercicio 6
--a
esPar :: Int -> Bool
esPar x = mod x 2 == 0

todosPares :: [Int] -> Bool
todosPares xs = paraTodo' xs esPar

--b
esMultiplo :: Int -> Int -> Bool
esMultiplo x y  = mod x y == 0 

hayMultiplo :: Int -> [Int] -> Bool
hayMultiplo y xs = existe' xs (esMultiplo y) 




--hayMultiplo 4 [1,3,5]
--existe (1:[3,5]) (esMultiplo 4) = esmultiplo 4 1 = True
--true || existe' (3:[5]) esMultiplo 4 = esMultiplo 4 3 = False
--(con los demas elementos)
--true
 

--c
cuadrados :: Int -> Int
cuadrados x = x*x

sumaCuadrados :: Int -> Int
sumaCuadrados t = sumatoria' [0..t] cuadrados 

--d
divide :: Int -> Int -> Bool
divide x y  = mod x y == 0 

existeDivisor :: Int -> [Int] -> Bool
existeDivisor n ls = existe' ls (divide n) 

--e
esPrimo:: Int -> Bool
esPrimo n = not(existeDivisor n [2..n-1])

--f
factorial' :: Int -> Int
factorial' n = productoria' [1..n] valorAbsoluto

--g
--filtroPrimo :: [Int] -> [Int]
--filtroPrimo [] = []
--filtroPrimo (x:xs) |(esPrimo x) == True = x : filtroPrimo xs |(esPrimo x) == False = filtroPrimo xs

esPrimo' :: Int -> Int
esPrimo' x | esPrimo x == True = x | otherwise = 1

multiplicaPrimos :: [Int] -> Int
multiplicaPrimos xs = productoria' xs esPrimo'


--h
fib :: Int -> Int
fib 0 = 1
fib 1 = 1
fib n = fib(n-1)+fib(n-2)

lFib :: Int -> [Int]
lFib 0 = [1]
lFib x = lFib(x-1) ++ [fib x] 

esFib :: Int -> Bool 
esFib n = existe' (lFib n) (n == )


--i
todosFib :: [Int] -> Bool
todosFib xs = paraTodo' xs esFib 

--Ejercicio 7:
--a)
--Map: Es una función aplicada a listas cuyo objetivo es tomar una lista xs y un parametro f, y devuelve otra lista aplicando a cada elemento de xs, f. 
--Filter: Toma una lista xs y un predicado, y devuelve otra lista con los elementos de xs que satisfagan al predicado

--b)
--map succ [1, -4, 6, 2, -8] donde succ n = n+1 = [2,-3,7,3,-7]
--c)
--esPositivo [1, -4, 6, 2, -8] = [1,6,2]


--Ejercicio 8:
--a)
multi :: [Int] -> [Int]
multi [] = []
multi (x:xs) = x * 2 : multi xs

--b)
multiConMap :: (Int -> Int) -> [Int] -> [Int]
multiConMap t xs = map t xs 

--Ejercicio 9:
--a)
filtroPrimo :: [Int] -> [Int]
filtroPrimo [] = []
filtroPrimo (x:xs) | x == 0 = filtroPrimo xs | esPrimo x == True = x : filtroPrimo xs | otherwise = filtroPrimo xs  

--b)
filtroP :: (Int -> Bool) -> [Int] -> [Int]
filtroP t xs = filter t xs 

--c)
multiplicaPrimosM :: [Int] -> Int
multiplicaPrimosM xs = productoria (filter esPrimo xs)

--Ejercicio 10:
--a)
primIgualesA :: Eq a => a -> [a] -> [a]
primIgualesA a [] = []
primIgualesA a (x:xs) | a == x = x : primIgualesA a xs | a /= x = []

--b)
primIgualesA' :: Eq a => a -> [a] -> [a]
primIgualesA' t xs = takeWhile (==t) xs 

--Ejercicio 11:
--a)

primIguales :: Eq a => [a] -> [a]
primIguales [] = []
primIguales [x] = [x]
primIguales (x:y:xs)
  | x == y = x : primIguales (y:xs)
  | x /= y = x:[]

--b)
primIguales' :: Eq a => [a] -> [a]
primIguales' (x:y:xs) = primIgualesA y (x:y:xs)


--Funcion Auxiliar:
mismaCategoriaLibro :: Categoria -> Categoria -> Bool
mismaCategoriaLibro Literatura Literatura = True
mismaCategoriaLibro Infantiles Infantiles = True
mismaCategoriaLibro Autoayuda Autoayuda = True
mismaCategoriaLibro Comics Comics = True
mismaCategoriaLibro _ _ = False

instance Eq  ArticulosLibreria where
    (Libro c1 e1 t1 p1) == (Libro c2 e2 t2 p2) = (mismaEditorial e1 e2)&&(t1 == t2)
    (Agenda m1 aa1 p1) == (Agenda m2 aa2 p2) = (mismaMarca m1 m2)&&(aa1==aa2)&&(p1==p2)
    (Cuaderno m1 p1) == (Cuaderno m2 p2) = (mismaMarca m1 m2)&&(p1 == p2)
    _ == _ = False
 



