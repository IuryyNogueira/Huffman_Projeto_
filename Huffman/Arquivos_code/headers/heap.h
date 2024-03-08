#ifndef HUFFMAN_HEAP_H
#define HUFFMAN_HEAP_H

#define HEAP_MAX_SIZE 257

#include "typedefs.h"

/** Heap - Fila de prioridade **/
typedef struct HEAP HEAP;
struct HEAP {
    int size;
    void *data[HEAP_MAX_SIZE];
};

/** Nó auxiliar **/
typedef struct _node {
    lli priority;
    void *data;
} _node;



#endif //HUFFMAN_HEAP_H