/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc procesos.c
 */

#include<stdio.h>
#include<unistdio.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("Soy el hijo %d con padre %d\n", getpid(), getppid());
	}
	else{
		printf("Soy el padre %d\n", getpid());
	}
	return 0;
}
