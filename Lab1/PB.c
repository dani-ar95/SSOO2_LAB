/***************************************************************************************
La tarea del proceso PB es copiar en cada directorio de estudiante el modelo de examen
que le corresponde.
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define CARPETA "./estudiantes"
#define FICHERO "./estudiantes_p1.txt"

int main()
{
    char *linea = NULL;
    char *dni;
    char *modelo;
    char path_copia[100];
    char path_modelo[100];
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen(FICHERO, "r");

    if (!fp)
    {
        fprintf(stderr, "Error abriendo el fichero %s: %s.\n", FICHERO, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        modelo = strtok(NULL, " ");
        sprintf(path_copia, "%s/%s/examen%s.pdf", CARPETA, dni, modelo);
        sprintf(path_modelo, "./MODELO%s.pdf", modelo);

        link(path_modelo, path_copia); //creamos un enlace duro al archivo original
    }

    fclose(fp);
    return 0;
}