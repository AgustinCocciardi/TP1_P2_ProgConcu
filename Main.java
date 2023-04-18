import java.util.Random;
import java.util.ArrayList;

public class Main{

    static class Matriz {
        private int[][] matrizA;
        private int[][] matrizB;
        private int[][] matrizCS;
        private int[][] matrizCH;
        private int tamanioMatriz;
        final int INICIO_ITERADOR = 0;
    
        public Matriz(int tamanio) {
            this.tamanioMatriz = tamanio;
            matrizA = new int[tamanio][tamanio];
            matrizB = new int[tamanio][tamanio];
            matrizCS = new int[tamanio][tamanio];
            matrizCH = new int[tamanio][tamanio];
        }
    
        // Método para mostrar las cuatro matrices
        public void mostrarMatrices() {
            System.out.println("Matriz A:");
            mostrarMatriz(matrizA);
            System.out.println("Matriz B:");
            mostrarMatriz(matrizB);
            System.out.println("Matriz CS:");
            mostrarMatriz(matrizCS);
            System.out.println("Matriz CH:");
            mostrarMatriz(matrizCH);
        }

        public void completarMatricesAleatorias() {
            Random random = new Random();
            for (int i = 0; i < tamanioMatriz; i++) {
                for (int j = 0; j < tamanioMatriz; j++) {
                    matrizA[i][j] = random.nextInt(65) - 32; // generamos un número entre -32 y 32
                    matrizB[i][j] = random.nextInt(65) - 32; // generamos un número entre -32 y 32
                }
            }
        }
    
        // Método para multiplicar las matrices A y B de forma secuencial
        public void multiplicarMatricesSecuencial() {
            for (int i = 0; i < tamanioMatriz; i++) {
                for (int j = 0; j < tamanioMatriz; j++) {
                    int suma = 0;
                    for (int k = 0; k < tamanioMatriz; k++) {
                        suma += matrizA[i][k] * matrizB[k][j];
                    }
                    matrizCS[i][j] = suma;
                }
            }
        }

        public void multiplicarMatricesConHilos(int cantidadHilos) {
            ArrayList<Thread> hilos = new ArrayList<>();
            for (int i = INICIO_ITERADOR; i < cantidadHilos; i++) {
                final int x = i;
                hilos.add(new Thread(new Runnable() {
                    @Override
                    public void run() {
                        funcionEjecutadaPorHilo(x);
                    }
                }));
            }
            for (Thread hilo : hilos) {
                hilo.start();
            }
            for (Thread hilo : hilos) {
                try {
                    hilo.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        void funcionEjecutadaPorHilo(int numeroHilo) {
            for (int j = INICIO_ITERADOR; j < this.tamanioMatriz; j++) {
                for (int k = INICIO_ITERADOR; k < this.tamanioMatriz; k++) {
                    this.matrizCH[numeroHilo][j] += this.matrizA[numeroHilo][k] * this.matrizB[k][j];
                }
            }
        }
    
        // Método auxiliar para mostrar una matriz
        private void mostrarMatriz(int[][] matriz) {
            for (int i = 0; i < tamanioMatriz; i++) {
                for (int j = 0; j < tamanioMatriz; j++) {
                    //System.out.print(matriz[i][j] + " ");
                    System.out.printf("%6d", matriz[i][j]);
                }
                System.out.println();
            }
            System.out.println();
        }
    }

    public static Matriz matrices;

    public static void main(String[] args) {
        // Validar que se haya pasado un solo parámetro
        if (args.length != 1) {
            System.out.println("Error: se esperaba un parámetro entero entre 5 y 20");
            return;
        }
        // Convertir el parámetro a un número entero
        int tamanioMatrices = 0;
        try {
            tamanioMatrices = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Error: el parámetro debe ser un número entero");
            return;
        }

        // Validar que el número entero esté entre 5 y 20
        if (tamanioMatrices < 5 || tamanioMatrices > 20) {
            System.out.println("Error: el número debe estar entre 5 y 20");
            return;
        }

        matrices = new Matriz(tamanioMatrices);
        matrices.completarMatricesAleatorias();
        matrices.multiplicarMatricesSecuencial();
        matrices.multiplicarMatricesConHilos(tamanioMatrices);
        matrices.mostrarMatrices();
        return;
    }
}