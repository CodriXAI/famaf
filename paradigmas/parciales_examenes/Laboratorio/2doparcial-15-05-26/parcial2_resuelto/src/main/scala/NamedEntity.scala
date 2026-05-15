/**
 * Clase base abstracta para todas las entidades nombradas.
 *
 * Una entidad nombrada es una expresión del texto que refiere a un objeto
 * del mundo real (persona, lugar, organización, tecnología, etc.).
 *
 * @param text el texto tal como aparece en el corpus
 */
abstract class NamedEntity(val text: String) {

  /**
   * Retorna el tipo de la entidad como String.
   */
  def entityType: String

  /**
   * Retorna una línea de descripción de la entidad para el informe.
   */
  def describe: String = s"[$entityType] $text"

  /**
    * Estrictamente la palabra debe coincidir
    *
    * @param s
    * @return si la palabra es estrictamente la esperada
    */
  def matches(s: String): Boolean = {
    /*
      ANTES:
      s == text //MUY ROBUSTO
    */

    // Solución:
    s.toLowerCase.contains(text.toLowerCase)
  }

  /**
    * Realiza relevamiento de clases
    *
    * @return true si es relevante
    */
  def isRelevant: Boolean = true
}

class Person(text: String) extends NamedEntity(text) {
  def entityType: String = "Person"

  override def matches(s: String): Boolean = {
    // Bien porque era CASE-SENSITIVE este caso, a diferencia de NamedEntity
    s.contains(text)
  }
}

class Organization(text: String) extends NamedEntity(text) {
  def entityType: String = "Organization"
  // Sobreescribe isRelevant
  override def isRelevant = false
}

class University(text: String) extends Organization(text) {
  override def entityType: String = "University"
  // Sobreescribe al Padre
  override def isRelevant: Boolean = true
}

class Place(text: String) extends NamedEntity(text) {
  def entityType: String = "Place"
  // Sobreescribe isRelevant
  override def isRelevant = false
}

class Technology(text: String) extends NamedEntity(text) {
  def entityType: String = "Technology"
  // Sobreescribe isRelevant
  override def isRelevant = false

  // Sobreescribe matches para detectar por ej. "Python" y no "python"
  override def matches(s : String): Boolean = { 
    // Esto estuvo perfecto
    val regex = ("\\b" + text + "\\b").r
    regex.findFirstIn(s).isDefined
  }
}

class ProgrammingLanguage(text: String) extends Technology(text) {
  override def entityType: String = "ProgrammingLanguage"
  // Sobreescribe al Padre
  override def isRelevant: Boolean = true
}

// Clases Agregadas del Parcial:

abstract class Event(text: String) extends NamedEntity(text){}

class Conference(text: String) extends Event(text){
  def entityType: String = "Conference"
}
