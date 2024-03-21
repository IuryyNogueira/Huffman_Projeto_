#include "func_extras.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "arvore_huffman.h"

void criacao_fila_prioridade(lli frequencia[], HEAP *heap) {
    int i;
    for (i = 0; i < 256; i++) {
        if (frequencia[i] != 0) {
            enqueue(heap, frequencia[i], create_node_arvore((u_char) i, frequencia[i], NULL, NULL));
        }
    }
}

lli *contador_de_frequencia(FILE *file) {

    lli *frequencia = calloc(256, sizeof(lli));
    mallocou(frequencia);

    u_char item;

    while (fscanf(file, "%c", &item) != EOF) {
        frequencia[(int) item]++;
    }

    return frequencia;
}

void mallocou(void *mem)
{
    if (!mem)
    {
        printf("Erro ao alocacar\n");
        exit(1);
    }
}

HEAP *montar_heap(FILE *arquivo_entrada)
{
    HEAP *heap = criar_heap();
    lli *frequencia = contador_de_frequencia(arquivo_entrada);
    criacao_fila_prioridade(frequencia, heap);

    return heap;
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    mallocou(result);

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}