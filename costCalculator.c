
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
element *arrayOperaciones;
queue *bufferCircular;

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

    // --------- INSERCIÓN DE DATOS (operaciones) en un array de elementos ---------------------------------------------------

    int numeroOperaciones; 
    fscanf(id_fichero, "%d", &numeroOperaciones);

    // array de elementos con TODAS las operaciones (lo utilizarán los productores para pasar los datos al buffer circular)
    *arrayOperaciones = malloc(numeroOperaciones * sizeof(element)); 

    for(int i = 0; i < numeroOperaciones; i++) { // insertar cada linea
        element nuevaOperacion;
        int indice;
        fscanf(id_fichero, "%d", &indice);
        fscanf(id_fichero, "%d", &nuevaOperacion.type);
        fscanf(id_fichero, "%d", &nuevaOperacion.time);
        arrayOperaciones[i] = nuevaOperacion;
    } 

    fclose(id_fichero);

/* ------ PRINT --------

    for(int i = 0; i < numeroOperaciones; i++) { 
        printf("%d %d \n", arrayOperaciones[i].type, arrayOperaciones[i].time);
    } 
*/ 


// --------- DIVISIÓN DE TAREAS POR HILO PRODUCTOR (ej: 7 operaciones para 5 hilos = 2,2,1,1,1) ------------

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

// -------------------------------- CREACIÓN DE BUFFER E HILOS --------------------------------
    
    bufferCircular =  queue_init(atoi(argv[3]));

    argumentos args; // Preparamos los argumentos de la función de los hilos productores
    args.inicio = 0;
    args.final = 0;
    pthread_t threads[numeroProductores];
    int i = 0;

    while(i < numeroProductores){
        args.final = args.inicio + operacionesPorProductor[i] - 1;
        pthread_create(&threads[i], NULL, &productor, &args); 
        args.inicio = args.final + 1; // 2
        i++;
    }

    pthread_t th_productor;
    pthread_create(&th_productor, NULL, &consumidor, NULL);

// --------------------------------FINALIZACIÓN DE HILOS Y BUFFER --------------------------------

    int j = 0;
    while(j < numeroProductores) {
        pthread_join(threads[j], NULL);
        j++;
    }

    pthread_join(th_productor, NULL); // OBTENER VALOR DE RETORNO (COSTE TOTAL) (?)

    queue_destroy(bufferCircular);

// ------------------------- LIBERAMOS ESPACIO Y DEVOLVEMOS COSTE TOTAL --------------------------

    free(arrayOperaciones);
    printf("Total: %i €.\n", total);
    return 0;

}



// ----------  FUNCIONES PRODUCTOR Y CONSUMIDOR (y definirlas en queue.h) ------------



void* productor(void* x) { // argumentos int inicio, int fin
    //    ...
    //int* my_param = (int*)x;

    return NULL;
}
void* consumidor(void* x) { // argumentos int inicio, int fin
    // ...

    //while(queue_empty) -> BLOQUEAR CON WAIT(no_vacio);
   // queue_get(q)

    return NULL;
}
