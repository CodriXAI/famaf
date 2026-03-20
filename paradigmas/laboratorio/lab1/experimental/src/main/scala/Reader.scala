import Model.Subscription // Import Subscription type
import scala.io.Source    // I/O handler
import scala.util.Using   // Can automatically close files when finished

// Necesarias para poder parsear y convertir lo que obtengamos del JSON
import org.json4s._
import org.json4s.jackson.JsonMethods._

object SubcriptionsReader {
  def getSubList(path: String): Option[List[Subscription]] = {

    implicit val formats = DefaultFormats // Necesario para json4s

    // Using es una estructura que nos permite cerrar automaticamente el archivo
    // Una vez dejamos de utilizarlo, el => define nuestra función anónima (o lambda)
    // que le pasaremos el argumento source dado por using, y aplicaremos la función
    // usando dicho source. ¿Qué hace la función lambda?, devuelve el valor content
    // que es el source convertido a una cadena de texto
    Using(Source.fromFile(path)) { source => 
      val content = source.mkString // Reading content
      val json = parse(content)     // Transformamos el contenido obtenido en JValue

      // El formato JSON va por jerarquías de padres e hijos.
      // El JArray es el padre (los corchetes [])
      // Luego, dentro del JArray tenemos los childrens
      // Que son los elementos entre llaves {}
      // Donde cada uno tiene sus propiedades (en este caso: name y url)
      // Como ya parseamos usando json4s, solo recorremos a los hijos
      // Y a cada uno accedemos a los campos, los contenidos los transformamos
      // en texto, y los añadimos a la tupla que añadiremos a la lista de subscriptions
      // (Tal cuál lo que devolvemos según el prototipo de getSubList) 
      json.children.map{ item =>
          val name = (item \ "name").extract[String]
          val url = (item \ "url").extract[String]
          (name, url) // Retornamos la tupla ya transformada
      }
    }.toOption
  }
}