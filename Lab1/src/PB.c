/***************************************************************************************
La tarea del proceso PB es copiar en cada directorio de estudiante el modelo de examen
que le corresponde.
***************************************************************************************/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define RUTA_CARPETA "./estudiantes"
#define RUTA_FICHERO "./recursos/estudiantes_p1.txt"
#define RUTA_MODELO "./recursos/MODELO"

int main()
{
    char *linea = NULL;
    char *dni;
    char *modelo;
    char path_copia[100];
    char path_modelo[100];
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen(RUTA_FICHERO, "r");

    if (!fp)
    {
        fprintf(stderr, "Error abriendo el fichero %s: %s.\n", RUTA_FICHERO, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        modelo = strtok(NULL, " ");
        sprintf(path_copia, "%s/%s/examen%s.pdf", RUTA_CARPETA, dni, modelo);
        sprintf(path_modelo, "%s%s.pdf", RUTA_MODELO, modelo);

        link(path_modelo, path_copia); // creamos un enlace duro al archivo original
    }

    fclose(fp);
    return 0;
}