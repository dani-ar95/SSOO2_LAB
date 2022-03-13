/***************************************************************************************
La tarea del proceso PA es la de crear un directorio por cada estudiante. El nombre del
directorio se corresponde con el DNI del estudiante 
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define CARPETA "./estudiantes"
#define FICHERO "./estudiantes_p1.txt"
#define PERMISOS 0777

int main()
{

    char *linea = NULL;
    char *dni;
    char path[1000];
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen(FICHERO, "r");

    if (!fp)
    {
        fprintf(stderr, "Error abriendo el fichero %s: %s.\n", FICHERO, strerror(errno));
        exit(EXIT_FAILURE);
    }

    mkdir(CARPETA, PERMISOS); // creamos una carpeta para guardar todos los directorios

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        sprintf(path, "%s/%s", CARPETA, dni);
        mkdir(path, PERMISOS);
    }

    fclose(fp);
    return 0;
}