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
#define EXITO 1

struct MatricesHilos
{
    int** matrizA;
    int** matrizB;
    int** matrizCS;
    int** matrizCH;
    int tamanioMatriz;
};

void mostrarMatriz(int **matriz,int tamanioMatriz,const char* nombre);
int** crearMatriz(int tamanioMatriz);
bool cantidadCorrectaDeParametros(int parametrosRecibidos, int parametrosEsperados);
bool rangoValidoN(int valor, int valorMinimo, int valorMaximo);
MatricesHilos llenarEstructura(int tamanio);
void mostrarMatrices(MatricesHilos matrizHilos);
void multiplicarMatricesSecuencial(MatricesHilos matrizHilos);
void llenarMatricesAleatorio(MatricesHilos matrizHilos);

int main(int argc, char* argv[]){
    if(!cantidadCorrectaDeParametros(argc,PARAMETROS_CORRECTOS)){
        std::cout<<"No ingreso la cantidad correcta de parametros. Solo debe ingresar el valor de N"<<std::endl;
        return PARAMETROS_INCORRECTOS;
    }
    int tamanioMatrices = atoi(argv[1]);
    if (!rangoValidoN(tamanioMatrices,RANGO_MINIMO,RANGO_MAXIMO))
    {
        std::cout<<"El rango de N debe estar entre 5 y 20"<<std::endl;
        return N_FUERA_DE_RANGO;
    }
    int cantidadHilos = tamanioMatrices;
    MatricesHilos matrizHilos = llenarEstructura(tamanioMatrices);
    llenarMatricesAleatorio(matrizHilos);
    multiplicarMatricesSecuencial(matrizHilos);
    mostrarMatrices(matrizHilos);
    return EXITO;
}

void llenarMatricesAleatorio(MatricesHilos matrizHilos)
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

void multiplicarMatricesSecuencial(MatricesHilos matrizHilos)
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

bool cantidadCorrectaDeParametros(int parametrosRecibidos, int parametrosEsperados)
{
    return parametrosRecibidos == parametrosEsperados;
}

bool rangoValidoN(int valor, int valorMinimo, int valorMaximo)
{
    return valor >= valorMinimo && valor <= valorMaximo;
}

MatricesHilos llenarEstructura(int tamanio)
{
    MatricesHilos matrizHilo;
    matrizHilo.matrizA = crearMatriz(tamanio);
    matrizHilo.matrizB = crearMatriz(tamanio);
    matrizHilo.matrizCS = crearMatriz(tamanio);
    matrizHilo.matrizCH = crearMatriz(tamanio);
    matrizHilo.tamanioMatriz = tamanio;
    return matrizHilo;
}

void mostrarMatrices(MatricesHilos matrizHilos)
{
    mostrarMatriz(matrizHilos.matrizA,matrizHilos.tamanioMatriz,"Matriz A");
    mostrarMatriz(matrizHilos.matrizB,matrizHilos.tamanioMatriz,"Matriz B");
    mostrarMatriz(matrizHilos.matrizCS,matrizHilos.tamanioMatriz,"Matriz CS");
    mostrarMatriz(matrizHilos.matrizCH,matrizHilos.tamanioMatriz,"Matriz CH");
}