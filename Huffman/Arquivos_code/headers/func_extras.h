#ifndef FUNC_EXTRAS_H
#define FUNC_EXTRAS_H


#include <stdio.h>
#include "heap.h"
#include "hash.h"
#include "arvore_huffman.h"

void criacao_fila_prioridade(lli frequencia[], HEAP *heap);

lli *contador_de_frequencia(FILE *file);

void mallocou(void *mem);

HEAP *montar_heap(FILE *arquivo_entrada);

char* concat(char *s1, char *s2);

#endif /* FUNC_EXTRAS_H */
