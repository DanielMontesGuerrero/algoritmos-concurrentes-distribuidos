#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>

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
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	printf("El mensaje es: %s\n", message.msg_text);
	return 0;
}
