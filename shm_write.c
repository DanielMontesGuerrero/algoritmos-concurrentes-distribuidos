#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>

int main(){
	int *vector, shmid;
	key_t llave;

	printf("Crear llave\n");
	llave = ftok("shared", 2019);
	printf("Read or create memory zone pointer\n");
	shmid = shmget(llave, 25 * sizeof(int), IPC_CREAT | 0777);
	vector = (int*)shmat(shmid, (void*)0, 0);
	vector[10] = 12345;
	shmdt(vector);
	//shmctl(shmid, IPC_RMID, 0);
	return 0;
}
