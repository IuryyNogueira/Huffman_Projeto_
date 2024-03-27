#include <stdio.h>
#include <stdlib.h>
#include "pq_heap.h"


// Função para criar uma nova fila de prioridade
PriorityQueueHeap* create_priority_queue(int capacity) {
    PriorityQueueHeap* pq = (PriorityQueueHeap*)malloc(sizeof(PriorityQueueHeap));
    if (pq == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila de prioridade.\n");
        exit(EXIT_FAILURE);
    }
    pq->capacity = capacity;
    pq->size = 0;
    pq->heap_array = (int*)malloc(capacity * sizeof(int));
    if (pq->heap_array == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array do heap.\n");
        exit(EXIT_FAILURE);
    }
    return pq;
}

// Função para ajustar o heap após a inserção de um novo elemento
int heapify_up(PriorityQueueHeap* pq, int index) { // index é o indice do elemento que adcionamos

    int i = 0;
    int* heap_array = pq->heap_array; //O(1)
    while (index > 0 && heap_array[index] < heap_array[(index - 1) / 2]) {
        i++;
        int temp = heap_array[index];
        heap_array[index] = heap_array[(index - 1) / 2];
        heap_array[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }

    return i;
}

// Função para inserir um novo elemento na fila de prioridade
int enqueueHeap(PriorityQueueHeap* pq, int data) {

    int i = 0;

    //verificando se a fila esta cheia
    if (pq->size == pq->capacity) { //nesse projeto nao vai passar do limite pq vamos inserir o tamanho certo de numeros
        fprintf(stderr, "A fila de prioridade está cheia.\n");
        exit(EXIT_FAILURE);
    } //O(1)
    
    pq->heap_array[pq->size++] = data; //O(1)
    i += heapify_up(pq, pq->size - 1);

    return i;
}

// Função para ajustar o heap após a remoção do elemento de maior prioridade
int heapify_down(PriorityQueueHeap* pq, int index) {
    int* heap_array = pq->heap_array;
    int comparisons = 0; // Variável para contar as comparações
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < pq->size) {
        comparisons++; // Incrementa o número de comparações
        if (heap_array[left_child] < heap_array[smallest]) {
            smallest = left_child;
        }
    }

    if (right_child < pq->size) {
        comparisons++; // Incrementa o número de comparações
        if (heap_array[right_child] < heap_array[smallest]) {
            smallest = right_child;
        }
    }

    if (smallest != index) {
        int temp = heap_array[index];
        heap_array[index] = heap_array[smallest];
        heap_array[smallest] = temp;
        // Chama heapify_down recursivamente para o nó filho alterado
        comparisons += heapify_down(pq, smallest);
    }

    return comparisons; // Retorna o número total de comparações realizadas
}


// Função para remover e retornar o elemento de maior prioridade da fila de prioridade
int dequeue(PriorityQueueHeap* pq) {
    if (is_empty(pq)) {
        fprintf(stderr, "A fila de prioridade está vazia.\n");
        exit(EXIT_FAILURE);
    }
    int top_element = pq->heap_array[0];
    pq->heap_array[0] =pq->heap_array[pq->size - 1];
    pq->size--;
    heapify_down(pq, 0);
    return top_element;
}

// Função para verificar se a fila de prioridade está vazia
int is_empty(PriorityQueueHeap* pq) {
    return pq->size == 0;
}

// Função para liberar a memória alocada para a fila de prioridade
void destroy_priority_queue(PriorityQueueHeap* pq) {
    free(pq->heap_array);
    free(pq);
}
