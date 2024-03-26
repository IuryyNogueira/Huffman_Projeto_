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
void enqueueNoHeap(PriorityQueue* pq, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o novo nó.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    if (pq->front == NULL || data < pq->front->data) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        Node* current = pq->front;
        while (current->next != NULL && data >= current->next->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
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

// Remove o elemento especificado da fila de prioridade
int delete_valueNoHeap(PriorityQueue* pq, int value) {
    
    int i = 0;
    if (is_emptyNoHeap(pq)) { //nao vai estar vazia nesse projeto
        fprintf(stderr, "A fila de prioridade está vazia.\n");
        exit(EXIT_FAILURE);
    }

    // Caso o valor esteja na frente da fila
    if (pq->front != NULL && pq->front->data == value) {
        i++;
        Node* temp = pq->front;
        pq->front = pq->front->next;
        free(temp);
    }

    // Caso o valor esteja em outros lugares na fila
    Node* current = pq->front;
    while (current != NULL && current->next != NULL) {
        i++;
        if (current->next->data == value) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return i;
}


// Libera toda a memória alocada para a fila de prioridade
void destroy_priority_queueNoHeap(PriorityQueue* pq) {
    while (!is_emptyNoHeap(pq)) {
        dequeueNoHeap(pq);
    }
    free(pq);
}