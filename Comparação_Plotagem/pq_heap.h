#ifndef pq_heap_h
#define pq_heap_h

// Estrutura para representar a fila de prioridade com heap
typedef struct {
    int* arr;        // Array para armazenar os elementos
    int capacity;    // Capacidade máxima da fila de prioridade
    int size;        // Tamanho atual da fila de prioridade
} PriorityQueueHeap;

// Cria uma fila de prioridade vazia com heap
PriorityQueueHeap* createPriorityQueueHeap(int capacity);

// Insere um elemento na fila de prioridade com heap
void enqueueHeap(PriorityQueueHeap* pq, int value);

// Remove e retorna o elemento de maior prioridade da fila de prioridade com heap
int dequeueHeap(PriorityQueueHeap* pq);

// Deleta um valor específico da fila de prioridade com heap
void deleteValueHeap(PriorityQueueHeap* pq, int value);

// Libera a memória alocada para a fila de prioridade com heap
void destroyPriorityQueueHeap(PriorityQueueHeap* pq);

#endif /* pq_heap_h */
