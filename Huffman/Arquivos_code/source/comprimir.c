#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comprimir.h"
#include "heap.h"
#include "hash.h"
#include "arvore_huffman.h"
#include "func_extras.h"

u_char set_bit(u_char c, int i)
{
    u_char mask = 1 << i;
    return mask | c;
}

void comprimir(FILE *input, FILE *output)
{
    HEAP *heap = montar_heap(input);

    rewind(input);

    TREE *huff_tree = criar_arvore_huffman(heap);

    HASH *paths = create_hash();

    u_short tree_tamanho = pegar_tamanho_tree(huff_tree);

    char path[tree_tamanho];

    mapear_caminhos(huff_tree, paths, path, 0);

    escrita_tamanho_arvore(tree_tamanho, output);

    escrita_arvore_pre_ordem(huff_tree, output);

    u_char trash = 0;

    if (is_leaf(huff_tree))
    {
        trash = escrita_especial_one_ascii_char(input, output);
    }
    else
    {
        trash = escrita_arquivo_comprimido(input, output, paths);
    }

    escrita_trash(trash, output);

    free_tree(huff_tree);
    free_heap(heap);
    free_hash(paths);
}
// alerta aqui 
void escrita_tamanho_arvore(u_short tree_tamanho, FILE *arquivo)
{
    u_short bytes = tree_tamanho << 8;
    bytes |= tree_tamanho >> 8;

    fwrite(&bytes, 2, 1, arquivo);
}

void escrita_trash(u_char trash, FILE *file)
{
    rewind(file);

    u_char c;
    fscanf(file, "%c", &c);

    trash = trash << 5;
    trash |= c;

    rewind(file);
    fwrite(&trash, 1, 1, file);

    rewind(file);
}


u_char escrita_especial_one_ascii_char(FILE *input, FILE *output)
{
    int i = 0;
    u_char c, byte = 0;

    while (fscanf(input, "%c", &c) != EOF)
    {
        if(i == 7)
        {
            fwrite(&byte, 1, 1, output);
            i = 0;
        }
        else {
            i++;
        }

    }
    if (i == 0) {
        return 0;
    }

    fwrite(&byte, 1, 1, output);

    return (u_char) (8 - i);

}


u_char escrita_arquivo_comprimido(FILE *input, FILE *output, HASH *paths)
{
    int i = 0, cont_bits = 7, path_size;
    u_char c, byte = 0;

    while (fscanf(input, "%c", &c) != EOF)
    {
        char *path = paths->table[c];
        path_size = strlen(path);

        for(i = 0; i < path_size; i++)
        {
            if (path[i] == '1') {
                byte = set_bit(byte, cont_bits);
            }

            cont_bits--;

            if (cont_bits == -1)
            {
                fwrite(&byte, 1, 1, output);

                cont_bits = 7;
                byte = 0;
            }   
        }
    }

    if (cont_bits == 7) {
        return 0;
    }
    fwrite(&byte, 1, 1, output);

    return (u_char) (cont_bits + 1);
}