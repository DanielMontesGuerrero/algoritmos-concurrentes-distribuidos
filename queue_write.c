#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>

struct msg_buffer {
	long msg_type;
	char msg_text[100];
};

struct msg_buffer message;

int main(){
	key_t key;
	int msgid;
	key = ftok("prgfile", 65);
	msgid = msgget(key, 0666 | IPC_CREAT);
	printf("Ingresa el mensaje: ");
	char buffer[100];
	scanf("%s", buffer);
	strcpy(message.msg_text, buffer);
	message.msg_type = 1;
	printf("El mensaje a enviar es: %s\n", message.msg_text);
	msgsnd(msgid, &message, sizeof(message), 0);
	return 0;
}
