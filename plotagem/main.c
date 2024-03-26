#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fila_prio.h"
#include "pq_heap.h"

#define MAX_SIZE 40000

int main() {
    // Inicializando a semente para gerar números aleatórios
    srand(time(NULL) ^ getpid());

    // Criando fila de prioridade com heap e sem heap
    PriorityQueueHeap* pqHeap = create_priority_queue(MAX_SIZE);
    PriorityQueue* pqNoHeap = create_priority_queueNoHeap(MAX_SIZE);

    // Abrir o arquivo para escrita
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }
    
    // Gerando e inserindo números aleatórios em ambas as filas
    for (int i = 0; i < MAX_SIZE; i++) {
        int randomNumber = rand() % 100000; // Gera números aleatórios entre 0 e 99999
        int heap = enqueueHeap(pqHeap, randomNumber);
        int noHeap = enqueueNoHeap(pqNoHeap, randomNumber);
        
        // Escrever as iterações, para inserir os valores na heap, no arquivo
        fprintf(file, "%d %d\n", noHeap, heap);
    }
    
    // Fechar o arquivo
    fclose(file);

    return 0;
}
