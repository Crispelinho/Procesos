#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <wait.h>

int shm_idptr, i, num;

typedef struct Ed {
    int id_luz;
    int tiempo;
    int estado;
    int sw;
    int salir;
}
Ed;

int main() {
    printf("--------------\n");

    Ed *ptr;

    shm_idptr = shmget(IPC_PRIVATE, sizeof(Ed), IPC_CREAT | 0666);
    ptr = shmat(shm_idptr, NULL, 0);

    printf("Ingrese el numero de luces: ");
    scanf("%d", &num);

    ptr->id_luz = -1;
    ptr->tiempo = 0;
    ptr->estado = -1;
    ptr->salir = 0;
    ptr->sw = 0;

    pid_t h[num];
    pid_t padre=getpid();

    printf("Soy el proceso %d \n", getpid());

    for (i = 0; i < num; i++) {
        h[i] = fork();
        
        if (h[i] == 0) {
        	sleep(10);
        	while(ptr->sw==1){

        		while(i == ptr->id_luz){

	            	printf("Soy la compuerta %d \n", i);

	            	printf("Ingrese el tiempo: ");
	            	scanf("%d", & ptr->tiempo);

	            	printf("Ingrese el estado del led: ");
	            	scanf("%d", & ptr->estado);

	            	printf("\n");

	            	ptr->sw =0;
	            	break;
            	}

        	}

        	while(i != ptr->id_luz){}
            
            printf("ptr->sw %d\n", ptr->sw);
            printf("Cerrando hijo %d\n", i);
            break;

        }
        /*else
        {
        	wait(NULL);
        }*/
	}

	if(padre==getpid()){

		printf("Soy el PAPA\n");
		while(ptr->sw == 0){
			printf("Ingrese al hijo que quiere ir:\n");
			scanf("%d",&ptr->id_luz);
			if (ptr->id_luz<=num)
			{
				ptr->sw = 1;
				sleep(100);
			}
			else
				{break;}
		}
		
	}


	return 0;
	printf("FIN DEL PROGRAMA \n");
}



