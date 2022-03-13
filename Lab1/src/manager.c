/***************************************************************************************
El proceso manager se dedica a crear y coordinar al resto de procesos,
además de mantener un archivo log.txt que registra la finalización de todas las tareas.
***************************************************************************************/
#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define READ 0
#define WRITE 1

#define ERROR -1

#define MAX_HIJOS 5
#define ID_PA 0
#define ID_PB 1
#define ID_PC 2
#define ID_PD 3
#define ID_DEMON 4

#define RUTA_LOG "./log.txt"

pid_t gbl_lista_pids[MAX_HIJOS]; // lista global con todos los pids de los procesos creados

void signal_handler();
void install_signal_handler();
void print_log(char *modo, char *mensaje);
void crear_proceso(char *nombre, int ID);

int main()
{
    pid_t pidC;
    pid_t codigo;

    int estado;
    char nota_media[100];

    char tuberia[100];
    int pipeHP[2];

    install_signal_handler(); // hacemos que el proceso pueda capturar señales SIGINT

    print_log("w", "******* Log del sistema ********\n");

    // Proceso PA
    crear_proceso("PA", ID_PA);
    wait(&estado);
    gbl_lista_pids[ID_PA] = 0; // indicamos que PA ha finalizado
    print_log("a", "Directorios creados\n");

    // Procesos PB y PC
    // PB
    crear_proceso("PB", ID_PB);

    // PC
    pipe(pipeHP); // creamos una tuberia para que PC pueda mandar la nota media al manager
    sprintf(tuberia, "%d", pipeHP[WRITE]);

    if ((pidC = fork()) == ERROR)
    {
        fprintf(stderr, "Error creando el proceso PC: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pidC == 0)
    {
        close(pipeHP[READ]);
        execl("./exec/PC", tuberia, NULL); // mandamos a PC el descriptor de la tuberia mediante execl
        fprintf(stderr, "Error ejecutando el proceso PC: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    gbl_lista_pids[ID_PC] = pidC;

    close(pipeHP[WRITE]);
    read(pipeHP[READ], nota_media, sizeof(nota_media)); // recibimos la nota media de parte de PC

    for (int i = 0; i < 2; i++)
    {
        codigo = wait(&estado); // esperamos a PB o PC

        if (codigo == pidC)
        {
            gbl_lista_pids[ID_PC] = 0; // indicamos que PC ha finalizado
            char mensaje[1000];
            sprintf(mensaje, "La nota media de la clase es: %s\n", nota_media);
            print_log("a", "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
            print_log("a", mensaje);
        }
        else
        {
            gbl_lista_pids[ID_PB] = 0; // indicamos que PB ha finalizado
            print_log("a", "Copia de modelos de examen, finalizada.\n");
        }
    }

    print_log("a", "FIN DE PROGRAMA");

    return 0;
}

// Función manejadora de la interrupción voluntaria CTRL+C
void signal_handler()
{
    int estado;

    // terminar procesos activos
    for (int i = 0; i < MAX_HIJOS; i++)
    {
        if (gbl_lista_pids[i] != 0)
        {
            if (kill(gbl_lista_pids[i], SIGINT) == 1)
            {
                fprintf(stderr, "Error intentando matar al proceso con pid %d: %s.\n", gbl_lista_pids[i], strerror(errno));
            }
        }
    }

    // PD
    crear_proceso("PD", ID_PD);
    print_log("a", "Interrupción voluntaria CTRL+C");
    wait(&estado);
    exit(EXIT_SUCCESS);
}

// Función para que el proceso manager pueda capturar señales SIGINT
void install_signal_handler()
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        fprintf(stderr, "Error instalando el manejador de señales: %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Función para escribir en el archivo log.txt
void print_log(char *modo, char *mensaje)
{
    FILE *log = fopen(RUTA_LOG, modo);
    fputs(mensaje, log);
    fclose(log);
}

// Función para crear procesos hijos
void crear_proceso(char *nombre, int ID)
{
    pid_t pid;
    char *const parmList[] = {NULL};
    char *const envParms[] = {NULL};
    char ruta_ejecutable[100];

    sprintf(ruta_ejecutable, "./exec/%s", nombre);

    if ((pid = fork()) == ERROR)
    {
        fprintf(stderr, "Error creando el proceso %s: %s.\n", nombre, strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        execve(ruta_ejecutable, parmList, envParms);
        fprintf(stderr, "Error ejecutando el proceso %s: %s.\n", nombre, strerror(errno));
        exit(EXIT_FAILURE);
    }
    gbl_lista_pids[ID] = pid; // añadimos el pid del proceso creado a la lista global de pids
}