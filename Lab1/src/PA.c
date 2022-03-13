/***************************************************************************************
La tarea del proceso PA es la de crear un directorio por cada estudiante. El nombre del
directorio se corresponde con el DNI del estudiante
***************************************************************************************/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define RUTA_CARPETA "./estudiantes"
#define RUTA_FICHERO "./recursos/estudiantes_p1.txt"
#define PERMISOS 0777

int main()
{

    char *linea = NULL;
    char *dni;
    char path[1000];
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen(RUTA_FICHERO, "r");

    if (!fp)
    {
        fprintf(stderr, "Error abriendo el fichero %s: %s.\n", RUTA_FICHERO, strerror(errno));
        exit(EXIT_FAILURE);
    }

    mkdir(RUTA_CARPETA, PERMISOS); // creamos una carpeta para guardar todos los directorios

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        sprintf(path, "%s/%s", RUTA_CARPETA, dni);
        mkdir(path, PERMISOS);
    }

    fclose(fp);
    return 0;
}