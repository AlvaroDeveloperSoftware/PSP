#include <stdio.h>
#include <stdlib.h>

void main(){
	printf("Llamando a varios comandos desde la función system()\n");
    printf("Contenido del directorio actual\n");
    system("ls -l");
    printf("Enviando el contenido del directorio actual a un fichero de texto \n");
    system("ls -l > salida.txt");
    printf("Se ha creado el fichero salida.txt\n");
    printf("Se abre el fichero salida.txt con gedit\n");
    //Se añade a system para abrir el fichero de texto
    //con la salida del comando ls
    system("gedit salida.txt");
    printf("\nProbando un comando erróneo: %d", 
    system("cop"));
    printf("\nPrograma finalizado\n");
}