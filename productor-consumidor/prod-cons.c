#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define MAX_PROD 100

int sem;

void wait(int semid, int num_sem){
	struct sembuf sops;
	sops.sem_op = -1;
	sops.sem_num = num_sem;
	sops.sem_flg = 0;
	if(semop(semid, &sops, 1) == -1){
		puts("Error en wait");
		exit(-1);
	}
}

void signal(int semid, int num_sem){
	struct sembuf sops;
	sops.sem_op = 1;
	sops.sem_num = num_sem;
	sops.sem_flg = 0;
	if(semop(semid, &sops, 1) == -1){
		puts("Error en signal");
		exit(-1);
	}
}

void write_char(char c, char file[]){
	/* printf("file: %s\n", file); */
	char buffer[1];
	buffer[0] = c;
	/* wait(sem, 0); */
		int fd = open(file, O_WRONLY);
	while(1){
		int len = write(fd, buffer, 1);
		printf("Escribió: %d\n", len);
		if(len == 1) break;
		puts("failed to write");
	}
		close(fd);
	/* signal(sem, 0); */
}

char read_char(char file[]){
	/* printf("file: %s\n", file); */
	char buffer[1];
	/* wait(sem, 0); */
		int fd = open(file, O_RDONLY);
	while(1){
		int len = read(fd, buffer, 1);
		printf("Leyó: %d\n", len);
		if(len == 1) break;
		puts("failed to read");
	}
		close(fd);
	/* signal(sem, 0); */
	return buffer[0];
}

void produce(char c, char pipe_name[]){
	int i = 0;
	while(i < MAX_PROD){
		printf("productor %d produciendo %c, quedan: %d\n", getpid(), c, MAX_PROD - i);
		write_char(c, pipe_name);
		i++;
	}
}

void consume(char pipe_name[]){
	int bucket[30];
	int i;
	for(i = 0; i < 26; i++)
		bucket[i] = 0;
	while(1){
		puts("consumiendo");
		char c = read_char(pipe_name);
		bucket[c - 'a']++;
		puts("bucket");
		for(i = 0; i < 26; i++)
			printf("%c: %d, ", i + 'a', bucket[i]);
		puts("");
	}
}

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Se necesita especificar número de productores y consumidores\n");
		return 0;
	}

	char pipe_name[] = "./pipe";
	int num_prods = atoi(argv[1]);
	int num_cons = atoi(argv[2]);
	printf("Ejecutando con %d productores y %d consumidores\n", num_prods, num_cons);
	int i;

	sem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0700);
	if(sem < 0){
		puts("Error al crear semaforo");
		return -1;
	}
	if(semctl(sem, 0, SETVAL, 1) < 0){
		puts("Error al iniciar semaforo");
		return -1;
	}

	pid_t pid;
	if(mkfifo(pipe_name, 0666) != 0){
		printf("Error creando pipe, ¿posiblemente ya existe?\n");
	}
	for(i = 0; i < num_prods; i++){
		pid = fork();
		if(pid == -1){
			printf("Error creando el productor: %d\n", i);
		}
		else if(pid == 0){
			produce(i % 26 + 'a', pipe_name);
			return 0;
		}
	}
	for(i = 0; i < num_cons; i++){
		pid = fork();
		if(pid == -1){
			printf("Error creando el consumidor: %d\n", i);
		}
		else if(pid == 0){
			consume(pipe_name);
			return 0;
		}
	}
	while(1);
	return 0;
}
