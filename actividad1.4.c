#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
/* gestión de señales en proceso padre       */
void gestion_padre(int signal)
{
    printf("Padre recibe señal..%d\n", signal);
}

int main()
{
    //Se declaran los identificadores tanto del proceso padre
    //como del hijo
    pid_t pid_padre, pid_hijo;
    //Se obtiene el identificador del proceso padre
    pid_padre = getpid();
    //Creamos hijo
    pid_hijo = fork();

    switch (pid_hijo)
    {
    /* En caso de que no se pudiera crear el proceso hijo
    mostrará un error y saldrá del programa.
    */
    case -1:
        printf("Error al crear el proceso hijo...\n");
        exit(-1);
    /* En caso que si se pueda crear el hijo el proceso hijo
     estará un segundo dormido y a continuación se ejecutará 
     la primera señal SIGUSR1, después bajará al default (padre)
     y con el metodo signal relacionará la señal con el manejador
     de señales del proceso padre, y esto lo hará con cada señal 
     que envíe el hijo. Por último enviará la señal de matar el proceso
     padre con SIGKILL.
    */
    case 0:
        sleep(1);
        kill(pid_padre, SIGUSR1);
        sleep(1);
        kill(pid_padre, SIGUSR1);
        sleep(1);
        kill(pid_padre, SIGUSR1);
        sleep(1);
        kill(pid_padre, SIGKILL);

        break;
    /* Caso por defecto (padre) en el que se hará uso del metodo
    signal como se ha explicado antes y con un bucle while infinito
    mostrará por consola las señales.
    */
    default:
        signal(SIGUSR1, gestion_padre);
        while (1)
        {
        }
        break;
    }
    return 0;
}
