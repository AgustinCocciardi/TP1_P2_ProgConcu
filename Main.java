import java.util.Random;
import java.util.ArrayList;

public class Main
{

  final static int NUMERO_PARAMETROS = 1;
  final static int RANGO_MINIMO = 5;
  final static int RANGO_MAXIMO = 20;
  final static int INICIALIZADOR = 0;

  static class Matriz 
  {
    private int[][] matrizA;
    private int[][] matrizB;
    private int[][] matrizCS;
    private int[][] matrizCH;
    private int tamanioMatriz;
    final int INICIO_ITERADOR = 0;
    final int VALOR_ALEATORIO_MAXIMO = 65;
    final int VALOR_ALEATORIO_NEGATIVO = 32;

    public Matriz(int tamanio) 
    {
      this.tamanioMatriz = tamanio;
      this.matrizA = new int[tamanio][tamanio];
      this.matrizB = new int[tamanio][tamanio];
      this.matrizCS = new int[tamanio][tamanio];
      this.matrizCH = new int[tamanio][tamanio];
    }
    
    public void mostrarMatrices() 
    {
      System.out.println("Matriz A:");
      mostrarMatriz(matrizA);
      System.out.println("Matriz B:");
      mostrarMatriz(matrizB);
      System.out.println("Matriz CS:");
      mostrarMatriz(matrizCS);
      System.out.println("Matriz CH:");
      mostrarMatriz(matrizCH);
    }

    public void completarMatricesAleatorias() 
    {
      Random random = new Random();
      for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++) 
      {
        for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++) 
        {
          matrizA[i][j] = random.nextInt(VALOR_ALEATORIO_MAXIMO) - VALOR_ALEATORIO_NEGATIVO; 
          matrizB[i][j] = random.nextInt(VALOR_ALEATORIO_MAXIMO) - VALOR_ALEATORIO_NEGATIVO; 
        }
      }
    }
    
    public void multiplicarMatricesSecuencial() 
    {
      for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++) 
      {
        for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++) 
        {
          int suma = INICIALIZADOR;
          for (int k = INICIO_ITERADOR; k < tamanioMatriz; k++) 
          {
            suma += matrizA[i][k] * matrizB[k][j];
          }
          matrizCS[i][j] = suma;
        }
      }
    }

    public void multiplicarMatricesConHilos(int cantidadHilos) 
    {
      ArrayList<Thread> hilos = new ArrayList<>();
      for (int i = INICIO_ITERADOR; i < cantidadHilos; i++) 
      {
        final int hilo = i;
        hilos.add(new Thread(new Runnable() 
        {
          @Override
          public void run() 
          {
            funcionEjecutadaPorHilo(hilo);
          }
        }));
      }
      for (Thread hilo : hilos) 
      {
        hilo.start();
      }
      for (Thread hilo : hilos) 
      {
        try 
        {
          hilo.join();
        } 
        catch (InterruptedException e) 
        {
          e.printStackTrace();
        }
      }
    }

    void funcionEjecutadaPorHilo(int numeroHilo) 
    {
      for (int j = INICIO_ITERADOR; j < this.tamanioMatriz; j++) 
      {
        for (int k = INICIO_ITERADOR; k < this.tamanioMatriz; k++) 
        {
          this.matrizCH[numeroHilo][j] += this.matrizA[numeroHilo][k] * this.matrizB[k][j];
        }
      }
    }

    private void mostrarMatriz(int[][] matriz) 
    {
      for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++) 
      {
        for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++) 
        {
          System.out.printf("%6d", matriz[i][j]);
        }
        System.out.println();
      }
      System.out.println();
    }

    void compararMatricesResultado()
    {
      boolean sonIguales = true;
      for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++) 
      {
        for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++) 
        {
          if (matrizCS[i][j] != matrizCH[i][j])
          {
            sonIguales = false;
            break;
          }
        }
      }
      if (sonIguales) 
        System.out.println("El producto matricial coincide");
      else
        System.out.println("El producto matricial no coincide");
    }
  }

  public static Matriz matrices;
  public static void main(String[] args) 
  {
    if (args.length != NUMERO_PARAMETROS) 
    {
      System.out.println("No ingreso la cantidad correcta de parametros. Solamente debe ingresar un entero positivo entre 5 y 20");
      return;
    }
    int tamanioMatrices = INICIALIZADOR;
    try 
    {
      tamanioMatrices = Integer.parseInt(args[0]);
    } 
    catch (NumberFormatException e) 
    {
      System.out.println("El parametro que usted ingreso no es un entero positivo entre 5 y 20");
      return;
    }

    if (tamanioMatrices < RANGO_MINIMO || tamanioMatrices > RANGO_MAXIMO) 
    {
      System.out.println("El rango de N debe estar entre 5 y 20");
      return;
    }
    int cantidadHilos = tamanioMatrices;
    matrices = new Matriz(tamanioMatrices);
    matrices.completarMatricesAleatorias();
    matrices.multiplicarMatricesSecuencial();
    matrices.multiplicarMatricesConHilos(cantidadHilos);
    matrices.mostrarMatrices();
    matrices.compararMatricesResultado();
    return;
  }
}