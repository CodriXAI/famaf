import org.json4s._
import org.json4s.jackson.JsonMethods._
import scala.io.Source

import scala.util.Using


object Main {
  // Redefinido Subscription para que admita 2 campos más (count y before)
  type subscription = (String, String, String, String)
  // Tipo Post con: (title, selftext, author_fullname)
  type post = (String, String, String)
  // Grupo de Palabras Censuradas
  val censoredWords: Set[String] = Set(
    "LLM", "LLMs", "AI", "ChatGPT", "Copilot", "Claude", "ML", "Gemini", "agent", 
    "agentic"
  )
  // Transformadas a minúsculas
  val censoredWordsLower: Set[String] = censoredWords.map(_.toLowerCase)

  // Pure function to read subscriptions from a JSON file
  def readSubscriptions(path: String): Option[List[subscription]] = {
    // Evita Resource Leaks
    Using(Source.fromFile(path)){ source =>
      val jsonString = source.mkString
      implicit val formats: Formats = DefaultFormats

      val json = parse(jsonString)

      json.children.flatMap { item =>
        val name = (item \ "name").extractOpt[String]
        val url = (item \ "url").extractOpt[String]
        val before = (item \ "before").extractOpt[String]
        val count = (item \ "count").extractOpt[String]

        //Si TODOS los campos fueron correctamente cargados, se agregarán a la Lista
        name.flatMap(n =>
          url.flatMap(u =>
            before.flatMap(bf =>             
              count.map(c =>
                (n, u, bf, c)
              )
            )
          )
        )
      }
    }.toOption
  }

  def readPosts(url: String): Option[List[post]] = {
    Using(Source.fromURL(url)){ source =>
      val source = Source.fromURL(url)
      val jsonContent = source.mkString
      implicit val formats: Formats = DefaultFormats

      val json = parse(jsonContent)
      val children = (json \ "data" \ "children").children

      children.flatMap { child =>
        val data = child \ "data"

        val title = (data \ "title").extractOpt[String]
        val selftext = (data \ "selftext").extractOpt[String]
        val author = (data \ "author_fullname").extractOpt[String]

        // Si y solo si TODOS los campos son válidos, se devolverá el post (Some)
        // Caso contrario, devolverá None
        title.flatMap(t =>
          selftext.flatMap(st =>
            author.map(a => 
              (t, st, a)
            )
          )
        )
      }.filter{ case (title, selftext, author) =>
        title.trim.nonEmpty && selftext.trim.nonEmpty && author.trim.nonEmpty 
        // En caso que algún campo sea vacío, se descarta
      }
    }.toOption
  }

  // Separa el texto en palabras simples
  def wordsFromText(text: String): List[String] = {
    text
      .split("[^A-Za-z']+")
      .toList
      .filter(_.nonEmpty)
  }

  // Conserva las palabras censuradas
  def onlyCensored (tokens : List[String]): List[String] = {
    tokens.filter { word =>
      censoredWordsLower.contains(word.toLowerCase)
    }
  }

  // Elimina las palabras censuradas
  def cleanCensored (tokens : List[String]): String = {
    tokens.filter { word =>
      !censoredWordsLower.contains(word.toLowerCase)
    }.mkString(" ")
  }

  // Agrupa palabras equivalentes y cuenta sus ocurrencias
  def countWordFrequencies(words: List[String]): List[(String, Int)] = {
    words
      .groupBy(identity)
      .map { case (word, occurrences) => (word, occurrences.size) }
      .toList
  }

  // Pure function to format posts from a subscription
  def formatSubscription(url: String, posts: List[post]): String = {
    val header = s"\n${"=" * 80}\nPosts from: $url \n${"=" * 80}"

    // "Hay que desarrollar el contador de palabras y después filtrarlas"
    // 1: Dividir la lista de cadenas de title y selftext en palabras individuales
    // 2: Contar las palabras que sean censurables
    // 3: Filtrarlas del title y del selftext

    val formattedPosts = posts.map{ case (title, selftext, author) => 

      val tokens = wordsFromText(s"$title $selftext")

      val censored = onlyCensored(tokens)

      val frequencies = countWordFrequencies(censored)

      val summation = frequencies.foldLeft(0)((acumulador, size) => acumulador + size._2)

      val titleWords = wordsFromText(title)
      val selftextWords = wordsFromText(selftext)

      val cleanTitle = cleanCensored(titleWords)
      val cleanSelftext = cleanCensored(selftextWords)

      "--------------------------------------" +
      s"\n ==TITLE== \n $cleanTitle \n" + 
      s"\n ==CONTENT== \n $cleanSelftext \n" +
      s"\n Palabras Censuradas: ${summation} \n" + 
      s"\n==AUTHOR== \n $author \n" +
      "--------------------------------------\n\n"
    }.mkString("\n")

    header + "\n" + formattedPosts
  }

  // Main function to run
  def main(args: Array[String]): Unit = {
    val header = s"Reddit Post Parser\n${"=" * 40}"

    println("=======================")
    println("")
    println("EJ1: LEER SUSCRIPCIONES")
    
    readSubscriptions("subscriptions.json") match {
      case None =>
        // Manejo de Excepciones: El archivo JSON falló al Parsearse:
        println("[Error]: No se pudo leer el archivo de subscripciones o el JSON es incorrecto")

      case Some(subs) =>
        val postToRead = subs.map{ case (name, url, before, count) =>
            println(s"$url")
        }

        println("")
        println("=======================")
        println("")
        println("EJ2: DESCARGAR POSTS")
  
        val allPosts = subs.map{ case (name, url, before, count) =>
            println(s"Fetching posts from: $url")
            val optPosts = readPosts(url)
            (name, url, optPosts)
        }

        println("")
        println("=======================")
        println("EJ3: IMPRIMIR POSTS Y CONTEO DE PALABRAS CENSURADAS")
        println("=======================")

        // Generamos el posts manejando cada Option de posts por separado:
        val posts = allPosts.map { 
          case (_, url, Some(posts)) => 
            formatSubscription(url, posts)
          case (_, url, None) => 
            // En caso de que ESA URL ESPECÍFICA haya fallado, se notifica:
            s"\n${"=" * 80}\n[Error] No se pudo descargar el feed:\n $url\n${"=" * 80}"
        }.mkString("\n")

        println(posts)
    }
  }
}
