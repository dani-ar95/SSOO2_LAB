#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CARPETA "./estudiantes"

int main()
{

    char *linea = NULL;
    char *dni;
    char path[1000];
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen("estudiantes_p1.txt", "r");

    if (!fp)
    {
        exit(EXIT_FAILURE);
    }

    mkdir(CARPETA, 0777);

    while ((nread = getline(&linea, &len, fp)) != -1)
    {
        dni = strtok(linea, " ");
        sprintf(path, "%s/%s", CARPETA, dni);
        mkdir(path, 0777);
    }

    fclose(fp);
    return 0;
}