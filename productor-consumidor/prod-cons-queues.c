/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: gcc prod-cons-queues.c
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

#define MAX_PROD 100
#define BUFFER_SIZE 100

struct msg_buffer {
	long msg_len;
	char msg_text[BUFFER_SIZE];
};

void write_char(char c, int msgid){
	/* printf("file: %s\n", file); */
	char buffer[1];
	buffer[0] = c;
	struct msg_buffer message;
	strcpy(message.msg_text, buffer);
	message.msg_len = 1;
	msgsnd(msgid, &message, sizeof(message), 0);
}

void read_chars(int msgid, int* bucket){
	int i = 0;
	struct msg_buffer message;
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	for(i = 0; i < message.msg_len; i++){
		bucket[message.msg_text[i] - 'a']++;
	}
}

void produce(char c, int msgid, int num_prd){
	int i;
	for(i = 0; i < MAX_PROD; i++){
		printf("productor %d produciendo %c, quedan: %d\n", num_prd, c, MAX_PROD - i);
		write_char(c, msgid);
	}
	printf("Termino %d produciendo %d\n", num_prd, i);
}

void consume(int msgid, int num_cons){
	int bucket[30];
	int i, cnt = 1;
	for(i = 0; i < 26; i++)
		bucket[i] = 0;
	while(1){
		printf("Consumidor %d consumiendo %d\n", num_cons, cnt);
		cnt++;
		read_chars(msgid, bucket);
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

	key_t key;
	char queue_name[] = "./queue";
	key = ftok(queue_name, 65);
	int msgid = msgget(key, 0666 | IPC_CREAT);
	int num_prods = atoi(argv[1]);
	int num_cons = atoi(argv[2]);
	printf("Ejecutando con %d productores y %d consumidores\n", num_prods, num_cons);
	int i;

	pid_t pid;
	for(i = 0; i < num_prods; i++){
		pid = fork();
		if(pid == -1){
			printf("Error creando el productor: %d\n", i);
		}
		else if(pid == 0){
			produce(i % 26 + 'a', msgid, i);
			return 0;
		}
	}
	for(i = 0; i < num_cons; i++){
		pid = fork();
		if(pid == -1){
			printf("Error creando el consumidor: %d\n", i);
		}
		else if(pid == 0){
			consume(msgid, i);
			return 0;
		}
	}
	while(1);
	return 0;
}
