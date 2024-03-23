#ifndef pq_heao_h
#define pq_heao_h

typedef struct PriorityQueueHeap {
    int *arr;
    int size;
    int capacity;
} PriorityQueueHeap;

PriorityQueueHeap* createPriorityQueueHeap(int capacity);
void enqueueHeap(PriorityQueueHeap* pq, int value, int priority);
int dequeueHeap(PriorityQueueHeap* pq);
void deleteValueHeap(PriorityQueueHeap* pq, int value);
void destroyPriorityQueueHeap(PriorityQueueHeap* pq);

#endif /* pq_heao_h */
