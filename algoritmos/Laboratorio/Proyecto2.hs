--Ejercicio 1:
--a)
data Carrera = Matematica | Fisica | Computacion | Astronomia 
--b)
titulo :: Carrera -> String
titulo t = case t of
    Matematica -> "Licenciatura en Matematicas"
    Fisica -> "Licenciatura en Fisica"
    Computacion -> "Licenciatura en Ciencias de la computuacion"
    Astronomia -> "Licenciatura en Astronomia"
{-
Ejemplos:
ghci> titulo Matematica
"Licenciatura en Matematicas"

ghci> titulo Fisica
"Licenciatura en Fisica"
-}
--c)
data NotaBasica = Do | Re | Mi | Fa | Sol | La | Si 
--d)
cifradoAmericano :: NotaBasica -> Char
cifradoAmericano n = case n of
    Do -> 'C'
    Re -> 'D'
    Mi -> 'E'
    Fa -> 'F'
    Sol -> 'G'
    La -> 'A'
    Si -> 'B'
{-
Ejemplos:
ghci> cifradoAmericano Do
'C'

ghci> cifradoAmericano Si
'B'
-}

--Ejercicio 2)
--a)
data NotaBasica' = Do' | Re' | Mi' | Fa' | Sol' | La' | Si' deriving(Eq,Show,Ord)

--Ejercicio 3)
--a)
minimoElemento :: (Ord a) => [a] -> a
minimoElemento [] = error "Lo sentimos, la funcion minimoElemento no esta definida para listas vacias :)"
minimoElemento [x] = x
minimoElemento (x:xs) = x `min` (minimoElemento xs)
{-
Ejemplos:
ghci> minimoElemento []
*** Exception: Lo sentimos, la funcion minimoElemento no esta definida para listas vacias :)
CallStack (from HasCallStack):
  error, called at Proyecto2.hs:44:21 in main:Main

ghci> minimoElemento [1]
1

ghci> minimoElemento [1,0,3,4]
0
-}

--b)
minimoElemento' :: (Show a,Ord a, Bounded a) => [a] -> a
minimoElemento' [] = minBound
minimoElemento' [x] = x
minimoElemento' (x:xs) = x `min` (minimoElemento' xs)
{-
Ejemplos:
ghci> minimoElemento [Fa',La',Sol',Re',Fa']
Re'

ghci> minimoElemento [La',Sol',Fa']
Fa'
-}

--Ejercicio 4
--a)
--Sinonimos de tipo
type Altura = Int
type NumCamiseta = Int

--Tipos algebraicos sin parametros
data Zona = Arco | Defensa | Mediocampo | Delantera deriving(Show,Eq)
data TipoReves = DosManos | UnaMano deriving(Show,Eq)
data Modalidad = Carretera | Pista | Monte | BMX deriving(Show,Eq)
data PiernaHabil = Izquierda | Derecha deriving(Show,Eq)

--Sinonimo
type ManoHabil = PiernaHabil

--Deportista es un tipo algebraico con constructores parametricos
data Deportista = Ajedrecista --Constructor sin argumentos
 | Ciclista Modalidad --Constructor con un argumento
 | Velocista Altura --Constructor con un argumento
 | Tenista TipoReves ManoHabil Altura --Constructor con tres argumentos
 | Futbolista Zona NumCamiseta PiernaHabil Altura --Constructor con cuatro argumentos
 deriving(Show,Eq)
 --b)
 --Ciclista :: Modalidad -> Deportista

 --c)
contar_velocistas :: [Deportista] -> Int
contar_velocistas [] = 0
--El elemento es un velocista entonces le suma 1 y hace la recursion
contar_velocistas ((Velocista a):xs) = 1 + contar_velocistas xs
--Cualquier otro elemento que no sea velocista no suma nada y sigue la recursion
contar_velocistas (_:xs) = contar_velocistas xs
{-
Ejemplos:
ghci> []
0

ghci> contar_velocistas [(Velocista 30),Ajedrecista,(Velocista 50)] 
2
-}

--d)
contar_futbolistas :: [Deportista] -> Zona -> Int
contar_futbolistas [] z = 0
contar_futbolistas (x:xs) z = case x of
    (Futbolista z _ _ _) -> 1 + contar_futbolistas xs z
    _ -> contar_futbolistas xs z

{-
contar_futbolistas [(Futbolista Delantera 20 Derecha 20)] Arco
z = Arco

Si:
(Futbolista Delantera 20 Derecha 20) /= (Futbolista Arco _ _ _)

¿Por qué ignora que hay zonas distintas?
-}

