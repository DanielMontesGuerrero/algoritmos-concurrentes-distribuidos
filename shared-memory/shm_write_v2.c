/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc shm_write_v2.c -o write
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char** argv){
	int *vector, shmid;
	key_t llave;

	if(argc < 2){
		printf("Syntaxis: shm_write <valor>\n");
		return -1;
	}

	int val = atoi(argv[1]);

	printf("El valor es: %d\n", val);

	printf("Crear llave\n");
	llave = ftok("shared", 2019);
	printf("Read or create memory zone pointer\n");
	shmid = shmget(llave, 25 * sizeof(int), IPC_CREAT | 0777);
	vector = (int*)shmat(shmid, (void*)0, 0);
	vector[10] = val;
	shmdt(vector);
	//shmctl(shmid, IPC_RMID, 0);
	return 0;
}
