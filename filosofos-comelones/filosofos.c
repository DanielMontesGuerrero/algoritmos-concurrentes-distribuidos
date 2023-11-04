/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc filosofos.c -lpthread
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<pthread.h>
#include<math.h>

#define BUFF_SIZE 200

int max(int a, int b){
	return a > b ? a : b;
}

int num_fil;
sem_t *sem_eating, **sem_forks;

void* eat(void* arg){
	int id = *((int*)arg);
	while(1){
		sem_wait(sem_eating);
		sem_wait(sem_forks[id]);
		printf("Filosofo: %d obtiene tenedor %d\n", id, id);
		sem_wait(sem_forks[(id + 1) % num_fil]);
		printf("Filosofo: %d obtiene tenedor %d\n", id, (id + 1) % num_fil);
		printf("Filosofo: %d empieza a comer\n", id);
		sleep(2);
		printf("Filosofo: %d termina de comer\n", id);
		sem_post(sem_eating);
		sem_post(sem_forks[id]);
		sem_post(sem_forks[(id + 1) % num_fil]);
		sleep(1);
	}
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("Uso: ./filosofos <num_filosofos>\n");
		return 1;
	}
	num_fil = atoi(argv[1]);
	int i = 0;
	sem_forks = (sem_t**)malloc(sizeof(sem_t*) * (num_fil));
	sem_unlink("sem_eating");
	sem_eating = sem_open("sem_eating", O_CREAT | O_EXCL, 0644, max(1, num_fil - 1));
	
	for(i = 0; i < num_fil; i++){
		char sem_name[BUFF_SIZE] = "sem_fork_";
		char num[BUFF_SIZE];
		snprintf(num, BUFF_SIZE, "%d", i);
		strcat(sem_name, num);
		printf("sem_name: %s\n", sem_name);
		sem_unlink(sem_name);
		sem_forks[i] = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
	}

	pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t) * num_fil);
	int* ids = (int*)malloc(sizeof(int) * num_fil);
	for(i = 0; i < num_fil; i++){
		ids[i] = i;
		if(pthread_create(&thread[i], NULL, eat, (void*)(&ids[i])) != 0){
			break;
		}
	}

	for(i = 0; i < num_fil; i++){
		pthread_join(thread[i], NULL);
	}

	return 0;
}
