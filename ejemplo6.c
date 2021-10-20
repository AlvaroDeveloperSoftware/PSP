#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//ABUELO-HIJO-NIETO
int main()
{
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;

    //Soy el  Abuelo, se crea el Hijo
    pid = fork(); 
    //Ha ocurrido un error
    if (pid == -1) 
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }

    //Nos encontramos en Proceso hijo, una vez estamos dentro del proceso hijo tenemos algunas situaciones de ejecución:
    if (pid == 0)
    {
        {
            //El hijo crea al nieto (es decir el padre del hijo creado)
            pid2 = fork();
            //Se evaluan los casos posibles:
            switch (pid2)
            {

            case -1:
                printf("No se ha podido crear el proceso hijo en el HIJO...");
                exit(-1);
                break;
                // proceso hijo
            case 0:
                printf("\t\tSoy el proceso NIETO %d; Mi padre es = %d \n", getpid(), getppid());
                break;
            default:
                // proceso padre
                Hijo2_pid = wait(NULL);
                printf("\tSoy el proceso HIJO %d, Mi padre es: %d.\n",
                       getpid(), getppid());
                printf("\tMi hijo: %d terminó.\n", Hijo2_pid);
            }
            //Nos encontramos en Proceso padre
        }else{
            //espera la finalización del proceso hijo
            Hijo_pid = wait(NULL);
            printf("Soy el proceso ABUELO: %d, Mi HIJO: %d terminó.\n", getpid(), pid);
        }
        exit(0);
    }

/*Caso ejecución de manera óptima:
    En la linea 10 se crea el hijo (la copia) con el metodo fork(),
    en el caso óptimo este proceso hijo, se evalúa en la linea 19 si se ha realizado la creación de él mismo
    por su padre (abuelo), después se crea el nieto (hijo del padre en la jerarquia), se evalúa entonces
    si se ha podido crear el nuevo proceso hijo (nieto del abuelo), si el caso es óptimo (linea 33), será el caso 0, ya que
    ya que el 0 indica que la creación de un hijo es realizada con exito, por lo que en la línea 34 devolverá el propio
    identificador del nieto y el de su padre.
    Si se trata del proceso padre (linea 41), el proceso hijo quedará en pausa, para reconocer que su padre es el que es mediante
    los metodos getpid(para proceso hijo, que es nieto) y getppid(para proceso padre, el padre en la jerarquia). 
   
    Por último entre la línea 44 y 47, tendremos al proceso padre (abuelo) que esperará que su proceso hijo acabe su ejecución, 
    para ello en la linea 46 entra en estado de pausa, una vez que ha acabado su proceso hijo, mostrará en la linea 47 el resultado
    indicando el PID del proceso hijo con el metodo getpid() y el PID del proceso abuelo con la variable pid, que es la variable que
    ha iniciado toda la jerarquía de los procesos. Evidentemente una vez

    En el caso negativo, primero se comprobará que el abuelo ha creado a su hijo (linea 13), si no es posible, directamente
    acabará en la línea 49 saliendo del programa.
    También en el caso negativo, una vez se ha comprobado que el padre existe, el padre crea un proceso hijo (nieto del abuelo), 
    una vez lo ha creado, si no se ha conseguido crea la copia del proceso hijo con fork() (caso -1) (linea 29), devolverá un error indicando
    que no se ha creado la copia del proceso hijo.
*/