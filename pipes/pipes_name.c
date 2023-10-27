/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc pipes_name.c
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

#define CHILD 0
#define ERROR -1

int main(){
	const char* pipeName = "./fifoChannel";
	mkfifo(pipeName, 0666);
	int fd = open(pipeName, O_CREAT | O_WRONLY);
	if(fd < 0) return -1;
	return 0;
}
