#include<stdio.h>
#include<signal.h>

void handler(int);

int main(void){
	kill(SIGUSR1, handler);
	while(1);
	return 0;
}

void handler(int sig){
	printf("Señal recibida: %d\n", sig);
}
