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

int main(int argc, char* argv[]){
    int vueltas = 10;
    double pista;
    printf("Ingresa el tamaño de la pista en metros: ");
    scanf("%d", &pista);

}


struct Carro {
    char nombre[50];
    double velocidad;
    double paradas;
};

struct Carro crearCarro(const char *nombre, int velocidad, int paradas) {
    struct Carro carro;
    strncpy(carro.nombre, nombre, sizeof(carro.nombre));
    carro.velocidad = velocidad;
    carro.paradas = paradas;
    return carro;
}

double getVelocidad(const struct Carro *carro){
    double vel = carro->velocidad;
    return vel;
}

double getParadas(const struct Carro *carro){
    double par = carro->paradas;
    return par;
}

double calcularTiempoVuelta(const struct Carro *carro, double longitudPista) {
    double velocidadCarro = carro->velocidad; 
    double tiempoVuelta = longitudPista / velocidadCarro;
    return tiempoVuelta;
}

double paradasEnVueltas(const struct Carro *carro, int vueltas){
    double paradasCarro = carro->paradas;
    double vueltapar = vueltas / paradasCarro;
    vueltapar = floor(vueltapar);
    return vueltapar;
}