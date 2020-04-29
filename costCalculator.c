
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
int main (int argc, const char * argv[] ) {

    if(argc < 4)
	{
		printf("No se han pasado suficientes argumentos\n");
		return -1;
	}
    int total = 0;
    int numeroProductores = atoi(argv[2]);
    printf("Total: %i €.\n", total);

    // ./calculator <file_name> <num. Producers> <buff. Size>

    FILE *id_fichero;
    id_fichero = fopen(argv[1], "r");
    
    /* // id_fichero no es un entero (es una estructura)
    if(id_fichero < 0){
		perror("error en la apertura del fichero especificado");
		exit(-1);
	}*/

    // INSERTAR DATOS (operaciones) en el array de elementos

    char *lineas; // = Obtener la primera linea del fichero (scanf)
    fscanf(id_fichero, "%s", lineas);
    int numeroLineas = atoi(lineas);
    printf("Líneas: %d \n", numeroLineas);

    // array de elementos con TODAS las operaciones (lo utilizarán los productores para pasar los datos al buffer circular)
    element *arrayOperaciones = malloc(numeroLineas * sizeof(element)); 
    printf("Acabo de reservar espacio \n"); 
    free(arrayOperaciones);

/*
    for(int i = 0; i < numeroLineas; i++) { // insertar cada linea
        element nuevaOperacion;
        char *indice;
        char *tipo;
        char *tiempo;
        // char *espacio;
        fscanf(id_fichero, "%s", indice);
        fscanf(id_fichero, "%s", tipo);
        fscanf(id_fichero, "%s", tiempo);
        nuevaOperacion.type = atoi(tipo);
        nuevaOperacion.time = atoi(tiempo);
        arrayOperaciones[i] = nuevaOperacion;

//        int indiceNum = atoi(indice);
        printf("Acabo de reservar fila %d \n", i);
    } 

    fclose(id_fichero);

    for(int i = 0; i < numeroLineas; i++) { // PRINT
        printf("%d %d \n", arrayOperaciones[i].time, arrayOperaciones[i].type);
    } 

    free(arrayOperaciones);

*/


/*
    queue bufferCircular;
    bufferCircular.length = argv[3];
    bufferCircular.arrayElementos = malloc(bufferCircular.length * sizeof(struct element));
    
*/
/*
    while(1 -> numProd){
        pthread_create(&th1, null, productor, null);
    }
    pthread_create(&th1, null, consumidor, null);

    pthread_join();
    ....

    pthread_mutex_destroy()
    destroy variables consumidor

free(); // libear fich
*/
    return 0;
}

/*
void productor(int inicio, int fin){
    ...



}
void consumidor(int inicio, int fin){
    ...
}

*/