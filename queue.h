#ifndef HEADER_FILE
#define HEADER_FILE


typedef struct element {
  int type; //Machine type
  int time; //Using time
}element;

typedef struct queue {
	// Define the struct yourself
  struct element *colaElementos;
	int length;
  int n_elementos; // numero de operaciones dentro del buffer
}queue;

queue* queue_init (int size);
int queue_destroy (queue *q);
int queue_put (queue *q, struct element* elem);
struct element * queue_get(queue *q);
int queue_empty (queue *q);
int queue_full(queue *q);

void *productor ();
void *consumidor ();
#endif
