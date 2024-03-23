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
        enqueueHeap(pqHeap, randomNumber);
        enqueueNoHeap(pqNoHeap, randomNumber);
    }
    
    return 0;
}
