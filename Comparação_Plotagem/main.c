#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila_prio.h"
#include "pq_heap.h"

#define MAX_SIZE 40000

int main() {
    // Inicializando a semente para gerar números aleatórios
    srand(time(NULL));

    // Criando fila de prioridade com heap e sem heap
    PriorityQueueHeap* pqHeap = createPriorityQueueHeap(MAX_SIZE);
    PriorityQueueNoHeap* pqNoHeap = createPriorityQueueNoHeap(MAX_SIZE);

    // Gerando e inserindo números aleatórios em ambas as filas
    for (int i = 0; i < MAX_SIZE; i++) {
        int randomNumber = rand() % 100000; // Gera números aleatórios entre 0 e 99999
        int randomPriority = rand() % 3; // Gera números aleatórios entre 0 e 2 para a prioridade
        enqueueHeap(pqHeap, randomNumber, randomPriority);
        enqueueNoHeap(pqNoHeap, randomNumber, randomPriority);
    }
    
    return 0;
}

