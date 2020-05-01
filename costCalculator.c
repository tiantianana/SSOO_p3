
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

    for(int i = 0; i < numeroOperaciones; i++) { // PRINT
        printf("%d %d \n", arrayOperaciones[i].type, arrayOperaciones[i].time);
    } 

    free(arrayOperaciones);



/* ----------- CREAR BUFFER CIRCULAR (reservar el espacio especificado) ---------------------*/

    queue bufferCircular;
    bufferCircular.length = argv[3];
    bufferCircular.arrayElementos = malloc(bufferCircular.length * sizeof(struct element));
    
    queue_init(argv[3]); 

// ...
    
    

/* ------------ CREAR HILOS, SEMÁFOROS Y VARIABLES CONDICIONALES------------------------------
// A los hilos hay que pasarles el rango de operaciones a insertar en el buffer, y la dirección de inicio del buffer (?). 
    
    while(1 -> numProd){
        pthread_create(&th1, null, productor, null);
    }
    pthread_create(&th1, null, consumidor, null);

// ESPERAR A QUE TERMINEN TODOS LOS HILOS Y DESTRUIR LOS SEMAFOROS Y VARIABLES CONDICIONALES
// Recoger la suma total del hilo consumidor (la tiene que devolver)

    pthread_join();
    ....

    pthread_mutex_destroy()
    destroy variables consumidor
*/

    printf("Total: %i €.\n", total);
    return 0;
}



// ---------- CREAR LAS FUNCIONES PRODUCTOR Y CONSUMIDOR (y definirlas en queue.h) ------------

/*
void productor(int inicio, int fin){
    ...



}
void consumidor(int inicio, int fin){
    ...
}

*/