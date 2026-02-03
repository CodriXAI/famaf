--Esta es una CONTINUACIÓN para evaluar en profundidad el alcance de las funciones 
--POLIMÓRFICAS abstractas

--Función para polGeneralMap:
--(La idea es que a cada elemento de tipo 'a' apliquemos algo)
--Por ejemplo, la identidad, que nos devuelve literalmente lo mismo para verificar
--Si todo sale bien

identidad :: a -> a 
identidad x = x

--Como NO sabemos nada del tipo 'a' (abstracto), hay pocas posibilidades para crear
--Funciones generales.

--Función para morePolGeneralMap:
--(La idea es que a cada elemento de tipo 'a' apliquemos algo y devolvamos de tipo 'b')
--En este caso es algo mas complejo de implementar algo general.
--Pero podemos hacer ejemplos concretos como:
--Dada una lista de numeros, decir si son menores a un valor especifico
--Dada una lista de booleanos, convertirlos a texto 
--Etc.

--Notar que "generalMap" claramente utiliza alto orden.
--Toma una lista de enteros como primer argumento,
--una función como segundo argumento (que toma un entero y devuelve un entero) 
--y devuelve como output una lista de enteros.


--Más aún, podemos generalizar el tipo de la lista [Int]
--a traves del "POLIMORFISMO" que consiste en definir funciones que
--estén bien definidas para cualquier tipo de datos.
--Asi podemos dar una version polimórfica de la función "generalMap" de
--la siguiente manera:

polGeneralMap :: [a] -> (a -> a) -> [a]
polGeneralMap [] f = []
polGeneralMap (x:xs) f = f x : polGeneralMap xs f

--Literalmente si hacemos:
--polGeneralMap ['a','b','c'] identidad
--El output será ['a','b','c']

--De esta manera, podemos utilizar "polGeneralMap" para realizar cualquier mapeo
--independientemente del tipo de la lista.
--De hecho, podemos dar una versión aún más polimórfica observando que el dominio y la imágen
--de la función de mapeo no necesariamente deben ser del mismo tipo. Es decir:

morePolGeneralMap :: [a] -> (a -> b) -> [b]
morePolGeneralMap [] f = []
morePolGeneralMap (x:xs) f = f x : morePolGeneralMap xs f