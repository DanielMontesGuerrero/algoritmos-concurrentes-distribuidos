/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc pipes.c
 */

#include<stdio.h>

int main(){
	int i, error, fd[2];
	char *buf = "a";
	error = pipe(fd);
	if(error < 0){
		printf("Error wn la creacion del pipe\n");
		return 1;
	}
	for(i = 1; ;i++){
		write(fd[1], buf, 1);
		printf("%d ", i);
		fflush(stdout);
	}
	return 0;
}
