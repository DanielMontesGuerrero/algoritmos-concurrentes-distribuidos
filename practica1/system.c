/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc system.c
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		system("cat system.c");
	}
	else{
		printf("Soy system.c\n");
	}
	return 0;
}
