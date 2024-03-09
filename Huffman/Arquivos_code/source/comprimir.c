#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comprimir.h"
#include "heap.h"
#include "hash.h"
#include "arvore_huffman.h"
#include "func_extra.h"


void comprimir(FILE *input, FILE *output)
{
    HEAP *heap = montar_heap(input);

    rewind(input);

    TREE *huff_tree = criar_arvore_huffman(heap);

    HASH *paths = create_hash();

    u_short tree_tamanho = pegar_tamanho_tree(huff_tree);

    char path[tree_tamanho];

    map_paths(huff_tree, paths, path, 0);

    write_tree_size(tree_tamanho, output);

    write_pre_order_tree(huff_tree, output);

    u_char trash = 0;

    if (is_leaf(huff_tree))
    {
        trash = write_one_ascii_char_doc(input, output);
    }
    else
    {
        trash = write_compress_doc(input, output, paths);
    }

    write_trash(trash, output);

    free_tree(huff_tree);
    free_heap(heap);
    free_hash(paths);
}