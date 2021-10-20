#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid_hijo, pid;
	pid = fork();

	//se ha producido algún error
	if(pid==-1){ 
		printf("Se ha producido un error y no se ha podido crear el proceso hijo\n");
		exit(pid);
	}
	//no hay error, y como el valor es 0 estamos en el proceso hijo
	if(pid==0){ 
		printf("Estamos en el proceso hijo\n");
		printf("El PID del proceso padre es %d\n", 
		getppid());
	//estamos en proceso padre, el valor de pid>0
		printf("Mi PID es el %d\n", getpid());
	}else{
	//bloquea al procesa padre y espera al proceso hijo
		pid_hijo = wait(NULL);

		printf("Estamos en el proceso padre, mi PID es %d\n el PID de mi padre es %d\n",
			getpid(),getppid());
		printf("Mi proceso hijo %d ha terminado\n",pid);
	}
	exit(0);
}
