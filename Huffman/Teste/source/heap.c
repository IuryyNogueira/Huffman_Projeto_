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

    // loop para inicializar a heap ---> limpando 
    for (int i = 1; i < HEAP_MAX_SIZE; ++i)
    {
        heap->data[i] = NULL;
    }

    // heap pronto para para o trabalho 
    return heap;
}

int get_parent_index(int i){ 
    return (i / 2);
}

int get_left_index(int i){
    return (2 * i);
} 

int get_right_index(int i) {
    return (2 * i + 1);
}


// ** pq passamos um endereco de memoria
void swap(void **item_1, void **item_2)
{
    void *aux = *item_1;
    *item_1 = *item_2;
    *item_2 = aux;
}
// retorna a prioridade do nó da arvore 
lli get_priority(HEAP *h, int indice)
{
    return ((_node *) h->data[indice])->priority;
}

//nós bytes/ frequencia / heap inicial(size | *data[] --> para os nós que vão guardar os nós da arvore)
void enqueue(HEAP *heap, lli prioridade, void *data)
{
    // passou dos tipos possiveis?
    if (heap->size >= HEAP_MAX_SIZE - 1) printf("Heap overflow\n");
   
    else
    {   
        // _node é definido em heap.h
        // que vai armazenar o nó da arvore
        _node *new_node = _create_node(prioridade, data);

        // em heap->data[++heap->size]  ++ é pra começar pelo 1 | é uma HEAP |
        // pq heap->size começa em 0 e nossa struct heap em *data[tem 257]
        // E add em size 
        heap->data[++heap->size] = new_node;

        // index do nó que acabou de ser adicionado
        int chave_index = heap->size;

        // index do pai do nó que acabou de ser adicionado
        // (chave_index / 2);
        int parent_index = get_parent_index(chave_index);

        // manter a propriedade de heap 
        // movendo o novo elemento para a posição correta
        while (parent_index >= 1 && get_priority(heap, chave_index) < get_priority(heap, parent_index))
        {
            // se freq do (nó arvore)do atual for menor que a do pai
            // troca os nós
            swap (&heap->data[parent_index], &heap->data[chave_index]);

            //troca
            chave_index = parent_index;
            parent_index = get_parent_index(chave_index);
        }
    }
}

// manter a propriedade de heap
void min_heapify(HEAP *heap, int i)
{
    int o_menor;

    // index do filho esquerdo no atual
    int left_index = get_left_index(i);

    // index do filho direito 
    int right_index = get_right_index(i);

    // Obtém ponteiros para os nós atual, esquerdo e direito na heap.
    _node *t = heap->data[i];
    _node *t_l = heap->data[left_index];
    _node *t_r = heap->data[right_index];

    // Verifica se o nó esquerdo existe na heap e se sua prioridade
    // é menor do que a prioridade do nó atual.
    if (left_index <= heap->size && t_l->priority < t->priority)
    {
        // vira o indice do filho esquerdo
        o_menor = left_index;
    }
    else
    {
        o_menor = i;
    }

    // preparo 2 verificacao
    _node *t_menor = heap->data[o_menor];

    // Verifica se o nó direito existe na heap e se sua prioridade 
    // é menor do que a prioridade do nó atual ou do nó esquerdo, se já foi definido como o menor.
    if (right_index <= heap->size && t_r->priority < t_menor->priority)
    {
        o_menor = right_index;
        t_menor = heap->data[o_menor];
    }

    // Verifica se o nó atual é diferente do nó de menor prioridade. Se forem diferentes, 
    // significa que a propriedade de heap é violada e é necessária uma troca.
    if (t != t_menor)
    {
        // troca os nós
        swap(&heap->data[i], &heap->data[o_menor]);
        // chama recursivamente a função para o nó de menor prioridade.
        min_heapify(heap, o_menor);
    }
}


// usado criar arvore de huffman
void *dequeue(HEAP *heap)
{
    if (!(heap->size))
    {
        printf("Heap underflow.\n");
        return NULL;
    }
    else
    {
        // extrai elemento menor prioridade da heap
        _node *item = (_node *) heap->data[1];

        // troca o menor elemento com o ultimo elemento
        heap->data[1] = heap->data[heap->size];

        // remove o ultimo elemento
        heap->data[heap->size] = NULL;

        // decrementa o tamanho da heap
        heap->size -= 1;

        // mantem a propriedade de heap
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
