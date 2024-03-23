#ifndef fila_prio_h
#define fila_prio_h

// Estrutura para representar um nó na fila de prioridade
typedef struct PriorityQueueNode {
    int value;
    int priority;
    struct PriorityQueueNode* next;
} PriorityQueueNode;

// Estrutura para representar a fila de prioridade
typedef struct {
    PriorityQueueNode* front;
} PriorityQueueNoHeap;

// Cria uma fila de prioridade vazia
PriorityQueueNoHeap* createPriorityQueueNoHeap();

// Insere um elemento na fila de prioridade
void enqueueNoHeap(PriorityQueueNoHeap* pq, int value, int priority);

// Remove e retorna o elemento de maior prioridade da fila de prioridade
int dequeueNoHeap(PriorityQueueNoHeap* pq);

// Remove um valor específico da fila de prioridade
void deleteValue(PriorityQueueNoHeap* pq, int value);

// Libera a memória alocada para a fila de prioridade
void destroyPriorityQueueNoHeap(PriorityQueueNoHeap* pq);

#endif /* fila_prio_h */
