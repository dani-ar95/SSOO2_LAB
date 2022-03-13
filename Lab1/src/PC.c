/***************************************************************************************
La tarea del proceso PC es crear un archivo txt en cada directorio de estudiante con la
nota que necesita sacar ese estudiante en el siguiente examen para aprobar.
Tambien calcula la nota media de todos los alumnos y se la envia al manager.
***************************************************************************************/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define RUTA_CARPETA "./estudiantes"
#define RUTA_FICHERO "./recursos/estudiantes_p1.txt"

int main(int argc, char *argv[])
{

    char *linea = NULL;
    char *dni;
    char *nota;
    char path[1000];
    size_t len = 0;
    ssize_t nread;

    float suma_notas = 0;
    int num_estudiantes = 0;
    char nota_media[100];

    FILE *fp = fopen(RUTA_FICHERO, "r");

    if (!fp)
    {
        fprintf(stderr, "Error abriendo el fichero %s: %s.\n", RUTA_FICHERO, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        strtok(NULL, " ");
        nota = strtok(NULL, " ");
        sprintf(path, "%s/%s/nota_necesaria.txt", RUTA_CARPETA, dni);

        FILE *txt = fopen(path, "w");
        fprintf(txt, "La nota que debes obtener en este nuevo examen para superar la prueba es %d", 10 - atoi(nota));
        fclose(txt);

        suma_notas += atoi(nota);
        num_estudiantes += 1;
    }

    sprintf(nota_media, "%.2f", suma_notas / num_estudiantes); // calculamos la nota media

    write(atoi(argv[0]), nota_media, strlen(nota_media) + 1); // enviamos la nota media al manager
    fclose(fp);
    return 0;
}