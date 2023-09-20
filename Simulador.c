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
#include <unistd.h>

#include <string.h>


#include <time.h>

struct Carro {
    /*  */
    char nombre[50];
    double velocidad;
    double paradas; 
};

struct Carro crearCarroAleatorio(int numeroCarro) {
    struct Carro carro;
    sprintf(carro.nombre, "Carro %d ", numeroCarro); 
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

void simuladorCarrera(const struct Carro *carro, double longitudPista, int vueltas){
    double tiempovuelta = calcularTiempoVuelta(carro, longitudPista);
    int vueltascomp = 0;
    int paradashechas = 0;
    double tiempocarrera = 0;

    while(vueltascomp < vueltas){
        if(vueltascomp == 0){
            sleep((tiempovuelta));
            tiempocarrera = tiempovuelta;
            vueltascomp++;
            printf("%s termino la vuelta 1 en: %.2f s\n", carro->nombre, tiempocarrera);
        }
        else{
            int paradashacer = carro->paradas;
            if(paradashechas < paradashacer){
                int parar = rand()% 2 + 1;
                int tipo = rand()% 2 + 1;
                sleep((tiempovuelta/2));
                if(parar == 1){
                    if(tipo == 1){
                        printf("%s hizo una parada en los pits para hechar gasolina \n", carro->nombre);
                        sleep(10);
                        tiempocarrera = tiempocarrera + 10;
                        printf("%s termino su parada en los pits\n", carro->nombre);
                        sleep((tiempovuelta/2));
                        tiempocarrera = tiempocarrera + tiempovuelta;
                        paradashechas++;
                    }
                    else if(tipo == 2){
                        printf("%s hizo una parada en los pits para cambiar sus llantas\n", carro->nombre);
                        sleep(20);
                        tiempocarrera = tiempocarrera + 20;
                        printf("%s termino su parada en los pits\n", carro->nombre);
                        sleep((tiempovuelta/2));
                        tiempocarrera = tiempocarrera + tiempovuelta;
                        paradashechas++;
                    }
                }
                else if (tipo == 2){
                    sleep((tiempovuelta/2));
                    tiempocarrera = tiempocarrera + tiempovuelta;
                }
                vueltascomp++;
                printf("%s termino la vuelta %d en: %.2f s\n", carro->nombre, vueltascomp, tiempocarrera);

            }
            else{
                vueltascomp++;
                sleep((tiempovuelta));
                tiempocarrera = tiempocarrera + tiempovuelta;
                printf("%s termino la vuelta %d en: %.2f s\n", carro->nombre, vueltascomp, tiempocarrera);
            }
        }
        
    }
    printf("%s termino la carrera en: %.2f s\n", carro->nombre, tiempocarrera);
    
}


int main(int argc, char* argv[]){
    int vueltas = 10;
    double pista = 0;
    int numeroCarros = 8;
    srand(time(NULL));
    struct Carro carros[8];
    for (int i = 0; i < 8; i++) {
        carros[i] = crearCarroAleatorio(i + 1);
    }
    printf("Estado inicial de los carros: \n");
    for (int i = 0; i < 8; i++) {
        printf("Carro %d - Nombre: %s, Velocidad: %.2lf m/s, Paradas: %.0lf\n", i + 1, carros[i].nombre, carros[i].velocidad, carros[i].paradas);
    }

    printf("Ingresa la dimension de la pista en metros: ");
    scanf("%lf", &pista);

    #pragma omp parallel
    {
         #pragma omp for
          for (int i = 0; i < 8; i++){
            simuladorCarrera(&carros[i],pista,vueltas);
         }
    }
    

   
    return 0;
}