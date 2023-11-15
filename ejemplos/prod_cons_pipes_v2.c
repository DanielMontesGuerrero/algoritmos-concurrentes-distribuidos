/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc prod_cons_pipes_v2.c -o prod_cons_pipes_v2
 */

#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<string.h>

int del_cons, del_prod;
int tuberia[2];

void productor(){
	printf("Productor: %d", getpid());
	char* buff = (char*)malloc(100 * sizeof(char));
	int cnt = 0;
	while(1){
		sprintf(buff, "%d", cnt);
		sleep(del_prod);

		int tam = strlen(buff);
		printf("A punto de escribir: %d\n", tam);
		write(tuberia[1], buff, tam);
		printf("Escribio: %d\n", cnt);

		cnt++;
		fflush(stdout);
	}
}

void consumidor(){
	printf("Consumidor: %d", getpid());
	char* buff = (char*)malloc(100 * sizeof(char));
	while(1){
		int bytes = read(tuberia[0], buff, 100);
		printf("\t\t\tLeyo: %s, %d\n", buff, bytes);
		sleep(del_cons);
		fflush(stdout);
	}
}

int main(int argc, char** argv){
	del_cons = 3;
	del_prod = 1;
	if(argc >= 3){
		del_prod = atoi(argv[1]);
		del_cons = atoi(argv[2]);
	}
	printf("Delays: %d %d\n", del_prod, del_cons);
	pid_t pid;
	pipe(tuberia);
	pid = fork();
	if(pid < 0){
		puts("Error");
	}
	else if(pid == 0){
		productor();
	}
	pid = fork();
	if(pid < 0){
		puts("Error");
	}
	else if(pid == 0){
		consumidor();
	}
	printf("Padre: %d", getpid());
}
