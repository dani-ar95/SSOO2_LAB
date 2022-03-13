/***************************************************************************************
La tarea del proceso PD es eliminar todos los directorios y archivos asociados a los
estudiantes.
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define CARPETA "./estudiantes"

int main()
{
    DIR *carpeta;
    DIR *dni;
    struct dirent *dit; // en este caso usamos la estructura dirent para guardar y acceder al nombre de los elementos que contiene un directorio mediante el campo d_name
    char ruta_dni[1000];
    char nombre_archivo[1000];

    if ((carpeta = opendir(CARPETA)) == NULL) // abrimos la carpeta estudiantes
    {
        fprintf(stderr, "Error abriendo el directorio %s: %s.\n", CARPETA, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((dit = readdir(carpeta)) != NULL) // iteramos sobre todos los elementos que hay en la carpeta estudiantes
    {
        if (strcmp(dit->d_name, ".") && strcmp(dit->d_name, "..")) // readdir devuelve tambien el directorio actual y anterior, eso no nos interesa
        {
            sprintf(ruta_dni, "%s/%s/", CARPETA, dit->d_name);
            if ((dni = opendir(ruta_dni)) == NULL) // abrimos la carpeta del dni correspondiente
            {
                fprintf(stderr, "Error abriendo el directorio %s: %s.\n", ruta_dni, strerror(errno));
                exit(EXIT_FAILURE);
            }
            while ((dit = readdir(dni)) != NULL) // iteramos sobre los elementos que hay en la carpeta del dni actual
            {
                if (strcmp(dit->d_name, ".") && strcmp(dit->d_name, ".."))
                {
                    sprintf(nombre_archivo, "%s", ruta_dni);
                    strcat(nombre_archivo, dit->d_name);
                    remove(nombre_archivo); // eliminamos los ficheros
                }
            }
            if (closedir(dni) == -1) // cerramos la carpeta del dni actual
            {
                fprintf(stderr, "Error cerrando el directorio %s: %s.\n", ruta_dni, strerror(errno));
                exit(EXIT_FAILURE);
            }
            rmdir(ruta_dni); // borramos la carpeta vacia del dni
        }
    }

    if (closedir(carpeta) == -1) // cerramos la carpeta estudiantes
    {
        fprintf(stderr, "Error cerrando el directorio %s: %s.\n", CARPETA, strerror(errno));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}