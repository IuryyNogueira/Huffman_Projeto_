#ifndef fila_prio
#define fila_prio

typedef struct PriorityQueueNoHeap{
    int *arr;
    int size;
    int capacity;
} PriorityQueueNoHeap;

PriorityQueueNoHeap* createPriorityQueueNoHeap(int capacity);
void enqueueNoHeap(PriorityQueueNoHeap* pq, int value, int priority);
int dequeueNoHeap(PriorityQueueNoHeap* pq);
void deleteValue(PriorityQueueNoHeap* pq, int value);
void destroyPriorityQueueNoHeap(PriorityQueueNoHeap* pq);

#endif /* fila_prio */
