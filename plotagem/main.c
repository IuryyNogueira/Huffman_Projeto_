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

    // Gerando e inserindo números aleatórios em ambas as filas
    for (int i = 0; i < MAX_SIZE; i++) {
        int randomNumber = rand() % 100000; // Gera números aleatórios entre 0 e 99999
        enqueueHeap(pqHeap, randomNumber);
        enqueueNoHeap(pqNoHeap, randomNumber);
    }

    // Abrir o arquivo para escrita
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }
    
    for (int i = 0; i < 10000; i++){
        int randomNumber = rand() % 100000;
        int heap = delete_value(pqHeap, randomNumber);
        int noHeap = delete_valueNoHeap(pqNoHeap, randomNumber);
        
        // Escrever os valores deletados no arquivo
        fprintf(file, "%d %d\n", noHeap, heap);
    }
    
    // Fechar o arquivo
    fclose(file);

    return 0;
}
