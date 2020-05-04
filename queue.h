#ifndef HEADER_FILE
#define HEADER_FILE


typedef struct element {
  int type; //Machine type
  int time; //Using time
}element;

typedef struct argumentos {
  element *arrayOperaciones;
  int inicio; //Machine type
  int final; //Using time
}argumentos;
typedef struct queue {
  element *colaElementos;
  int length;
  int n_elementos; // numero de operaciones dentro del buffer
  int head;
  int tail;
  pthread_mutex_t mutex;
  pthread_cond_t no_lleno;
  pthread_cond_t no_vacio;
} queue;

queue* queue_init (int maxitems);
int queue_destroy (queue *q);
int queue_put (queue *q, struct element *elem);
struct element * queue_get(queue *q);
int queue_empty (queue *q);
int queue_full(queue *q);

void *productor ();
void *consumidor ();
#endif