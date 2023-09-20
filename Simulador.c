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
#include <omp.h>

int main(int argc, char* argv[]){

}


struct Carro {
    char nombre[50];
    int velocidad;
    int paradas;
};

struct Carro crearCarro(const char *nombre, int velocidad, int paradas) {
    struct Carro carro;
    strncpy(carro.nombre, nombre, sizeof(carro.nombre));
    carro.velocidad = velocidad;
    carro.paradas = paradas;
    return carro;
}

int getVelocidad(const struct Carro *carro){
    int vel = carro->velocidad;
    return vel;
}

int getParadas(const struct Carro *carro){
    int par = carro->paradas;
    return par;
}