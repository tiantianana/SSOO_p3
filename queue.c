#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"
#include <pthread.h>


//To create a queue
queue* queue_init(int maxitems){
    queue *q = (queue *)malloc(sizeof(queue));
    q->length = maxitems;
    q->n_elementos= 0;
    q->colaElementos = malloc(maxitems * sizeof(struct element));
    q->head = 0;
    q->tail = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->no_lleno, NULL);
    pthread_cond_init(&q->no_vacio,NULL);
    return q;
}


// To Enqueue an element
int queue_put(queue *q, struct element *x) {
    pthread_mutex_lock(&q->mutex);
    while(queue_full(q)) { // si la cola está llena, se bloquea hasta que el consumidor le indique que ya quedan huecos
        pthread_cond_wait(&q->no_lleno, &q->mutex);
    }
    (q->colaElementos[q->head]).time = x->time;
    (q->colaElementos[q->head]).type = x->type;
    q->head = (q->head+1) % q->length;
    q->n_elementos++;
    pthread_cond_signal(&q->no_vacio); // indica al consumidor que la cola no está vacía
    pthread_mutex_unlock(&q->mutex); 
    return 0;
}


// To Dequeue an element.
struct element* queue_get(queue *q) {
    pthread_mutex_lock(&q->mutex);
    while(queue_empty(q)) { // si la cola está vacía, se bloquea hasta que un productor le indique que ya hay un elem que procesar
        pthread_cond_wait(&q->no_vacio, &q->mutex);
    }
    element *operacion = malloc(sizeof(element));  // Transferimos liberacion de memoria al hilo consumidor
    operacion->time = (q->colaElementos[q->tail]).time;
    operacion->type = (q->colaElementos[q->tail]).type;
    q->tail = (q->tail +1) % q->length;
    q->n_elementos--;
    pthread_cond_signal(&q->no_lleno); // indica al consumidor que la cola no está vacía
    pthread_mutex_unlock(&q->mutex);
    return operacion;
}


//To check queue state
int queue_empty(queue *q){
    return q->n_elementos == 0;
}

int queue_full(queue *q){
    return q->n_elementos == q->length;
}

//To destroy the queue and free the resources
int queue_destroy(queue *q){
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->no_lleno);
    pthread_cond_destroy(&q->no_vacio);
    free(q->colaElementos);
    free(q);
    return 0;
}