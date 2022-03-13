El proyecto consta de una carpeta src con todos los archivos de código fuente, una carpeta recursos con los ficheros necesarios para la correcta ejecución del programa y un archivo Makefile para compilar y ejecutar los procesos fácilmente.

- Para compilar el proyecto simplemente escribimos `make`. Se crearan dos nuevos directorios: obj/ que contiene los archivos .o y exec/ que contiene los ejecutables del proyecto.
- Para ejecutar el programa escribimos en la terminal `make solution`.

Al ejecutar el programa se creará un directorio estudiantes donde se crearan las carpetas de cada estudiante con su modelo de examen y su nota necesaria. También se creará un directorio backup donde el proceso demonio irá haciendo copias de seguridad periodicamente cada minuto. Además se creará un archivo log.txt con la información sobre las distintas tareas realizadas por los procesos.

Nota: hay que tener en cuenta que cada vez que se ejecute el programa con `make solution` se creará un proceso demonio en segundo plano que trabajará de forma indefinida. En el caso de querer terminar este proceso debemos escribir en la terminal `kill -15 <pid>` siendo pid el identificador del proceso del demonio. Para conocer el pid del demonio podemos escribir en la terminal `ps -axl`. Esto mostrará todos los procesos activos y sus pids entre otros. 
