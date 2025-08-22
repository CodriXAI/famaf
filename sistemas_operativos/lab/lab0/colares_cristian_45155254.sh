#!/bin/bash
# EJERCICIO 1: Modelo del procesador
grep "name" -m 1 /proc/cpuinfo | cut -d ':' -f2
# EJERCICIO 2: Número de unidades de ejecución (cores)
grep "model name" /proc/cpuinfo | wc -l
# EJERCICIO 3: Lista de nombres de usuarios para red social de superhéroes
curl https://raw.githubusercontent.com/dariomalchiodi/superhero-datascience/master/content/data/heroes.csv | cut -d ';' -f2 | tr ' ' '_' | tr 'A-Z' 'a-z' | sed '/^$/d' > superheroes_usuarios.txt
# EJERCICIO 4A: Día de máxima temperatura en Córdoba
sort -n -r datos/weather_cordoba.in -k5 | awk '{print $1, $2, $3}' | head -n1
# EJERCICIO 4B: Día de mínima temperatura en Córdoba
sort -n datos/weather_cordoba.in -k6 | awk '{print $1, $2, $3}' | head -n1
# EJERCICIO 5: Ordenar jugadores de tenis por ranking
sort datos/atpplayers.in -n -k3
# EJERCICIO 6: Ordenar tabla de Superliga por puntos y diferencia de goles
awk '{print $1, $2, $3, $4, $5, $6, $7, $8, $7 - $8}' datos/superliga.in | sort -n -r -k2 -k9 |awk '{print $1, $2, $3, $4, $5, $6, $7, $8}'
# EJERCICIO 7: MAC address de la placa WiFi del equipo
ip a | grep -Eo "ether ([0-9a-f]{2}:){5}[0-9a-f]{2}" | head -n 1 | cut -d ' ' -f2 
# EJERCICIO 8: Renombrar archivos de subtítulos
seq -w 1 10 | xargs -I{} mv serie_prueba/fma_S01E{}_es.srt serie_prueba/fma_S01E{}.srt
# EJERCICIO 9A: Recortar video con ffmpeg
echo no lo hice
# EJERCICIO 9B: Mezclar audio con ffmpeg
echo no lo hice







