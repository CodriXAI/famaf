object Main {
  def main(args: Array[String]): Unit = {

    val dictionary: List[NamedEntity] = Dictionary.loadAll()
    println(s"Diccionario cargado: ${dictionary.size} entidades.\n")

    val subscriptions = FileIO.readSubscriptions()

    val allDetected: List[NamedEntity] = subscriptions.flatMap { url =>
      println(s"Descargando posts de: $url")
      val json   = FileIO.downloadFeed(url)
      val titles = FileIO.extractPostTitles(json)
      println(s"\n${"=" * 60}\n$url\n${"=" * 60}")
      titles.flatMap { title =>
        /*
          Habia faltado modificar esta función, lastima :(, no te preocupes rey, vos me hiciste bueno a mi.
          Sin tus errores yo no sería bueno, solo no te rindas porque vas a ser el mejor que hayan visto

          Atte: Del Cris del Futuro para el Cris del Futuro más Crack :D
        */
        val entities = Analyzer.detectRelevant(title, dictionary)
        // Cambio de Formato para el Parcial:
        println(Formatters.formatGroupedNERResult(title, entities))
        entities
      }
    }

    println(s"\n${Formatters.formatEntityStats(Analyzer.countByType(allDetected))}")
  }
}
