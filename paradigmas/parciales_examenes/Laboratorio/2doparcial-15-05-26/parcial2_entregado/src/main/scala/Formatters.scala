/**
 * Responsable de convertir los resultados del análisis a texto para mostrar.
 */
object Formatters {

  /**
   * Formatea el análisis NER de un post individual.
   *
   * @param postTitle título del post analizado
   * @param entities  entidades detectadas en ese post
   * @return bloque de texto con el título y las entidades encontradas
   */
  def formatNERResult(postTitle: String, entities: List[NamedEntity]): String = {
    val header = s"""Post: "$postTitle"\nEntidades detectadas:"""
    val body =
      if (entities.isEmpty) "  (sin entidades detectadas)"
      else entities.map(e => s"  ${e.describe}").mkString("\n")
    s"$header\n$body"
  }

  /**
   * Formatea un resumen de estadísticas de entidades por tipo.
   *
   * @param counts mapa de entityType → cantidad
   * @return texto con las estadísticas ordenadas por cantidad (de mayor a menor)
   */
  def formatEntityStats(counts: Map[String, Int]): String = {
    val lines = counts.toList
      .sortBy(-_._2)
      .map { case (entityType, count) => s"$entityType: $count" }
    ("=== Estadísticas de entidades ===" :: lines).mkString("\n")
  }
  def formatGroupedNERResult(postTitle: String, entities: List[NamedEntity]): String = {
    val header = s"Post: $postTitle \n Entidades Detectadas: \n" 
    val body =
      if (entities.isEmpty)  s"$postTitle\n (sin entidades detectadas)"
      else
        // 1. Agrupar por tipo (Map[String, List[NamedEntity]])
        entities.groupBy(_.entityType).map { case (entityType, entityList) =>
          val entityTexts = entityList.map(_.text).mkString(", ")
          s"$entityType: $entityTexts"
        }
    // 3. Unir todo con saltos de línea
    s"$header\n$body\n"
  }
}
