#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    char buffer[10];
    pid_t pid;

    pipe(fd); //1

    pid = fork(); //2

    switch (pid)
    {
    case -1: //ERROR
        printf("NO SE HA PODIDO CREAR HIJO...");
        exit(-1);
        break;

    case 0:
        //HIJO
        printf("El proceso hijo lee en el pipe...\n");
        //El proceso hijo lee el buffer escrito por el padre.
        read(fd[0], buffer, 10); //4
        //Muestra por pantalla el mensaje con el buffer.
        printf("\tMensaje leido: %s\n", buffer);
        break;

    default:
        //PADRE
        printf("El proceso padre escribe en el pipe...\n");
        //El padre escribe en el buffer.
        write(fd[1], "Hola hijo", 10);
        //El padre espera a que lo lea el hijo.
        wait(NULL); //3
        break;
    }
}
