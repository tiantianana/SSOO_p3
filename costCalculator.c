
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <pthread.h>
#include "queue.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUM_CONSUMERS 1

/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */

pthread_mutex_t mutex;
pthread_cond_t no_lleno;
pthread_cond_t no_vacio;

int main (int argc, const char * argv[] ) { // ./calculator <file_name> <num. Producers> <buff. Size>

    if(argc != 4)
	{
		printf("No se han pasado suficientes argumentos\n");
		return -1;
	}
    
    int total = 0;
    int numeroProductores = atoi(argv[2]);
    FILE *id_fichero = fopen(argv[1], "r");
    
    if(id_fichero == NULL){
		perror("error en la apertura del fichero especificado");
		exit(-1);
	}

    // --------- INSERTAR DATOS (operaciones) en un array de elementos ---------------------------------------------------

    int numeroOperaciones; 
    fscanf(id_fichero, "%d", &numeroOperaciones);

    // array de elementos con TODAS las operaciones (lo utilizarán los productores para pasar los datos al buffer circular)
    element *arrayOperaciones = malloc(numeroOperaciones * sizeof(element)); 

    for(int i = 0; i < numeroOperaciones; i++) { // insertar cada linea
        element nuevaOperacion;
        int indice;
        fscanf(id_fichero, "%d", &indice);
        fscanf(id_fichero, "%d", &nuevaOperacion.type);
        fscanf(id_fichero, "%d", &nuevaOperacion.time);
        arrayOperaciones[i] = nuevaOperacion;
    } 

    fclose(id_fichero);

/*
    for(int i = 0; i < numeroOperaciones; i++) { // PRINT
        printf("%d %d \n", arrayOperaciones[i].type, arrayOperaciones[i].time);
    } 
*/ 
/* ----------- CREAR BUFFER CIRCULAR (reservar el espacio especificado) ---------------------*/

    queue *bufferCircular =  queue_init(atoi(argv[3]));

    // DIVIDIR OPERACIONES (INDICES) ENTRE HILOS ...

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&no_lleno, NULL);
    pthread_cond_init(&no_vacio,NULL);


// Definimos en un array el numero de operaciones de cada productor (ej: 7 operaciones para 5 hilos = 2,2,1,1,1)
    int operacionesPorProductor [numeroProductores];
    int k = numeroOperaciones;
    while(k > 0){
        if(k == numeroOperaciones){ // Primera iteracion
            for(int i = 0; i < numeroProductores; i++){
                operacionesPorProductor[i] = 0;
            } 
        }
        for(int i = 0; i < numeroProductores; i++){
           if(k == 0){
                break;
            }           
            operacionesPorProductor[i] ++;
            k--;
        }
    }

    printf("Número operaciones %d \n", numeroOperaciones); // PRINT
    for(int i = 0; i < numeroProductores; i++) { 
        printf("%d \n", operacionesPorProductor[i]);
    } 


    int inicio = 0;
    int final = 0;
    pthread_t threads[numeroProductores];
    int i = 0;

// 0 1 | 2 3 | 4 | 5 | 6


    while(i < numeroProductores){
        final = inicio + operacionesPorProductor[i] - 1; // 
        pthread_create(&threads[i], NULL, productor, NULL); // PASAR LOS INDICES DE OPERACIONES
        inicio = final + 1; // 2
        i++;
    }


    pthread_t *th_productor;
    pthread_create(th_productor, NULL, consumidor, NULL);


    int j = 0;
    while(j < numeroProductores) {
        pthread_join(threads[j], NULL);
        j++;
    }

    //pthread_join(threads[j], NULL); // OBTENER VALOR DE RETORNO (COSTE TOTAL) (?)
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&no_lleno);
    pthread_cond_destroy(&no_vacio);


    free(arrayOperaciones);
    printf("Total: %i €.\n", total);
    return 0;

}



// ---------- CREAR LAS FUNCIONES PRODUCTOR Y CONSUMIDOR (y definirlas en queue.h) ------------


void *productor() { // argumentos int inicio, int fin
//    ...

}
void *consumidor() { // argumentos int inicio, int fin
    // ...

}