{-
En este caso, logra detectar cuando se trata de un futbolista, mas no puedo detectar cuando es una zona en específico.
Ejemplo:
ghci> contar_futbolistas [(Futbolista Delantera 20 Derecha 20),(Futbolista Mediocampo 20 Izquierda 20)] Mediocampo
2
ghci> contar_futbolistas [(Futbolista Delantera 20 Derecha 20),(Futbolista Mediocampo 20 Izquierda 20)] Arco
2
-}

--e)
filtroFut :: Zona -> Deportista -> Bool
filtroFut z (Futbolista zn _ _ _) = zn == z
filtroFut z _ = False

contar_futbolistas' :: [Deportista] -> Zona -> Int
contar_futbolistas' xs z = length(filter(filtroFut z)xs)
{-
Ejemplos:
ghci> contar_futbolistas' [(Futbolista Delantera 20 Derecha 20),Ajedrecista,(Futbolista Arco 20 Izquierda 20)] Arco
1

ghci> contar_futbolistas' [(Futbolista Arco 20 Derecha 20),Ajedrecista,(Futbolista Arco 20 Izquierda 20)] Arco
2
-}

    
--Ejercicio 5
--a)
sonidoNatural :: NotaBasica ->  Int
sonidoNatural Do = 0
sonidoNatural Re = 2
sonidoNatural Mi = 4
sonidoNatural Fa = 5
sonidoNatural Sol = 7
sonidoNatural La = 9
sonidoNatural Si = 11
--b)
data Alteracion = Bemol | Natural | Sostenido
--c)
data NotaMusical = Nota NotaBasica Alteracion
--d)
sonidoCromatico :: NotaMusical -> Int
sonidoCromatico (Nota n a) =
    case a of
        Bemol -> valorNota - 1
        Sostenido -> valorNota + 1
        Natural -> valorNota
    where 
        valorNota = sonidoNatural n
--e)
instance (Eq NotaMusical) where
    nm1 == nm2 = sonidoCromatico nm1 == sonidoCromatico nm2
{-
Ejemplos:
ghci> Nota Do Sostenido == Nota Re Bemol
True
ghci> Nota Fa Sostenido == Nota Re Bemol
False
-}
--f)
instance (Ord NotaMusical) where
    nm1 <= nm2 = sonidoCromatico nm1 <= sonidoCromatico nm2
{-
Ejemplos:
ghci> Nota Mi Bemol <= Nota Mi Natural    
True
ghci> Nota Mi Sostenido <= Nota Mi Natural
False
-}
--Ejercicio 6:
primerElemento :: [a] -> Maybe a
primerElemento [] = Nothing
primerElemento (x:xs) = Just x
{-
Ejemplos:
ghci> primerElemento []
Nothing
ghci> primerElemento [2,3,4] 
Just 2
ghci>
-}

--Ejercicio 7:
data Cola = VaciaC | Encolada Deportista Cola deriving(Show)
--a1)
atender :: Cola -> Maybe Cola
atender VaciaC = Nothing
atender (Encolada d (Encolada de p)) = Just (Encolada de p)
{-
Ejemplos:
ghci> atender (Encolada(Ajedrecista)(Encolada(Ciclista BMX) VaciaC))   
Just (Encolada (Ciclista BMX) VaciaC)
ghci> atender VaciaC
Nothing
-}

--a2)
encolar :: Deportista -> Cola -> Cola
encolar d VaciaC = Encolada d VaciaC
encolar d (Encolada d' c) = Encolada d (Encolada d' c) 
{-
Ejemplos:
ghci> encolar Ajedrecista (Encolada Ajedrecista (Encolada (Ciclista BMX) VaciaC))
Encolada Ajedrecista (Encolada Ajedrecista (Encolada (Ciclista BMX) VaciaC))

ghci> encolar Ajedrecista VaciaC
Encolada Ajedrecista VaciaC
-}

{-Esta funcion es parecida al constructor-}

--a3)
busca :: Cola -> Zona -> Maybe Deportista
busca VaciaC z = Nothing
busca (Encolada (Futbolista zn nc ph a) c) z | z == zn = Just ((Futbolista zn nc ph a)) | otherwise = busca c z
busca (Encolada _ c) z = busca c z 
{-
Ejemplos:
ghci> busca (Encolada (Futbolista Delantera 20 Derecha 20) VaciaC) Mediocampo
Nothing
ghci> busca (Encolada (Futbolista Mediocampo 20 Derecha 20) VaciaC) Mediocampo
Just (Futbolista Mediocampo 20 Derecha 20)
-}

--Ejercicio 8:
data ListaAsoc a b = Vacia | Nodo a b ( ListaAsoc a b ) deriving(Show,Eq)
{-
a)
Podriamos instanciar el tipo ListaAsoc de la siguiente forma:
type lineaTelefonica = ListaAsoc Int Int
-}

