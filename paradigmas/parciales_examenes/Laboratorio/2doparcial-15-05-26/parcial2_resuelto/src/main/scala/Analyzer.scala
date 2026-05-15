/**
 * Responsable de detectar entidades nombradas en texto libre y
 * producir estadísticas sobre ellas.
 */
object Analyzer {

  /**
   * Detecta las entidades del diccionario que aparecen en el texto dado.
   *
   * @param text       texto a analizar (ej: título o cuerpo de un post)
   * @param dictionary lista de entidades conocidas (cargadas desde los diccionarios)
   * @return lista de entidades cuyo texto aparece en el texto analizado
   */
  def detectEntities(text: String, dictionary: List[NamedEntity]): List[NamedEntity] = {
    //val lowerText = text.toLowerCase
    //dictionary.filter(entity => lowerText.contains(entity.text.toLowerCase))
    dictionary.filter(entity => entity.matches(text))
  }
  /**
    * FUNCIÓN DE PARCIAL 2:
    * Detecta únicamente las entidades cuyo isRelevant y cuyo matches es true para
    * el texto dado, es decir solo debe detectar:
    *
    * Person
    * University
    * ProgrammingLanguage
    * Conference (Agregada anteriormente)
    *
    * @param text
    * @param dictionary
    * @return la lista de las entidades que cumplen con las condiciones
    */
  def detectRelevant(text: String, dictionary: List[NamedEntity]): List[NamedEntity] = {
    val entities = detectEntities(text,dictionary)
    entities.filter(entity => entity.isRelevant && entity.matches(text))
  }

  /**
   * Cuenta cuántas entidades de cada tipo fueron detectadas.
   *
   * @param entities lista de entidades detectadas
   * @return mapa de entityType → cantidad de apariciones
   */
  def countByType(entities: List[NamedEntity]): Map[String, Int] = {
    entities.groupBy(_.entityType).view.mapValues(_.size).toMap
  }
}
