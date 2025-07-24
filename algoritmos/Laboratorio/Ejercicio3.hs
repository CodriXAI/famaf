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

