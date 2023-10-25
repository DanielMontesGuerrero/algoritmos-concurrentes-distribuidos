#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

#define CHILD 0
#define ERROR -1

int main(){
	int i, error, fd[2], tam, pid, bytes;
	tam = 5;
	char *buf = (char*)malloc(sizeof(char) * tam);
	char *buf2 = (char*)malloc(sizeof(char) * tam);
	
	buf = (char*)calloc(tam, sizeof(char));
	
	error = pipe(fd);
	if(error < 0){
		printf("Error wn la creacion del pipe\n");
		return 1;
	}
	pid = fork();
	switch(pid){
		case ERROR:
			printf("Error en la creacion del hijo\n");
			break;
		case CHILD:
			//read(fd[0], buf2, tam);
			bytes = read(fd[0], buf2, 3);
			printf("H: %s %d\n", buf2, bytes);
			break;
		default:
			sleep(2);
			strcpy(buf, "abcde");
			write(fd[1], buf, tam);
			printf("P: %s\n", buf);
	}
	return 0;
}
