#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comprimir.h"
#include "heap.h"
#include "hash.h"
#include "arvore_huffman.h"
#include "func_extras.h"


void comprimir(FILE *input, FILE *output)
{
    // Monta a heap com base na frequencia dos bytes 
    HEAP *heap = montar_heap(input);

    // volta o ponteiro pro inicio do arquivo - pós leitura -
    rewind(input);

    // Cria a árvore de Huffman com base na heap
    TREE *huff_tree = criar_arvore_huffman(heap);

    // seta nossa hash com cada valor do array(256) como NULL
    HASH *paths = create_hash();
    
    // num de nós
    u_short tree_tamanho = pegar_tamanho_tree(huff_tree);

    //array char num de nós da árvore de huffman
    char path[tree_tamanho];

    // funcao em arvore_huffman.c
    mapear_caminhos(huff_tree, paths, path, 0);

    escrita_tamanho_arvore(tree_tamanho, output);

    //ultima funcao em arvore_huffman.c
    escrita_arvore_pre_ordem(huff_tree, output);

    u_char trash = 0;

    // caso especial 
    if (is_leaf(huff_tree))
    {
        trash = escrita_especial_one_ascii_char(input, output);
    }
    else
    {
        //normal
        trash = escrita_arquivo_comprimido(input, output, paths);
    }

    escrita_trash(trash, output);

    free_tree(huff_tree);
    free_heap(heap);
    free_hash(paths);
}

u_char set_bit(u_char c, int i)
{   
    //00000001 vira 10000000
    u_char mask = 1 << i;
    
    //OU bit a bit
    return mask | c;
}


/*00000000 00000000

00000010 00000001 inicial

00000001 00000000 depois << 8

00000000 00000010 depois >> 8

00000001 00000010 depois |= ou*/

// u_short 16 bits
// func para q o fwrite escreva os 16 bits corretamente
// garante que a ordem dos bytes seja consistente durante a escrita no arquivo
// bytes menos significativos e mais significativos trocam de posicao
// faz funcionar para big ou little endian
void escrita_tamanho_arvore(u_short tree_tamanho, FILE *arquivo)
{
    u_short bytes = tree_tamanho << 8;

    //"ou" bit a bit com o valor atual de bytes. 
    // Isso coloca os 8 bits menos significativos do valor tree_tamanho 
    // nos 8 bits mais significativos da variável bytes.
    bytes |= tree_tamanho >> 8;

    //Escreve os 2 bytes (16 bits) da variável bytes no arquivo 
    fwrite(&bytes, 2, 1, arquivo);
}

void escrita_trash(u_char trash, FILE *file)
{   
    //volta comeco
    rewind(file);

    u_char c;
    fscanf(file, "%c", &c);

    // 00000101 << 5 = 10100000

    trash = trash << 5;
    trash |= c;

    rewind(file);
    fwrite(&trash, 1, 1, file);

    rewind(file);
}

// a arvore é uma folha
u_char escrita_especial_one_ascii_char(FILE *input, FILE *output)
{   
    int i = 0; // contador
    
    u_char c, byte = 0;

    // se i == 7, escreve o byte no arquivo
    // se i < 7, há espaço no byte para mais bits.
    // se i == 0, não há bits no byte, n tem oq escrever
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

    // Se i não for igual a 0, ainda há bits que precisam ser escritos no arquivo
    if (i == 0) return 0;
    fwrite(&byte, 1, 1, output);

    //Retorna o número de bits que precisam ser descartados
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
                //hora de criar nosso byte real 
                byte = set_bit(byte, cont_bits);
            }

            cont_bits--;

            // quando fazer pra cada bit
            if (cont_bits == -1)
            {
                fwrite(&byte, 1, 1, output);
                
                //reinicia o contador de bits
                cont_bits = 7;
                byte = 0;
            }   
        }
    }

    // sem lixo
    if (cont_bits == 7) return 0;
    
    // se houver lixo, escreva o byte no arquivo
    fwrite(&byte, 1, 1, output);

    //Retorna o número de bits que precisam ser descartados 
    return (u_char) (cont_bits + 1);
}