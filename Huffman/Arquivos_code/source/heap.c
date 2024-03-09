#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "func_extras.h"

// Estrutura de um nó da heap

_node* _create_node(lli priority, void *data)
{
    _node *new_node = (_node *) malloc(sizeof(_node));
    mallocou(new_node);

    new_node->priority = priority;
    new_node->data = data;

    return new_node;
}

// Estrutura da heap 

HEAP *criar_heap()
{
    HEAP *heap = (HEAP *) malloc(sizeof(HEAP));
    mallocou(heap);

    heap->size = 0;

    for (int i = 1; i < HEAP_MAX_SIZE; ++i)
    {
        heap->data[i] = NULL;
    }

    return heap;
}

int get_parent_index(int i)
{
    return (i / 2);
}

int get_left_index(int i)
{
    return (2 * i);
}

int get_right_index(int i)
{
    return (2 * i + 1);
}

void swap_data(void **item_1, void **item_2)
{
    void *aux = *item_1;
    *item_1 = *item_2;
    *item_2 = aux;
}

lli get_priority(HEAP *h, int index)
{
    return ((_node *) h->data[index])->priority;
}

//foco aqui
void enqueue(HEAP *heap, lli prioridade, void *data)
{
    if (heap->size >= HEAP_MAX_SIZE - 1)
    {
        printf("Heap overflow\n");
    }
    else
    {
        _node *new_node = _create_node(priority, data);

        heap->data[++heap->size] = new_node;

        int chave_index = heap->size;

        int parent_index = get_parent_index(chave_index);

        while (parent_index >= 1 && get_priority(heap, chave_index) < get_priority(heap, parent_index))
        {
            swap_data(&heap->data[parent_index], &heap->data[chave_index]);

            chave_index = parent_index;

            parent_index = get_parent_index(chave_index);
        }
    }
}

void min_heapify(HEAP *heap, int i)
{
    int o_menor;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);

    _node *t = heap->data[i];
    _node *t_l = heap->data[left_index];
    _node *t_r = heap->data[right_index];

    if (left_index <= heap->size && t_l->priority < t->priority)
    {
        o_menor = left_index;
    }
    else
    {
        o_menor = i;
    }

    _node *t_menor = heap->data[o_menor];

    if (right_index <= heap->size && t_r->priority < t_menor->priority)
    {
        o_menor = right_index;
        t_menor = heap->data[o_menor];
    }

    if (t != t_menor)
    {
        swap_data(&heap->data[i], &heap->data[o_menor]);
        min_heapify(heap, o_menor);
    }
}
//foca aqui
void *dequeue(HEAP *heap)
{
    if (!(heap->size))
    {
        printf("Heap underflow.\n");
        return NULL;
    }
    else
    {
        _node *item = (_node *) heap->data[1];

        heap->data[1] = heap->data[heap->size];

        heap->data[heap->size] = NULL;

        heap->size -= 1;

        min_heapify(heap, 1);

        return item->data;
    }
}

void free_heap(HEAP *heap)
{
    for (int i = 1; i <= heap->size; ++i)
    {
        free((_node *) heap->data[i]);
    }
    free(heap);
}
