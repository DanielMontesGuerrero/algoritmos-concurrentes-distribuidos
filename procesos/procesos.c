/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc procesos.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
	pid_t pid, pid_p, pid_h, pid_pp;
	pid = fork();
	switch(pid){
		case -1:
			printf("Error\n");
			break;
		case 0:
			printf("Hijo\n");
			pid_p = getpid();
			printf("H %d\n", pid_p);
			fflush(stdout);
			sleep(2);
			printf("hijo despierta\n");
			//while(1);
			break;
		default:
			printf("I am your father\n");
			pid_h = getpid();
			pid_pp = getppid();
			printf("P %d, %d\n", pid_p, pid_pp);
			fflush(stdout);
			sleep(5);
			printf("padre despierta\n");
			//while(1);
			break;
	}
	return 0;
}
