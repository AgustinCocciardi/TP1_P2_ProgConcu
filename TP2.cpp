#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define PARAMETROS_INCORRECTOS 0
#define N_FUERA_DE_RANGO PARAMETROS_INCORRECTOS
#define ESPACIO_CARACTERES 6
#define INICIO_ITERADOR 0
#define PARAMETROS_CORRECTOS 2
#define RANGO_MINIMO 5
#define RANGO_MAXIMO 20
#define VALOR_ALEATORIO_MAXIMO 65
#define VALOR_ALEATORIO_NEGATIVO 32

void llenarMatricesAleatorio(int **matrizA, int **matrizB,int tamanioMatriz);
void mostrarMatriz(int **matriz,int tamanioMatriz,const char* nombre);
int** crearMatriz(int tamanioMatriz);
void mostrarMatrices(int **matrizA, int **matrizB, int **matrizCS, int **matrizCH, int tamanioMatriz);
int** multiplicarMatricesSecuencial(int **matrizA, int **matrizB, int tamanioMatriz);

int main(int argc, char* argv[]){
    if(argc != PARAMETROS_CORRECTOS){
        std::cout<<"No ingreso la cantidad correcta de parametros. Solo debe ingresar el valor de N"<<std::endl;
        return PARAMETROS_INCORRECTOS;
    }
    int tamanioMatrices = atoi(argv[1]);
    if (tamanioMatrices < RANGO_MINIMO || tamanioMatrices > RANGO_MAXIMO)
    {
        std::cout<<"El rango de N debe estar entre 5 y 20"<<std::endl;
        return N_FUERA_DE_RANGO;
    }
    int cantidadHilos = tamanioMatrices;
    int **matrizA, **matrizB, **matrizCS, **matrizCH;
    matrizA = crearMatriz(tamanioMatrices);
    matrizB = crearMatriz(tamanioMatrices);
    matrizCH = crearMatriz(tamanioMatrices);
    llenarMatricesAleatorio(matrizA,matrizB,tamanioMatrices);
    matrizCS = multiplicarMatricesSecuencial(matrizA,matrizB,tamanioMatrices);
    mostrarMatrices(matrizA,matrizB,matrizCS,matrizCH,tamanioMatrices);    
}

void llenarMatricesAleatorio(int **matrizA, int **matrizB,int tamanioMatriz)
{
    srand(time(NULL));
    for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++)
    {
        for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++)
        {
            matrizA[i][j] = rand() % VALOR_ALEATORIO_MAXIMO - VALOR_ALEATORIO_NEGATIVO;
            matrizB[i][j] = rand() % VALOR_ALEATORIO_MAXIMO - VALOR_ALEATORIO_NEGATIVO;
        }
    }
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

void mostrarMatrices(int **matrizA, int **matrizB, int **matrizCS, int **matrizCH, int tamanioMatriz)
{
    mostrarMatriz(matrizA,tamanioMatriz,"Matriz A");
    mostrarMatriz(matrizB,tamanioMatriz,"Matriz B");
    mostrarMatriz(matrizCS,tamanioMatriz,"Matriz CS");
    mostrarMatriz(matrizCH,tamanioMatriz,"Matriz CH");
}

int** multiplicarMatricesSecuencial(int **matrizA, int **matrizB, int tamanioMatriz)
{
    int** matriz = crearMatriz(tamanioMatriz);
    for (int i = INICIO_ITERADOR; i < tamanioMatriz; i++)
    {
        for (int j = INICIO_ITERADOR; j < tamanioMatriz; j++)
        {
            matriz[i][j] = 0;
            for (int k = INICIO_ITERADOR; k < tamanioMatriz; k++)
            {
                matriz[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    return matriz;
}