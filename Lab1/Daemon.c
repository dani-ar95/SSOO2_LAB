/***************************************************************************************
La tarea del demonio es hacer una copia de seguridad con todos los archivos de los
estudiantes cada minuto
Nota: es un proceso que se ejecuta en segundo plano continuamente. Para terminar este
proceso se debe ejecutar el comando "kill -15 <pid>". Para saber cual es el pid del
proceso demonio se puede consultar con el comando "ps -axl".
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <signal.h>

#define CARPETA "./estudiantes"
#define BACKUP "./backup"

int main()
{
    pid_t pid;
    int x_fd;
    char comando[100];

    // Paso 1: Ejecutamos el proceso en segundo plano
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    // Paso 2: Creamos una nueva sesión
    if (setsid() < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Paso 3: Ignoramos ciertas señales
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // Paso 4: Prohibimos que el proceso vuelva a abrir el terminal de control
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    // Paso 5: Establecemos una máscara al archivo del proceso
    umask(077);

    // Paso 6: Cerramos los descriptores de archivos que no son necesarios
    for (x_fd = sysconf(_SC_OPEN_MAX); x_fd >= 0; x_fd--)
    {
        close(x_fd);
    }

    // Paso 8: Tarea del demonio
    sprintf(comando, "cp -r %s %s", CARPETA, BACKUP);
    mkdir("./backup", 0777);
    while (1)
    {
        sleep(60);
        system(comando);
    }
}