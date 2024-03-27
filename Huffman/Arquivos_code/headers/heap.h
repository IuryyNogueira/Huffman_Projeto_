#ifndef HEAP_H
#define HEAP_H

// 0 --> 255 + 1 = 257
#define HEAP_MAX_SIZE 257

#include "typedefs.h"

//Fila de prioridade 
typedef struct HEAP HEAP;

struct HEAP {
    int size;
    void *data[HEAP_MAX_SIZE];
};

//Nó auxiliar 
typedef struct _node {
    lli priority;
    void *data; 
} _node;

_node* _create_node(lli priority, void *data);

HEAP *criar_heap();

int get_parent_index(int i);

int get_left_index(int i);

int get_right_index(int i);

void swap_data(void **item_1, void **item_2);

lli get_priority(HEAP *h, int index);

void enqueue(HEAP *heap, lli prioridade, void *data);

void min_heapify(HEAP *heap, int i);

void *dequeue(HEAP *heap);

void free_heap(HEAP *heap);


#endif //HEAP_H