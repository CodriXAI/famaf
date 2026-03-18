--Otro concepto interesante del paradigma funcional, es que, podemos definir 
--nuestos propios tipos:

type Radio = Float   --Define un "alias de tipo" (sinónimo)
type Lado = Float

--Vamos a definir 4 figuras
data Figura = Circulo Radio        --Cada uno de estos es un _constructor_
            | Cuadrado Lado        --define el constructor de un "Cuadrado"
            | Rectangulo Lado Lado --define el constructor de un "Rectangulo"
            | Punto                --define el constructor de un "Punto"
              deriving (Eq, Show)
              
--(esta última linea permite hacer que se impriman en pantalla los constructores
--de una Figura, y que se puedan comparar.)

--Y obviamente, podemos definir funciones sobre nuestros propios tipos de datos:

perimetro :: Figura -> Float
perimetro (Circulo radio) = 2 * pi * radio
perimetro (Cuadrado lado) = 4 * lado
perimetro (Rectangulo base altura) = 2 * base + 2 * altura
perimetro (Punto) = error "No se puede calcular el perimetro del punto"

--Ejercicio 4: definir una función que devuelva la superficie de una "Figura"

--Primero antes de codear, debemos averiguar las fórmulas de las superficies de cada
--elemento de nuestro tipo figura:

--Superficie de:
--  Circulo: pi * (Radio*Radio)
--  Cuadrado: Lado * Lado
--  Rectangulo: Base * Altura
--  Punto: No se puede calcular

superficie :: Figura -> Float 
superficie (Circulo radio) = pi * (radio * radio)
superficie (Cuadrado lado) = lado * lado
superficie (Rectangulo base altura) = base * altura 
superficie (Punto) = error "No se puede calcular la superficie del punto"