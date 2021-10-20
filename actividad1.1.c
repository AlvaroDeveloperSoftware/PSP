#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    //Se declaran las variables necesarias
    int valor_entero = 10;
	pid_t pid_hijo, pid_padre=4;

    //Como bien dice el enunciado del ejercicio, hay que mostrar el valor del proceso padre
    //antes de crear el proceso hijo.
    printf("El identificador del padre es : %d\n", valor_entero);
    //Proceso hijo, con fork() se ha realizo una "copia" del proceso padre con sus mismos datos
    //, pero con distinta dirección de memoria.
    pid_hijo = fork();

    //Se comprueba que se haya creado el proceso hijo
    if(pid_hijo == -1){
        printf("No se ha podido crear el proceso hijo");
        exit(-1);
    }

    //Si se ha creado el proceso hijo, se restará 6 al valor entero que es 10, para obtener el pid del hijo, que será 4.
    if(pid_hijo == 0){
        pid_hijo= valor_entero-6;
        //Se muestra el proceso hijo
        printf("El proceso hijo muestra: %d\n", pid_hijo);

       
    //En el proceso padre, se mostrará la suma entre el proceso padre que es 4 como indica el enunciado más el valor entero
    //para obtener 14.
    }else{
        //Proceso padre, se pausa el proceso hijo para que se ejecute el proceso padre
        pid_hijo = wait(NULL);
         //Se muestra la variable modificada del proceso padre
        printf("La variable modificada quedaria así: %d\n", pid_padre+valor_entero);
    }
}