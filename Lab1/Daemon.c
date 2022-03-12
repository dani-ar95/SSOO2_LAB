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

    // Step 1
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    // Step 2
    if (setsid() < 0)
    {
        exit(EXIT_FAILURE);
    }

    // Step 3
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // Step 4
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    printf("Daemon pid = %d\n", getpid());

    // Step 5
    umask(077);

    // Step 6
    // chdir("/");

    // Step 7
    for (x_fd = sysconf(_SC_OPEN_MAX); x_fd >= 0; x_fd--)
    {
        close(x_fd);
    }

    // Step 8
    sprintf(comando, "cp -r %s %s", CARPETA, BACKUP);
    mkdir("./backup", 0777);
    while (1)
    {
        sleep(60);
        system(comando);
    }
}