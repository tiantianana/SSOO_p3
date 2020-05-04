#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"



//To create a queue
queue* queue_init(int maxitems){
    queue * q = (queue *)malloc(sizeof(queue));
    q->length = maxitems; //tamaño maximo
    q->size = 0;
    q->n_elementos= 0;
    q->colaElementos = malloc(maxitems * sizeof(struct element));
    q->enqueued = 0;
    q->dequeued = 0;
    q->head = 0;
    q->tail = -1;
    return q;
}


// To Enqueue an element
int queue_put(queue q, struct element x) {

    if(q->size == q->length) {
        printf("Error, cola está llena\n");
        return -1;
    } else {
        q->tail = q->tail+1;
        if(q->tail == q->length) q->tail = 0;
        q->size++;
        q->enqueued++;
    }
    return 0;
}


// To Dequeue an element.
struct element* queue_get(queue q) {
    struct element element;

    return element;
}


//To check queue state
int queue_empty(queue *q){
    if(q->n_elementos <=0){
        return 1;
    }else{
        return 0;
    }
}

int queue_full(queue *q){
    if(q->n_elementos >= q->length){
        return 1;
    }else{
        return 0;
    }
}

//To destroy the queue and free the resources
int queue_destroy(queue *q){
    //Si la cola esta llena no podemos añadir mas.
    //free(colaElementos);
    free(q);
    return 0;
}