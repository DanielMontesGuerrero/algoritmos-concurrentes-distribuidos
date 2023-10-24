/*
 * Alumno: Daniel Montes Guerrero
 * Ejecutar: g++ hilos.cpp && ./a.out
 */
#include<iostream>
#include<pthread.h>

using namespace std;

void *func(void* args){
	cout << "Soy un hilo" << endl;
	return NULL;
}

int main(){
	for(int i = 0; true; i++){
		cout << "Crando hilo " << i << endl;
		pthread_t h;
		if(pthread_create(&h, NULL, func, NULL) != 0)
			break;
	}
	return 0;
}
