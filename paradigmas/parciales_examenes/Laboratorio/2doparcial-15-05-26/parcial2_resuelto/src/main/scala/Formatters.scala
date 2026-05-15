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
    val header = s"Post: $postTitle \nEntidades Detectadas: \n" 
    val body =
      if (entities.isEmpty)  " (sin entidades detectadas) \n"
      else
        // 1. Agrupar por tipo (Map[String, List[NamedEntity]])
        entities.groupBy(_.entityType)          // Agrupamos por entityType (esto devuelve Map(String,List[NamedEntity]))
        .toList                                 // Convertimos a una Lista para poder ordenar
        .sortBy(_._1)                           // Ordenamos en orden alfabético según la entityType (El string)
        .map { case (tipo, listaTipo) =>        // Abrimos el contenido para un elemento especifico de entities
          val cantidad = listaTipo.size         // Calculamos el largo de toda la lista de esa entity especifica
          val nombres = listaTipo               // Necesitamos ahora ordenar los nombres
            .map(_.text)                        // De la lista extraemos solo el texto de cada elemento
            .sorted                             // Ordenamos Alfabéticamente
            .mkString("\n ")                    // Convertimos a texto para que podamos devolver la información

          s"$tipo ($cantidad): \n $nombres"     // Formato solicitado en la Consigna
        }.mkString("\n")                        // Convertimos todo lo anterior a texto
    // 3. Unir todo con saltos de línea
    s"$header\n$body\n"
  }
}
