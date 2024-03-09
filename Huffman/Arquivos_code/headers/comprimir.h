#ifndef COMPRIMIR_H
#define COMPRIMIR_H

#include "heap.h"
#include "hash.h"
#include "arvore_huffman.h"

u_char set_bit(u_char c, int i);

void comprimir(FILE *input, FILE *output);

void escrita_tamanho_arvore(u_short tree_tamanho, FILE *arquivo);

void escrita_trash(u_char trash, FILE *file);

u_char escrita_especial_one_ascii_char(FILE *input, FILE *output);

u_char escrita_arquivo_comprimido(FILE *input, FILE *output, HASH *paths);

#endif /* COMPRIMIR_H */

