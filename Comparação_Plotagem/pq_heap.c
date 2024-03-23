#include <stdio.h>
#include <stdlib.h>
#include "pq_heap.h"

PriorityQueueHeap* createPriorityQueueHeap(int capacity) {
    PriorityQueueHeap* pq = (PriorityQueueHeap*)malloc(sizeof(PriorityQueueHeap));
    if (pq == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila de prioridade com heap.\n");
        exit(EXIT_FAILURE);
    }
    pq->arr = (int*)malloc(capacity * sizeof(int));
    if (pq->arr == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array da fila de prioridade com heap.\n");
        exit(EXIT_FAILURE);
    }
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueueHeap* pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->arr[index] > pq->arr[parent]) {
        swap(&pq->arr[index], &pq->arr[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void enqueueHeap(PriorityQueueHeap* pq, int value) {
    if (pq->size == pq->capacity) {
        fprintf(stderr, "A fila de prioridade com heap está cheia.\n");
        exit(EXIT_FAILURE);
    }
    pq->arr[pq->size] = value;
    heapifyUp(pq, pq->size);
    pq->size++;
}

void heapifyDown(PriorityQueueHeap* pq, int index) {
    int leftChild, rightChild, maxChild;
    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        maxChild = index;
        if (leftChild < pq->size && pq->arr[leftChild] > pq->arr[maxChild]) {
            maxChild = leftChild;
        }
        if (rightChild < pq->size && pq->arr[rightChild] > pq->arr[maxChild]) {
            maxChild = rightChild;
        }
        if (maxChild == index) {
            break;
        }
        swap(&pq->arr[index], &pq->arr[maxChild]);
        index = maxChild;
    }
}

int dequeueHeap(PriorityQueueHeap* pq) {
    if (pq->size == 0) {
        fprintf(stderr, "A fila de prioridade com heap está vazia.\n");
        exit(EXIT_FAILURE);
    }
    int maxValue = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return maxValue;
}

void deleteValueHeap(PriorityQueueHeap* pq, int value) {
    int i;
    for (i = 0; i < pq->size; i++) {
        if (pq->arr[i] == value) {
            // Element found, perform deletion
            pq->arr[i] = pq->arr[pq->size - 1];
            pq->size--;
            heapifyDown(pq, i);
            return; // Element deleted
        }
    }
    
}

void destroyPriorityQueueHeap(PriorityQueueHeap* pq) {
    free(pq->arr);
    free(pq);
}
