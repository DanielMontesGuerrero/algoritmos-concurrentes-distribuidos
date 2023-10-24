/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: javac Procesos.java && java Procesos
 */

class ThreadExample extends Thread {
	public void run(){
		System.out.println("Soy el hijo " + ProcessHandle.current().pid());
	}
}

public class Procesos {
	public static void main(String[] args){
		ThreadExample thread = new ThreadExample();
		thread.start();
		System.out.println("Soy el padre " + ProcessHandle.current().pid());
	}
}
