/*
*----------------------------------------
* Simulador.c
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3086 - Programacion de Microprocesadores
* Ver.: 1.3
* Fecha: 2023/09/21
*
* Bianca Calderón - 22272
* Diego Duarte - 22075
* Daniel Dubón - 22233
* Juan Pablo Solis - 22102
* 
* ---------------------------------------
* Simulador de Carreras de Formula 1 
*----------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


#include <string.h>


#include <time.h>

struct Carro {
    char nombre[50];
    double velocidad;
    double paradas; 
};

struct Carro crearCarroAleatorio(int numeroCarro) {
    struct Carro carro;
    sprintf(carro.nombre, "Carro %d", numeroCarro); 
    carro.velocidad = (rand() % 40+ 47.7778) /2; 
    carro.paradas = rand() % 6 + 1; 
    return carro;
}


double calcularTiempoVuelta(const struct Carro *carro, double longitudPista) {
    double velocidadCarro = carro->velocidad; 
    double tiempoVuelta = longitudPista / velocidadCarro;
    return tiempoVuelta;
}

double paradasTiempo(const struct Carro *carro, double tiempo){
    double paradasCarro = carro->paradas;
    double vueltapar = tiempo / paradasCarro;
    return vueltapar;
}

void simuladorCarrera(const struct Carro *carro, double longitudPista){
    double tiempovuelta = calcularTiempoVuelta(carro, longitudPista);
    double tiempoparo = paradasTiempo(carro, tiempovuelta);
    int vueltas;
    
}



int main(int argc, char* argv[]){
    int vueltas = 10;
    double pista;
    int numeroCarros = 8;
    srand(time(NULL));
    struct Carro carros[8];
    for (int i = 0; i < 8; i++) {
        carros[i] = crearCarroAleatorio(i + 1);
    }
    printf("Estado inicial de los carros:\n");
    for (int i = 0; i < 8; i++) {
        printf("Carro %d - Nombre: %s, Velocidad: %.2lf m/s, Paradas: %.0lf\n", i + 1, carros[i].nombre, carros[i].velocidad, carros[i].paradas);
    }


  
    printf("Ingresa el tamaño de la pista en metros: ");
    scanf("%d", &pista);

    #pragma omp parallel 
    {

    }
    
}