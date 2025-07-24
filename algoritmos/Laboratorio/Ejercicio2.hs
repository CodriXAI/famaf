type Titulo = String
type Precio = Int
type AnioAgenda = Int

data Categoria = Literatura | Infantiles | Autoayuda | Comics
data Editorial = Altea | Minotauro | Panini --NO DEBE SER CLASE EQ NI ORD
data Marca = Monoblock | Papikra --NO DEBE SER CLASE EQ NI ORD

data ArticulosLibreria = Libro Categoria Editorial Titulo Precio | Agenda Marca AnioAgenda Precio | Cuaderno Marca Precio --NO DEBE SER CLASE EQ NI ORD
instance Eq  ArticulosLibreria where
    (Libro c1 e1 t1 p1) == (Libro c2 e2 t2 p2) = (mismaEditorial e1 e2)&&(t1 == t2)
    (Agenda m1 aa1 p1) == (Agenda m2 aa2 p2) = (mismaMarca m1 m2)&&(aa1==aa2)&&(p1==p2)
    (Cuaderno m1 p1) == (Cuaderno m2 p2) = (mismaMarca m1 m2)&&(p1 == p2)
    _ == _ = False

--Funcion Auxiliar:
mismaCategoriaLibro :: Categoria -> Categoria -> Bool
mismaCategoriaLibro Literatura Literatura = True
mismaCategoriaLibro Infantiles Infantiles = True
mismaCategoriaLibro Autoayuda Autoayuda = True
mismaCategoriaLibro Comics Comics = True
mismaCategoriaLibro _ _ = False

--Utilizando la variable auxiliar para ver si tienen la misma categoria
cuantosLibros :: [ArticulosLibreria] -> Categoria -> Int
cuantosLibros [] c1 = 0
cuantosLibros ((Libro c e t p):xs) c1 | mismaCategoriaLibro c c1 = 1 + cuantosLibros xs c1 | otherwise = cuantosLibros xs c1

mismaEditorial :: Editorial -> Editorial -> Bool
mismaEditorial Altea Altea = True
mismaEditorial Minotauro Minotauro = True
mismaEditorial Panini Panini = True
mismaEditorial _ _ = False 

mismaMarca :: Marca -> Marca -> Bool
mismaMarca Monoblock Monoblock = True
mismaMarca Papikra Papikra = True
mismaMarca _ _ = False