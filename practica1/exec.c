/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc exec.c
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		execl("/bin/cat", "cat", "./exec.c", 0);
	}
	else{
		printf("Soy exec.c\n");
	}
	return 0;
}
