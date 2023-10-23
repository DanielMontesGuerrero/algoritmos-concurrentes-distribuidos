/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: g++ procesos.cpp
 */
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main () {
	pid_t pid = fork();
	if(pid == 0){
		cout << "Soy el hijo " << getpid() << " con padre " << getppid() << endl;
	}
	else{
		cout << "Soy el padre " << getpid() << endl;
	}
	return 0;
}

