#ifndef DESCOMPRIMIR_H
#define DESCOMPRIMIR_H

#include "heap.h"
#include "hash.h"
#include "arvore_huffman.h"

int is_bit_set(u_char c, int i);

int qual_tamanho_lixo(FILE *input);

short qual_tamanho_arvore(FILE *input);

TREE* qual_e_arvore(FILE* input, TREE* tree);

void decomprimir_one_ascii_file(FILE* input, FILE* output, TREE* tree, int trash_size);

void descomprimir_arquivo(FILE* input, FILE* output, TREE* tree, int trash_size);

void descomprimir(FILE *input, FILE *output);

#endif //DESCOMPRIMIR_H