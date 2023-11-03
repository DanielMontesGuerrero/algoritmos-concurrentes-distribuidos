/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc prod-cons-pipes.c
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<semaphore.h>

#define MAX_PROD 10

sem_t *semp, *semc;

void write_char(char c, char file[]){
	/* printf("file: %s\n", file); */
	sem_wait(semp);
	char buffer[1];
	buffer[0] = c;
	int fd = open(file, O_WRONLY);
	int len = write(fd, buffer, sizeof(char));
	close(fd);
	sem_post(semp);
}

void read_chars(char file[], int* bucket){
	/* printf("file: %s\n", file); */
	sem_wait(semc);
	char buffer[MAX_PROD];
	int fd = open(file, O_RDONLY);
	int len = read(fd, buffer, sizeof(char) * MAX_PROD);
	/* printf("Leyó: %d %c\n", len, buffer[0]); */
	int i = 0;
	for(i = 0; i < len; i++){
		bucket[buffer[i] - 'a']++;
	}
	/* puts("failed to read"); */
	close(fd);
	sem_post(semc);
}

void produce(char c, char pipe_name[], int num_prd){
	int i;
	for(i = 0; i < MAX_PROD; i++){
		printf("productor %d produciendo %c, quedan: %d\n", num_prd, c, MAX_PROD - i);
		write_char(c, pipe_name);
	}
	printf("Termino %d produciendo %d\n", num_prd, i);
}

void consume(char pipe_name[], int num_cons){
	int bucket[30];
	int i, cnt = 1;
	for(i = 0; i < 26; i++)
		bucket[i] = 0;
	while(1){
		printf("Consumidor %d consumiendo %d\n", num_cons, cnt);
		cnt++;
		read_chars(pipe_name, bucket);
		printf("bucket del consumidor %d\n", num_cons);
		for(i = 0; i < 26; i++)
			printf("%c: %d, ", i + 'a', bucket[i]);
		puts("");
	}
}

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Uso ./prod-cons <num_productores> <num_consumidores>");
		return 0;
	}

	char pipe_name[] = "./pipe";
	int num_prods = atoi(argv[1]);
	int num_cons = atoi(argv[2]);
	printf("Ejecutando con %d productores y %d consumidores\n", num_prods, num_cons);
	int i;

	sem_unlink("semc");
	sem_unlink("semp");
	semp = sem_open("semp", O_CREAT | O_EXCL, 0644, 1);
	semc =sem_open("semc", O_CREAT | O_EXCL, 0644, 1);

	pid_t pid;
	if(mkfifo(pipe_name, 0600) != 0){
		printf("Error creando pipe, ¿posiblemente ya existe?\n");
	}
	for(i = 0; i < num_prods; i++){
		pid = fork();
		if(pid == -1){
			printf("Error creando el productor: %d\n", i);
		}
		else if(pid == 0){
			produce(i % 26 + 'a', pipe_name, i);
			return 0;
		}
	}
	for(i = 0; i < num_cons; i++){
		pid = fork();
		if(pid == -1){
			printf("Error creando el consumidor: %d\n", i);
		}
		else if(pid == 0){
			consume(pipe_name, i);
			return 0;
		}
	}
	while(1);
	return 0;
}
