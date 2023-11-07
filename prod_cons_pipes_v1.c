#include<stdio.h>
#include<stdlib.h>
#include<wait.h>

int tuberia[2];

void productor(){
	printf("Productor: %d", getpid());
	char* buff = (char*)malloc(100 * sizeof(char));
	int cnt = 0;
	while(1){
		sprintf(buff, "%d", cnt);
		sleep(1);

		int tam = strlen(buff);
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
		printf("\t\t\tLeyo: %s\n", buff);
		sleep(2);
		fflush(stdout);
	}
}

int main(){
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
