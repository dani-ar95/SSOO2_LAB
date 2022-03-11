#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{

    char *linea = NULL;
    char *dni;
    char *modelo;
    char path_copia[100];
    char path_modelo[100];
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen("estudiantes_p1.txt", "r");

    if (!fp)
    {
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        modelo = strtok(NULL, " ");
        sprintf(path_copia, "./estudiantes/%s/examen%s.pdf", dni, modelo);
        sprintf(path_modelo, "./MODELO%s.pdf", modelo);

        link(path_modelo, path_copia);
    }

    fclose(fp);
    return 0;
}