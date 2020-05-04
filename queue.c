#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"



//To create a queue
queue* queue_init(int maxitems){
    queue *q = (queue *)malloc(sizeof(queue));
    q->length = maxitems; //tamaño maximo
    q->n_elementos= 0;
    q->colaElementos = malloc(maxitems * sizeof(struct element));
    q->head = 0;
    q->tail = -1;
    return q;
}


// To Enqueue an element
int queue_put(queue *q, struct element *x) {

    if(q->n_elementos == q->length) {
        printf("Error, cola está llena\n");
        return -1;
    } else {
        q->head = (q->head+1) % q->length; 
        memcpy(&(q->colaElementos[q->head]), x , sizeof(element)); // q.colaElementos[q.head] = x;
        q->n_elementos++;
    }
    return 0;
}


// To Dequeue an element.
struct element* queue_get(queue *q) {
    struct element *operacion = &(q->colaElementos[q->tail]);
    q->tail = (q->tail +1) % q->length;
    q->n_elementos--;
    return operacion;
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
    free(q->colaElementos);
    free(q);
    return 0;
}