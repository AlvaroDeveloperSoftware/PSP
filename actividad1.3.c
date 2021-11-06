#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
//ABUELO-HIJO-NIETO
int main()
{
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;

    int fd1[2]; //padre-hijo
    int fd2[2]; //hijo-padre

    char saludoAbuelo[] = "Saludos del Abuelo.\0";
    char saludoPadre[] = "Saludos del Padre..\0";
    char saludoHijo[] = "Saludos del Hijo...\0";
    char saludoNieto[] = "Saludos del Nieto..\0";

    char buffer[80] = "";

    pipe(fd1); //pipe para comunicación de padre a hijo
    pipe(fd2); //pipe para comunicación de hijo a padre

    pid = fork(); //Soy el  Abuelo, creo a Hijo

    if (pid == -1) //Ha ocurrido un error
    {
        printf("No se ha podido crear el proceso hijo...");
        exit(-1);
    }

    if (pid == 0) //Nos encontramos en Proceso hijo  {
    {
        pid2 = fork(); //Soy el Hijo, creo a Nieto
        switch (pid2)
        {
        case -1: // error
         printf("No se ha podido crear el proceso hijo en el HIJO...");
         exit(-1); 
         break;        
      case 0:    // proceso hijo 
            //NIETO RECIBE DEL ABUELO
            close(fd2[1]);//cierra el descriptor de entrada
            read(fd2[0], buffer, sizeof(buffer)); //leo el pipe            
            printf("\t\tNIETO RECIBE mensaje de su padre por parte del ABUELO: %s\n",buffer);      
           
            //NIETO ENVIA         
            printf("\t\tNIETO ENVIA MENSAJE a su abuelo...\n");    
            close(fd1[0]);
            write(fd1[1], saludoNieto, strlen(saludoNieto)); 
           
        break;
      default:   // proceso padre 
         //HIJO RECIBE
         close(fd1[1]);//cierra el descriptor de entrada
         read(fd1[0], buffer, sizeof(buffer)); //leo el pipe            
         printf("\tPADRE recibe mensaje de ABUELO: %s\n",buffer);   

         //HIJO ENVIA a su hijo
         close(fd2[0]);
         write(fd2[1], saludoAbuelo, strlen(saludoAbuelo));//escribo en pipe 
        // Hijo2_pid=wait(NULL); //espero al hijo    
         
         //RECIBE de su hijo
         close(fd1[1]);//cierra el descriptor de entrada
         read(fd1[0], buffer, sizeof(buffer)); //leo el pipe            
         printf("\tPADRE recibe mensaje de su hijo para el abuelo: %s\n",buffer);   

         //HIJO ENVIA a su PADRE
         printf("\tPADRE ENVIA MENSAJE al abuelo por parte del NIETO: %s \n",buffer);   
         close(fd2[0]);
         write(fd2[1], saludoNieto, strlen(saludoNieto));//escribo en pipe
        }
    }
    else //Nos encontramos en Proceso padre
    {
        //PADRE ENVIA
        printf("ABUELO ENVIA EL MENSAJE QUE SERA PARA SU NIETO...\n");
        close(fd1[0]);
        write(fd1[1], saludoAbuelo, strlen(saludoAbuelo)); //escribo en pipe
            Hijo_pid = wait(NULL); //espera la finalización del proceso hijo

            //PADRE RECIBE
            close(fd2[1]);                    //cierra el descriptor de entrada
        read(fd2[0], buffer, sizeof(buffer)); //leo el pipe
        printf("El ABUELO RECIBE MENSAJE del HIJO: %s\n", buffer);
    }
    exit(0);
}
