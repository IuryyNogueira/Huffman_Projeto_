#include <stdio.h>
#include <stdlib.h>
#include "fila_prio.h"

PriorityQueueNoHeap* createPriorityQueueNoHeap() {
    PriorityQueueNoHeap* pq = (PriorityQueueNoHeap*)malloc(sizeof(PriorityQueueNoHeap));
    if (pq == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila de prioridade.\n");
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

void enqueueNoHeap(PriorityQueueNoHeap* pq, int value, int priority) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->priority = priority;
    newNode->next = NULL;

    // Se a fila estiver vazia ou se o novo elemento tiver prioridade maior do que o primeiro elemento
    if (pq->front == NULL || priority > pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        PriorityQueueNode* current = pq->front;
        // Procurar o local de inserção do novo elemento
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int dequeueNoHeap(PriorityQueueNoHeap* pq) {
    if (pq->front == NULL) {
        fprintf(stderr, "A fila de prioridade sem heap está vazia.\n");
        exit(EXIT_FAILURE);
    }
    PriorityQueueNode* temp = pq->front;
    int value = temp->value;
    pq->front = pq->front->next;
    free(temp);
    return value;
}

void deleteValue(PriorityQueueNoHeap* pq, int value) {
    if (pq->front == NULL) {
        fprintf(stderr, "A fila de prioridade sem heap está vazia.\n");
        return;
    }
    PriorityQueueNode* current = pq->front;
    PriorityQueueNode* prev = NULL;
    // Procurar o nó com o valor especificado
    while (current != NULL && current->value != value) {
        prev = current;
        current = current->next;
    }
    // Se o valor não foi encontrado
    if (current == NULL) {
        printf("Valor não encontrado na fila de prioridade.\n");
        return;
    }
    // Se o nó com o valor foi encontrado
    if (prev == NULL) {
        // Se o nó está no início da fila
        pq->front = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}

void destroyPriorityQueueNoHeap(PriorityQueueNoHeap* pq) {
    while (pq->front != NULL) {
        PriorityQueueNode* temp = pq->front;
        pq->front = pq->front->next;
        free(temp);
    }
    free(pq);
}
