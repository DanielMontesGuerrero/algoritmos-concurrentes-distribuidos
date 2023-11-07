#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<string.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

#define MAXN 1000

int del_cons, del_prod;
char Q_BUFF[MAXN];
int back;
sem_t sem_b, sem_prod, sem_cons;

void* productor(void* arg){
	printf("Productor: %d", getpid());
	char* buff = (char*)malloc(100 * sizeof(char));
	int cnt = 0;
	int i;
	while(1){
		sprintf(buff, "%d", cnt);
		sleep(del_prod);
		int tam = strlen(buff);

		sem_wait(&sem_prod);
		if(back + tam > MAXN){
		}
		// region critica
		sem_wait(&sem_b);
		for(int i = 0; i < tam; i++){
			Q_BUFF[back] = buff[i];
			back++;
		}
		sem_post(&sem_b);
		// region critica
		sem_post(&sem_cons);

		printf("Escribio: %d\n", cnt);

		cnt++;
		fflush(stdout);
	}
}

void* consumidor(void* arg){
	printf("Consumidor: %d", getpid());
	char* buff = (char*)malloc(101 * sizeof(char));
	int i = 0;
	int j = 0;
	while(1){
		sem_wait(&sem);
		for(i = 0; i < 100 && i < back; i++){
			buff[i] = Q_BUFF[i];
		}
		buff[i] = '\0';
		int bytes = i;
		for(j = 0; i < back; i++, j++){
			Q_BUFF[j] = Q_BUFF[i];
		}
		back = j;
		sem_post(&sem);

		printf("\t\t\tLeyo: %s, %d\n", buff, bytes);
		sleep(del_cons);
		fflush(stdout);
	}
}

int main(int argc, char** argv){
	del_cons = 3;
	del_prod = 1;
	back = 0;
	if(argc >= 3){
		del_prod = atoi(argv[1]);
		del_cons = atoi(argv[2]);
	}
	printf("Delays: %d %d\n", del_prod, del_cons);
	if(sem_init(&sem, 0, 1) < 0){
		puts("Error creando el semaforo");
	}
	
	pthread_t h1, h2;
	puts("Creando hilos");
	pthread_create(&h1, 0, productor, NULL);
	pthread_create(&h2, 0, consumidor, NULL);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);

	printf("Padre: %d", getpid());
}
