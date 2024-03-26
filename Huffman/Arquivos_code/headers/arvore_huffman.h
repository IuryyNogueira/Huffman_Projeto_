#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include "heap.h"
#include "hash.h"
#include "func_extras.h"

// -------Árvore--------
typedef struct TREE{
    lli frequency;
    
    // (caractere/byte)
    u_char c;
    
    // nós filhos
    struct TREE *left;
    struct TREE *right;
} TREE;

TREE *create_node_arvore(u_char character, lli frequency, TREE *left, TREE *right);

int is_empty(TREE *tree);

int is_leaf(TREE *tree);

int is_escape_char(TREE *tree, u_char c);

u_short pegar_tamanho_tree(TREE *tree);

void free_tree(TREE *tree);

lli get_parent_frequencia(TREE *tree);

TREE *criar_arvore_huffman(HEAP *heap);

void mapear_caminhos(TREE *tree, HASH *hash, char *path, int i);

void escrita_arvore_pre_ordem(TREE *tree, FILE *output);

#endif //HUFF_TREE_H