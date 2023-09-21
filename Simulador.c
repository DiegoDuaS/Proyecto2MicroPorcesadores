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

    //Importacion de Librerias 
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <omp.h>
    #include <unistd.h>
    #include <string.h>
    #include <time.h>

    //Objeto Carro
    struct Carro {
        char nombre[50];
        double velocidad;
        double paradas; 
        double tiempoTotal;
    };

    //Funcion Crear Carro Aleatorio
    struct Carro crearCarroAleatorio(int numeroCarro) {
        struct Carro carro;
        sprintf(carro.nombre, "Carro %d ", numeroCarro); 
        carro.velocidad = (rand() % 40+ 47.7778) /2; 
        carro.paradas = rand() % 6 + 1; 
        carro.tiempoTotal = 0;
        return carro;
    }

    //Funcion Calcular Tiempo Vuelta 
    double calcularTiempoVuelta(struct Carro *carro, double longitudPista) {
        double velocidadCarro = carro->velocidad; 
        double tiempoVuelta = longitudPista / velocidadCarro;
        return tiempoVuelta;
    }

    //Funcion Simular Carrera
    void simuladorCarrera( struct Carro *carro, double longitudPista, int vueltas){
        double tiempovuelta = calcularTiempoVuelta(carro, longitudPista);
        int vueltascomp = 0;
        int paradashechas = 0;

        //Mientras las vueltas completadas sean menores a las vueltas de la carrera
        while(vueltascomp < vueltas){
            //Caso vuelta 1
            if(vueltascomp == 0){
                sleep((tiempovuelta));
                carro->tiempoTotal = tiempovuelta;
                vueltascomp++;
                printf("%s termino la vuelta 1 en: %.2f s\n", carro->nombre, carro->tiempoTotal);
            }
            //Caso vuelta 2-10
            else{
                int paradashacer = carro->paradas;
                //En caso que las paradas hechas sean menores a las paradas por hacer
                if(paradashechas < paradashacer){
                    //Randomizador para considerar que el carro debe hacer una parada
                    int parar = rand()% 2 + 1;
                    int tipo = rand()% 2 + 1;
                    sleep((tiempovuelta/2));
                    //En caso que tiene que hacer parada 
                    if(parar == 1){
                        //Caso Parada Gasolina
                        if(tipo == 1){
                            printf("%s hizo una parada en los pits para hechar gasolina \n", carro->nombre);
                            sleep(10);
                            carro->tiempoTotal = carro->tiempoTotal + 10;
                            printf("%s termino su parada en los pits\n", carro->nombre);
                            sleep((tiempovuelta/2));
                            carro->tiempoTotal = carro->tiempoTotal + tiempovuelta;
                            paradashechas++;
                        }
                        //Caso Parada Llanta 
                        else if(tipo == 2){
                            printf("%s hizo una parada en los pits para cambiar sus llantas\n", carro->nombre);
                            sleep(20);
                            carro->tiempoTotal = carro->tiempoTotal + 20;
                            printf("%s termino su parada en los pits\n", carro->nombre);
                            sleep((tiempovuelta/2));
                            carro->tiempoTotal = carro->tiempoTotal + tiempovuelta;
                            paradashechas++;
                        }
                    }
                    //Caso que no tenga que hacer parada aunque aun le falten paradas por hacer
                    else if (tipo == 2){
                        sleep((tiempovuelta/2));
                        carro->tiempoTotal = carro->tiempoTotal + tiempovuelta;
                    }
                    vueltascomp++;
                    printf("%s termino la vuelta %d en: %.2f s\n", carro->nombre, vueltascomp, carro->tiempoTotal);

                }
                //Caso que ya no tiene que hacer paradas
                else{
                    vueltascomp++;
                    sleep((tiempovuelta));
                    carro->tiempoTotal = carro->tiempoTotal + tiempovuelta;
                    printf("%s termino la vuelta %d en: %.2f s\n", carro->nombre, vueltascomp, carro->tiempoTotal);
                }
            }
            
        }
        //Impresion de finalizacion de carrera
        printf("%s METAAA!! termino la carrera en: %.2f s\n", carro->nombre, carro->tiempoTotal);
        
    }

    // Main
    int main(int argc, char* argv[]){
        int vueltas = 10;
        double pista = 0;
        int numeroCarros = 8;
        struct Carro carros[8];

        //Creacion de los 8 carros 
        for (int i = 0; i < 8; i++) {
            carros[i] = crearCarroAleatorio(i + 1);
        }

        //Impresion de estado inicial de los carros 
        printf("\n***FORUMULA 1***\n");
        printf("\nEstado inicial de los carros: \n");
        for (int i = 0; i < 8; i++) {
            printf("Carro %d - Nombre: %s, Velocidad: %.2lf m/s, Paradas: %.0lf\n", i + 1, carros[i].nombre, carros[i].velocidad, carros[i].paradas);
        }


        //Tamaño de la pista ingresada por usuario
        printf("\nIngresa la dimension de la pista en metros: ");
        scanf("%lf", &pista);

        printf("EMPIEZA LA CARRERA\n");

        //Simulacion de la Carrera
        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < 8; i++){
                simuladorCarrera(&carros[i],pista,vueltas);
            }
        }
        
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7 - i; j++) {
                if (carros[j].tiempoTotal > carros[j + 1].tiempoTotal) {
                    struct Carro temp = carros[j];
                    carros[j] = carros[j + 1];
                    carros[j + 1] = temp;
                }
            }
        }

        // Impresion de la tabla de resultados ordenados
        printf("\nTabla de resultados:\n");
        printf("Posicion\tNombre del Carro\tTiempo (s)\n");
        for (int i = 0; i < 8; i++) {
            printf("%d\t\t%s\t\t%.2lf\n", i + 1, carros[i].nombre, carros[i].tiempoTotal);
        }

        return 0;
    }