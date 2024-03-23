#ifndef fila_prio_h
#define fila_prio_h

// Estrutura para representar um nó da fila de prioridade
typedef struct node {
    int data;
    struct node* next;
} Node;

// Estrutura para representar uma fila de prioridade
typedef struct {
    Node* front;
} PriorityQueue;

// Inicializa uma fila de prioridade vazia
PriorityQueue* create_priority_queueNoHeap();

// Insere um elemento na fila de prioridade com base em sua prioridade
void enqueueNoHeap(PriorityQueue* pq, int data);

// Remove e retorna o elemento de maior prioridade da fila de prioridade
int dequeueNoHeap(PriorityQueue* pq);

// Verifica se a fila de prioridade está vazia
int is_emptyNoHeap(PriorityQueue* pq);

// Remove o elemento especificado da fila de prioridade
void delete_valueNoHeap(PriorityQueue* pq, int value);

// Libera toda a memória alocada para a fila de prioridade
void destroy_priority_queueNoHeap(PriorityQueue* pq);

#endif /* fila_prio_h */
