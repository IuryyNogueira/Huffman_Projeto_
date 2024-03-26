#ifndef pq_heap_h
#define pq_heap_h

typedef struct PriorityQueueHeap{
    int* heap_array; // Array que armazena os elementos do heap
    int capacity;    // Capacidade máxima do heap
    int size;        // Número atual de elementos no heap
} PriorityQueueHeap;

PriorityQueueHeap* create_priority_queue(int capacity);
int enqueueHeap(PriorityQueueHeap* pq, int data);
int dequeue(PriorityQueueHeap* pq);
int heapify_up(PriorityQueueHeap* pq, int index);
int heapify_down(PriorityQueueHeap* pq, int index);
int is_empty(PriorityQueueHeap* pq);
void destroy_priority_queue(PriorityQueueHeap* pq);

#endif /* pq_heap_h */
