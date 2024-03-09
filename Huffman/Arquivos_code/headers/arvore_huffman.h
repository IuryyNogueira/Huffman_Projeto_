#ifndef HUFFMAN_HUFF_TREE_H
#define HUFFMAN_HUFF_TREE_H

#include "heap.h"
#include "hash.h"

/** Árvore de Huffman **/
typedef struct TREE{
    lli frequency;
    u_char c;
    struct TREE *left;
    struct TREE *right;
} TREE;