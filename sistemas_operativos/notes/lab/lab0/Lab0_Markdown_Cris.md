# Comandos de Linux y Conectores

## Comandos de Linux

---

## 1. `grep`
**Qué hace:** Busca texto dentro de archivos o salidas de otros comandos.  

**Variaciones:**
- `-i` → Ignorar mayúsculas/minúsculas.
- `-n` → Mostrar número de línea.
- `-r` → Buscar recursivamente en carpetas.
- `-v` → Mostrar líneas que **no** coincidan.
- `-E` → Expresiones regulares extendidas.

**Ejemplos:**
```bash
grep "error" log.txt
grep -i "error" log.txt
grep -n "error" log.txt
grep -v "OK" log.txt
```

## 2. `cat`
**Qué hace:** Muestra o concatena archivos

**Variaciones:**
- `-n` → Numera líneas.

- `-b` → Numera solo líneas con contenido.

- `-s` → Quita líneas en blanco repetidas.

**Ejemplos:**
```bash
cat archivo.txt
cat -n archivo.txt
cat archivo1.txt archivo2.txt > juntos.txt
```

## 3. `sort`
**Qué hace:** Ordena lineas

**Variaciones:** 
- `-r` → Orden inverso.

- `-n` → Orden numérico.

- `-u` → Elimina duplicados.

- `-k N` → Ordena por la columna N.

**Ejemplos:**
```bash
sort nombres.txt
sort -r nombres.txt
sort -n numeros.txt
sort -k2 datos.txt
```

## 4. `head`
**Qué hace:** Muestra las primeras lineas de un archivo

**Variaciones:**
- `-n N` → Muestra N líneas (default 10).

**Ejemplos:**
```bash
head archivo.txt
head -n 5 archivo.txt
```

## 5. `awk`
**Qué hace:** Procesa texto por columnas

**Variaciones:**

- `'{print $1}'` → Primera columna.

- `'{print $2, $3}'` → Varias columnas.

- `-F` → Cambia el separador.

**Ejemplos:**
```bash
awk '{print $1}' datos.txt
awk -F, '{print $2}' datos.csv
awk '{if($3 > 10) print $0}' datos.txt
```

## 6. `tr`
**Qué hace:** Traduce o eliminar caracteres

**Variaciones:**
- `tr 'a' 'A'` → Cambia letras.

- `-d` → Borra caracteres.

- `-s` → Comprime repeticiones

**Ejemplos:**
Cambia las minúsculas por las mayúsculas:
```bash
echo "hola" | tr 'a-z' 'A-Z'
```

Elimina los espacios en hola mundo:
```bash
echo "hola mundo" | tr -d ' '
```

Elimina repeticiones de la a:
```bash
echo "aaabbb" | tr -s 'a'
```

## 7. `cut`
**Qué hace:** Extrae partes de líneas

**Variaciones:**
- `-f N` → Campo N.

- `-d` → Delimitador.

- `-c N` → Carácter N.

**Ejemplos:**
```bash
cut -f1 datos.txt
cut -d, -f2 datos.csv
cut -c1-5 texto.txt
```

## 8. `wc`
**Qué hace:** Cuenta líneas, palabras o bytes

**Variaciones:**
- `-l` → Líneas.

- `-w` → Palabras.

- `-c` → Bytes.

**Ejemplos:**
```bash
wc archivo.txt
wc -l archivo.txt
wc -w archivo.txt
```

## 9. `curl`
**Qué hace:** Transfiere datos desde o hacia un servidor, usando protocolos como HTTP, HTTPS, FTP, etc.

**Variaciones:**
- `-O`  Guarda el archivo con el mismo nombre que tiene en el servidor 
- `-o <archivo>` Guarda la salida en un archivo con el nombre que elijas 
- `-L`  Sigue redirecciones (HTTP 3xx) 
- `-I`  Muestra solo los headers de la respuesta HTTP 
- `-X <método>` Especifica el método HTTP (GET, POST, PUT, DELETE) 
- `-d "<datos>"`  Envía datos en una solicitud POST 
- `-H "<header>"` Añade un header HTTP personalizado 
- `-u usuario:contraseña` Autenticación básica 
- `-s` Modo silencioso (sin barra de progreso) 
- `-v` Modo verbose (muestra todo el detalle de la conexión) 

**Ejemplos:**
Mostrar página web en pantalla: 
```bash
curl https://example.com
```

Guardar archivo con el mismo nombre:
```bash
curl -O https://example.com/file.txt
```

Guardar archivo con nombre personalizado:
```bash
curl -o mi_archivo.txt https://example.com/file.txt
```

Hacer POST con datos:
```bash
curl -X POST -d "usuario=cristian&clave=1234" https://example.com/login
```

Ver solo los headers:
```bash
curl -I https://example.com
```

## 10. `sed`
**¿Qué hace?:** Procesa y modifica texto línea por línea: reemplazos, borrados, inserciones o extracciones.

**Variaciones:**
- `-e "<script>"`	Permite pasar un comando sed
- `-f <archivo>`	Ejecuta comandos desde un archivo
- `-i`	Edita el archivo directamente (in-place)
- `-n`	No imprime por defecto; se usa con p para mostrar solo lo deseado
- `-r`	Usa expresiones regulares extendidas (Eregex)
- `-E`	Lo mismo que -r en algunas versiones de sed

**Ejemplos:**
Reemplazar "hola" por "chau" en la salida de un archivo:
```bash
sed 's/hola/chau/' archivo.txt
```

Reemplazar todas las ocurrencias:
```bash
sed 's/hola/chau/g' archivo.txt
```

Borrar lineas que contienen error:
```bash
sed '/error/d' archivo.txt
```

Mostrar solo líneas que contienen “hola”:
```bash
sed -n '/hola/p' archivo.txt
```

Editar archivo directamente:
```bash
sed -i 's/hola/chau/g' archivo.txt
```
---

## Conectores de Comandos

---
## `;` - Punto y Coma

**Qué hace:** Ejecuta varios comandos en secuencia, sin importar si fallan.

**Ejemplo:**
```bash
echo "Hola" ; echo "Mundo"
```

## `&` - Ampersand
**Qué hace:** Ejecuta un comando en segundo plano

**Ejemplo:**
```bash
./programa &   # El programa sigue corriendo y el terminal queda libre
```

## `|` - Pipe
**Qué hace:** Pasa la salida de un comando como entrada de otro

**Ejemplo:**
```bash
cat archivo.txt | grep "error"
```
## `>` - Redirección
**Qué hace:** Envía la salida a un archivo (sobrescribe).

**Ejemplo:**
```bash
echo "Hola" > saludo.txt
```

## `>>` - Redirección al final
**Qué hace:** Igual que `>`, pero **añade** al final.

**Ejemplo:**
```bash
echo "Mundo" >> saludo.txt
```

## `<` - Entrada
**Qué hace:** Usa un archivo como entrada de un comando.

**Ejemplo**
```bash
sort < nombres.txt
```
