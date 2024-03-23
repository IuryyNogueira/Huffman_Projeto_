#include "fila_prio.h"
#include <stdio.h>
#include <stdlib.h>

PriorityQueueNoHeap* createPriorityQueueNoHeap(int capacity) {
    PriorityQueueNoHeap* pq = (PriorityQueueNoHeap*)malloc(sizeof(PriorityQueueNoHeap));
    pq->arr = (int*)malloc(capacity * sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void enqueueNoHeap(PriorityQueueNoHeap* pq, int value) {
    if (pq->size == pq->capacity) {
        printf("A fila de prioridade sem heap está cheia.\n");
        return;
    }
    int index = pq->size;
    while (index > 0 && pq->arr[(index - 1) / 2] < value) {
        pq->arr[index] = pq->arr[(index - 1) / 2];
        index = (index - 1) / 2;
    }
    pq->arr[index] = value;
    pq->size++;
}

int dequeueNoHeap(PriorityQueueNoHeap* pq) {
    if (pq->size == 0) {
        printf("A fila de prioridade sem heap está vazia.\n");
        return -1;
    }
    int maxValue = pq->arr[0];
    int lastValue = pq->arr[pq->size - 1];
    pq->size--;
    int index = 0;
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild >= pq->size) {
            break;
        }
        int maxChild = leftChild;
        if (rightChild < pq->size && pq->arr[rightChild] > pq->arr[leftChild]) {
            maxChild = rightChild;
        }
        if (lastValue >= pq->arr[maxChild]) {
            break;
        }
        pq->arr[index] = pq->arr[maxChild];
        index = maxChild;
    }
    pq->arr[index] = lastValue;
    return maxValue;
}

void destroyPriorityQueueNoHeap(PriorityQueueNoHeap* pq) {
    free(pq->arr);
    free(pq);
}
