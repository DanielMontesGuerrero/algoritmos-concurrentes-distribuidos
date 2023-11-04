/*
 * Alumno: Daniel Montes Guerrero
 * Compilar: javac Filosofos.java
 */

import java.util.ArrayList;

class Controller {
    int num_eating;
    int num_fil;
    int limit;
    ArrayList<Integer> forks;

    Controller(int num_fil){
        num_eating = 0;
        forks = new ArrayList<Integer>(num_fil);        
        for(int i = 0; i < num_fil; i++){
            forks.add(0);
        }
        this.num_fil = num_fil;
        this.limit = Math.max(1, num_fil - 1);
    }

    public synchronized void wait_to_eat(){
        while(num_eating == limit){
            try{
                wait();
            }
            catch(Exception e){
                System.out.println(e);
                System.out.println("error en controlador");
            }
        }
        num_eating++;
        notifyAll();
    }
    public synchronized void wait_to_get_fork(int fork){
        while(forks.get(fork) == 1){
            try{
                wait();
            }
            catch(Exception e){
                System.out.println(e);
                System.out.println("error en controlador");
            }
        }
        forks.set(fork, 1);
        notifyAll();
    }
    public synchronized void release_eating(){
        num_eating--;
        notifyAll();
    }
    public synchronized void release_fork(int fork){
        forks.set(fork, 0);
        notifyAll();
    }
}

class Filosofo extends Thread {
    Controller controller;
    int id;
    int num_fil;

    Filosofo(Controller controller, int id, int num_fil){
        this.controller = controller;
        this.id = id;
        this.num_fil = num_fil;
    }

    public void run(){
        try{
            while (true) {
                controller.wait_to_eat();
                controller.wait_to_get_fork(id);
                System.out.println("Filosofo: " + id + " obtiene tenedor " + id);
                controller.wait_to_get_fork((id + 1) % num_fil);
                System.out.println("Filosofo: " + id + " obtiene tenedor " + (id + 1) % num_fil);
                System.out.println("Filosofo: " + id + " empieza a comer");
                Thread.sleep(2000);

                System.out.println("Filosofo: " + id + " termina de comer");
                controller.release_eating();
                controller.release_fork(id);
                controller.release_fork((id + 1) % num_fil);
                Thread.sleep(1000);
            }
        }
        catch(Exception e){
            System.out.println(e);
            System.out.println("Error en filosofo");
        }
    }
}

public class Filosofos {
    public static void main(String[] args){
        if (args.length < 1) {
            System.out.println("Uso: java Filosofos <num_filosofos>");
            return;
        }
        int num_fil = Integer.parseInt(args[0]);
        System.out.println("Filosofos: " + num_fil);
        var controller = new Controller(num_fil);
        var filosofos = new ArrayList<Filosofo>(num_fil);
        for (int i = 0; i < num_fil; i++) {
            filosofos.add(new Filosofo(controller, i, num_fil));
            filosofos.get(i).start();
        }
        try {
            for (int i = 0; i < num_fil; i++) {
                filosofos.get(i).join();
            }
        } catch (InterruptedException e) {

        }
    }
}