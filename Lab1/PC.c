#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    char *linea = NULL;
    char *dni;
    char *modelo;
    char *nota;
    char path[1000];
    size_t len = 0;
    ssize_t nread;

    float suma_notas = 0;
    int num_estudiantes = 0;

    char nota_media[100];

    FILE *fp = fopen("estudiantes_p1.txt", "r");

    if (!fp)
    {
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        modelo = strtok(NULL, " ");
        nota = strtok(NULL, " ");
        sprintf(path, "./estudiantes/%s/nota_necesaria.txt", dni);
        FILE *txt = fopen(path, "w");
        fprintf(txt, "La nota que debes obtener en este nuevo examen para superar la prueba es %d", 10 - atoi(nota));
        fclose(txt);
        suma_notas += atoi(nota);
        num_estudiantes += 1;
    }

    sprintf(nota_media, "%.2f", suma_notas / num_estudiantes);

    write(atoi(argv[0]), nota_media, strlen(nota_media) + 1);
    fclose(fp);
    return 0;
}