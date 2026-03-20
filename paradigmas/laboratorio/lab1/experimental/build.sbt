//SBT = Scala Build Tool
//Scala = Scalable-Language Combination

// Nombre del proyecto del Laboratorio 1
name := "rss-parser"

version := "0.1.0"

/* Versión de Scala: Ojo que el README decía Scala 3 
  pero acá estamos usando la 2.13.18 
*/
scalaVersion := "2.13.18"

// Librería para parsear Reddit (usa el motor Jackson)
libraryDependencies += "org.json4s" %% "json4s-jackson" % "4.0.6"
