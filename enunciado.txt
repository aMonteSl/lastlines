Escribe un programa lastlines.c en C para Linux que no reciba argumentos.

El programa escribirá por su salida estándar la última línea de todos los ficheros acabados en .txt que se encuentren directamente en el directorio actual (directamente, sin recursión) precedidas del nombre y el número de línea separados por dos puntos. Sólo debe salir con error si tiene problemas al abrir o leer algún fichero acabado en .txt o el directorio.

El formato a imprimir será nombre de fichero, dos puntos, número de línea (empezando en 1), espacio y la última línea. Si el fichero está vacío, se considerará que tiene una línea vacía. Si la última línea no tiene '\n' se considerará una línea igualmente.

El programa no debe atravesar enlaces simbólicos, sólo trabajará con ficheros convencionales (ignorando el resto).

Ejemplo:

$> ls
lastlines
$> echo 'hola
linea bla' > fich.txt
$> echo 'hola
adios
pepe' > fich2.txt
$> echo 'esto no' > fich
$> touch fich3.txt
$> echo -n 'otro
parcial' > fich4.txt
$> ./lastlines
fich.txt:2 linea bla
fich2.txt:3 pepe
fich3.txt:1
fich4.txt:2 parcial


El programa no debe ejecutar otros programas externos ni una shell. Se debe usar lstat(2) para averiguar si los elementos del directorio se corresponden a ficheros.