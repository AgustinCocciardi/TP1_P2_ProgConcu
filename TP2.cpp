#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <cstring>

#define PARAMETROS_INCORRECTOS 0
#define N_FUERA_DE_RANGO PARAMETROS_INCORRECTOS
#define PARAMETRO_NO_ENTERO PARAMETROS_INCORRECTOS
#define ESPACIO_CARACTERES 6
#define INICIO_ITERADOR 0
#define PARAMETROS_CORRECTOS 2
#define RANGO_MINIMO 5
#define RANGO_MAXIMO 20
#define VALOR_ALEATORIO_MAXIMO 65
#define VALOR_ALEATORIO_NEGATIVO 32
#define EXITO 1

struct MatricesHilos
{
  int** matrizA;
  int** matrizB;
  int** matrizCS;
  int** matrizCH;
  int tamanioMatriz;
  int cantidadHilos;
};

bool cantidadCorrectaDeParametros(int parametrosRecibidos, int parametrosEsperados);
bool parametroNEsEntero(char* parametro);
bool rangoValidoN(int valor, int valorMinimo, int valorMaximo);
int** crearMatriz(int tamanioMatriz);
void mostrarMatriz(int **matriz,int tamanioMatriz,const char* nombre);
MatricesHilos llenarEstructura(int tamanio);
void llenarMatricesAleatorio();
void multiplicarMatricesSecuencial();
void multiplicarMatricesConHilos(int cantidadHilos);
void mostrarMatrices();
void funcionEjecutadaPorHilo(int numeroHilo);
void compararMatricesResultado();

MatricesHilos matrizHilos;

int main(int argc, char* argv[])
{
  if(!cantidadCorrectaDeParametros(argc,PARAMETROS_CORRECTOS))
  {
    std::cout<<"No ingreso la cantidad correcta de parametros. Solamente debe ingresar un entero positivo"<<std::endl;
    return PARAMETROS_INCORRECTOS;
  }
  char* parametroN = argv[1];
  if (!parametroNEsEntero(parametroN))
  {
    std::cout<<"El parametro que usted ingreso no es un entero positivo"<<std::endl;
    return PARAMETRO_NO_ENTERO;
  }
  int tamanioMatrices = atoi(argv[1]);
  if (!rangoValidoN(tamanioMatrices,RANGO_MINIMO,RANGO_MAXIMO))
  {
    std::cout<<"El rango de N debe estar entre 5 y 20"<<std::endl;
    return N_FUERA_DE_RANGO;
  }
  
  matrizHilos = llenarEstructura(tamanioMatrices);
  llenarMatricesAleatorio();
  multiplicarMatricesSecuencial();
  multiplicarMatricesConHilos(matrizHilos.cantidadHilos);
  mostrarMatrices();
  compararMatricesResultado();
  return EXITO;
}

bool cantidadCorrectaDeParametros(int parametrosRecibidos, int parametrosEsperados)
{
  return parametrosRecibidos == parametrosEsperados;
}

bool parametroNEsEntero(char* parametro)
{
  for (int i = INICIO_ITERADOR; i < strlen(parametro); i++)
  {
    if (!isdigit(parametro[i]))
    {
      return false;
    }
  }
  return true;
}

bool rangoValidoN(int valor, int valorMinimo, int valorMaximo)
{
  return valor >= valorMinimo && valor <= valorMaximo;
}

int** crearMatriz(int tamanioMatriz)
{
  int** matriz = new int*[tamanioMatriz];
  for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++)
  {
    matriz[i] = new int[tamanioMatriz];
    for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++)
    {
      matriz[i][j] = 0;
    }
  }
  return matriz;
}

void mostrarMatriz(int **matriz,int tamanioMatriz,const char* nombre)
{
  std::cout<<nombre<<std::endl;
  for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++)
    {
      std::cout << std::setw(ESPACIO_CARACTERES) << matriz[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

MatricesHilos llenarEstructura(int tamanio)
{
  MatricesHilos matrizHilo;
  matrizHilo.matrizA = crearMatriz(tamanio);
  matrizHilo.matrizB = crearMatriz(tamanio);
  matrizHilo.matrizCS = crearMatriz(tamanio);
  matrizHilo.matrizCH = crearMatriz(tamanio);    
  matrizHilo.tamanioMatriz = matrizHilo.cantidadHilos = tamanio;
  return matrizHilo;
}

void llenarMatricesAleatorio()
{
  srand(time(NULL));
  for (int i = INICIO_ITERADOR; i < matrizHilos.tamanioMatriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < matrizHilos.tamanioMatriz; j++)
    {
      matrizHilos.matrizA[i][j] = rand() % VALOR_ALEATORIO_MAXIMO - VALOR_ALEATORIO_NEGATIVO;
      matrizHilos.matrizB[i][j] = rand() % VALOR_ALEATORIO_MAXIMO - VALOR_ALEATORIO_NEGATIVO;
    }
  }    
}

void multiplicarMatricesSecuencial()
{
  for (int i = INICIO_ITERADOR; i < matrizHilos.tamanioMatriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < matrizHilos.tamanioMatriz; j++)
    {
      matrizHilos.matrizCS[i][j] = 0;
      for (int k = INICIO_ITERADOR; k < matrizHilos.tamanioMatriz; k++)
      {
        matrizHilos.matrizCS[i][j] += matrizHilos.matrizA[i][k] * matrizHilos.matrizB[k][j];
      }
    }
  }    
}

void multiplicarMatricesConHilos(int cantidadHilos)
{
  std::vector<std::thread> hilos;
  for (int i = INICIO_ITERADOR; i < cantidadHilos; i++)
  {
    hilos.emplace_back(funcionEjecutadaPorHilo,i);
  }
  for (auto& hilo : hilos) 
  {
    hilo.join();
  }
}

void mostrarMatrices()
{
  mostrarMatriz(matrizHilos.matrizA,matrizHilos.tamanioMatriz,"Matriz A");
  mostrarMatriz(matrizHilos.matrizB,matrizHilos.tamanioMatriz,"Matriz B");
  mostrarMatriz(matrizHilos.matrizCS,matrizHilos.tamanioMatriz,"Matriz CS");
  mostrarMatriz(matrizHilos.matrizCH,matrizHilos.tamanioMatriz,"Matriz CH");
}

void funcionEjecutadaPorHilo(int numeroHilo)
{
  for (int j = INICIO_ITERADOR; j < matrizHilos.tamanioMatriz; j++)
  {
    for (int k = INICIO_ITERADOR; k < matrizHilos.tamanioMatriz; k++)
    {
      matrizHilos.matrizCH[numeroHilo][j] += matrizHilos.matrizA[numeroHilo][k] * matrizHilos.matrizB[k][j];
    }
  }
}

void compararMatricesResultado()
{
  bool sonIguales = true;
  for (int i = INICIO_ITERADOR; i < matrizHilos.tamanioMatriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < matrizHilos.tamanioMatriz; j++)
    {
      if (matrizHilos.matrizCS[i][j] != matrizHilos.matrizCH[i][j])
      {
        sonIguales = false;
        break;
      }
    }
  }
  if (sonIguales)
    std::cout<<"El producto matricial coincide"<<std::endl;
  else
    std::cout<<"El producto matricial no coincide"<<std::endl;
}