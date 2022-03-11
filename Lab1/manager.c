#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

void signal_handler();
void install_signal_handler();

int main()
{
    pid_t pidA;
    pid_t pidB;
    pid_t pidC;
    pid_t pidD;
    pid_t codigo;

    char *const parmList[] = {NULL};
    char *const envParms[] = {NULL};

    int estado;
    char nota_media[100];

    char tuberia[80];
    int pipeHP[2];

    install_signal_handler();

    pipe(pipeHP);
    sprintf(tuberia, "%d", pipeHP[WRITE]);

    FILE *log = fopen("log.txt", "w");
    fprintf(log, "******* Log del sistema ********\n");

    if ((pidA = fork()) == -1)
    {
        fprintf(stderr, "Error creando el proceso PA: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pidA == 0)
    {
        execve("PA", parmList, envParms);
        fprintf(stderr, "Error ejecutando el proceso PA: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    codigo = wait(&estado);
    fprintf(log, "Directorios creados\n");

    sleep(3);

    if ((pidB = fork()) == -1)
    {
        fprintf(stderr, "Error creando el proceso PB: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pidB == 0)
    {
        execve("PB", parmList, envParms);
        fprintf(stderr, "Error ejecutando el proceso PB: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if ((pidC = fork()) == -1)
    {
        fprintf(stderr, "Error creando el proceso PC: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pidC == 0)
    {
        close(pipeHP[READ]);
        execl("PC", tuberia, NULL);
        fprintf(stderr, "Error ejecutando el proceso PC: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(pipeHP[WRITE]);
    read(pipeHP[READ], nota_media, sizeof(nota_media));

    for (int i = 0; i < 2; i++)
    {
        codigo = wait(&estado);

        if (codigo == pidB)
        {
            fprintf(log, "Copia de modelos de examen, finalizada.\n");
        }
        else
        {
            fprintf(log, "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
            fprintf(log, "La nota media de la clase es: %s\n", nota_media);
        }
    }

    fprintf(log, "FIN DE PROGRAMA");

    fclose(log);
    return 0;
}

void signal_handler()
{
    pid_t pidD;
    char *const parmList[] = {NULL};
    char *const envParms[] = {NULL};

    // terminar procesos activos

    if ((pidD = fork()) == -1)
    {
        fprintf(stderr, "Error creando el proceso PD: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pidD == 0)
    {
        execve("PD", parmList, envParms);
        fprintf(stderr, "Error ejecutando el proceso PD: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    FILE *log = fopen("log.txt", "a");
    fprintf(log, "Interrupción voluntaria CTRL+C");
    fclose(log);
}

void install_signal_handler()
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        fprintf(stderr, "[MANAGER] Error installing signal handler: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}