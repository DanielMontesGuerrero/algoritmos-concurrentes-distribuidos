/*
 * Alumno: Daniel Montes Guerrero
 * Ejecutar: gcc hilos.c -lpthread && ./a.out
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *func(void *arg){
	printf("Soy un hilo\n");
}

int main(){
	int i;
	for(i = 0; ; i++){
		printf("Crando hilo %d\n", i);
		pthread_t h;
		if(pthread_create(&h, NULL, func, NULL) != 0)
			break;
	}
	return 0;
}
