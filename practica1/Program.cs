/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: dotnet build
 */

using System.Threading;
using System.Diagnostics;

class Task{
	public void Run(){
		Console.WriteLine("Soy el hijo " + Process.GetCurrentProcess().Id);
	}
}

class Program{
	static void Main(string[] args){
		var task = new Task();
		Thread trd = new Thread(new ThreadStart(task.Run));
		trd.Start();
		Console.WriteLine("Soy el padre " + Process.GetCurrentProcess().Id);
	}
}