--b1)
la_long :: ListaAsoc a b -> Int
la_long Vacia = 0
la_long (Nodo _ _ resto) = 1 + la_long resto 
{-
Ejemplos:
ghci> la_long (Nodo 1 2 (Nodo 8 3 (Vacia)))
2

ghci> la_long (Nodo 1 2 (Nodo 8 3 (Nodo 4 5 (Vacia))))
3
-}

--b2)
la_concat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b
la_concat Vacia l2 = l2
la_concat (Nodo clave valor r1) l2 = Nodo clave valor (la_concat r1 l2)
{-
Ejemplos:
ghci> la_concat (Nodo 3 4 (Vacia)) (Nodo 5 6 (Vacia))
Nodo 3 4 (Nodo 5 6 Vacia)

la_concat (Nodo 0 5 (Vacia)) (Nodo 1 3 (Nodo 9 0(Vacia)))
Nodo 0 5 (Nodo 1 3 (Nodo 9 0 Vacia))
-}

--b3)
la_agregar :: Eq a => ListaAsoc a b -> a -> b -> ListaAsoc a b
la_agregar Vacia nuevaClave nuevoValor = Nodo nuevaClave nuevoValor Vacia
la_agregar (Nodo clave valor resto) nuevaClave nuevoValor
    | nuevaClave == clave = Nodo nuevaClave nuevoValor resto
    | otherwise = Nodo clave valor (la_agregar resto nuevaClave nuevoValor)
{-
ghci> la_agregar (Nodo 2 3 (Vacia)) 5 6
Nodo 2 3 (Nodo 5 6 Vacia)

ghci> la_agregar Vacia 5 6             
Nodo 5 6 Vacia
-}

--b4)
la_pares :: ListaAsoc a b -> [(a, b)]
la_pares Vacia = []
la_pares (Nodo clave valor resto) = (clave, valor) : la_pares resto
{-
Ejemplos:
ghci> la_pares (Nodo 2 3 (Vacia))
[(2,3)]
ghci> la_pares (Nodo 2 3 (Nodo 5 6 (Nodo 8 9 (Vacia))))
[(2,3),(5,6),(8,9)]
-}

--b5
la_busca :: Eq a => ListaAsoc a b -> a -> Maybe b
la_busca Vacia _ = Nothing
la_busca (Nodo clave valor resto) b
    | clave == b = Just valor
    | otherwise = la_busca resto b
{-
Ejemplos:
ghci> la_busca (Nodo 9 8 (Nodo 3 0 (Nodo 200 300 (Vacia)))) 200
Just 300
ghci> la_busca (Nodo 9 8 (Nodo 3 0 (Nodo 200 300 (Vacia)))) 300
Nothing
-}

--b6)
la_borrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b
la_borrar _ Vacia = Vacia
la_borrar claveActual (Nodo clave valor resto)
    | claveActual == clave = resto
    | otherwise = Nodo clave valor (la_borrar claveActual resto)
{-
Ejemplos:
ghci> la_borrar 4 (Nodo 3 500(Nodo 5 40(Nodo 4 20 (Nodo 2 30(Vacia)))))
Nodo 3 500 (Nodo 5 40 (Nodo 2 30 Vacia))

ghci> la_borrar 45 (Nodo 3 500(Nodo 5 40(Nodo 4 20 (Nodo 2 30(Vacia)))))
Nodo 3 500 (Nodo 5 40 (Nodo 4 20 (Nodo 2 30 Vacia)))
-}

type NombreApellido = String
data Nivel = One | Two | Three deriving(Show,Eq)
type NotaParcial1 = Int
type NotaParcial2 = Int
type NotaFinal = Int

data NotasDeIngles = EvolucionDelEstudiante NombreApellido Nivel NotaParcial1 NotaParcial2 NotaFinal NotasDeIngles | NoHayMasEstudiantes

pasaDeNivel :: NotasDeIngles -> String -> Bool
pasaDeNivel NoHayMasEstudiantes n = False
pasaDeNivel (EvolucionDelEstudiante n l p1 p2 f xs) n1 | n == n1 = ( ( l==Three && (p1>=7 && p2>=7 && f>=8 ) ) || ( (p1>=7 || p2>=7) && f>=6 ) ) | otherwise = pasaDeNivel xs n1

devolverNivel :: NotasDeIngles -> String -> Maybe Nivel
devolverNivel NoHayMasEstudiantes n = Nothing
devolverNivel (EvolucionDelEstudiante n l p1 p2 f xs) n1 | n==n1 = Just l | otherwise = Nothing








    
 


