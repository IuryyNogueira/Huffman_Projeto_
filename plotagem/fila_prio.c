#include <stdio.h>
#include <stdlib.h>
#include "fila_prio.h"

// Inicializa uma fila de prioridade vazia
PriorityQueue* create_priority_queueNoHeap() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila de prioridade.\n");
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

// Insere um elemento na fila de prioridade com base em sua prioridade
int enqueueNoHeap(PriorityQueue* pq, int data) {

    //inicializando o contador das iterações
    int i = 0;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data; //O(1)

    i++;

    //veriicando se o item inserido vai ser o novo front
    if (pq->front == NULL || data < pq->front->data) {
        
        newNode->next = pq->front;
        pq->front = newNode;
    } 
    else {

        Node* current = pq->front;
        while (current->next != NULL && data >= current->next->data) {
            i++;
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    return i;
}

// Remove e retorna o elemento de maior prioridade da fila de prioridade
int dequeueNoHeap(PriorityQueue* pq) {
    if (is_emptyNoHeap(pq)) {
        fprintf(stderr, "A fila de prioridade está vazia.\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = pq->front;
    int data = temp->data;
    pq->front = pq->front->next;
    free(temp);
    return data;
}

// Verifica se a fila de prioridade está vazia
int is_emptyNoHeap(PriorityQueue* pq) {
    return pq->front == NULL;
}

// Libera toda a memória alocada para a fila de prioridade
void destroy_priority_queueNoHeap(PriorityQueue* pq) {
    while (!is_emptyNoHeap(pq)) {
        dequeueNoHeap(pq);
    }
    free(pq);
}