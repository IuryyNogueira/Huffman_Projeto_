#include <stdio.h>
#include <stdlib.h>

#include "../headers/descomprimir.h"

int is_bit_set(u_char c, int i)
{
    u_char mask = 1 << i;
    return mask & c;
}

int qual_tamanho_lixo(FILE *input)
{
	int trash_size = 0;
	u_char byte;

	fscanf(input, "%c", &byte);
	trash_size = byte >> 5;
	return trash_size;
}

short qual_tamanho_arvore(FILE *input)
{
	short tree_size = 0;
	u_char byte;

	fscanf(input, "%c", &byte);
	byte <<= 3;
	byte >>= 3;
	tree_size = byte << 8;
	fscanf(input, "%c", &byte);
	tree_size = tree_size | byte;
	return tree_size;
}

TREE* qual_e_arvore(FILE* input, TREE* tree)
{
	u_char c;
	fscanf(input, "%c",&c);
	tree = create_node_arvore(c, 0, NULL, NULL);

	if(c == '*'){
		tree->left = qual_e_arvore(input, tree->left);
		tree->right = qual_e_arvore(input, tree->right);
	}
	else if(c=='\\'){
		fscanf(input, "%c",&c);
        tree->c = c;
	}

	return tree;
}

void descomprimir_one_ascii_file(FILE* input, FILE* output, TREE* tree, int trash_size)
{
	TREE* new_tree = tree;

	int i;
    u_char c1, c2;

    fscanf(input, "%c", &c1);
	
    while(fscanf(input, "%c", &c2) != EOF)
	{
		for(i = 7; i >= 0; i--)
		{
            fwrite(&new_tree->c, 1, 1, output);
			new_tree = tree;
		}

        c1 = c2;
	}

    for(i = 7; i >= trash_size; i--)
    {
        fwrite(&new_tree->c, 1, 1, output);
		new_tree = tree;
    }
}

void descomprimir_arquivo(FILE* input, FILE* output, TREE* tree, int trash_size)
{
	TREE* new_tree = tree;

	int i;
    u_char c1, c2;

    fscanf(input, "%c", &c1);

	while(fscanf(input, "%c", &c2) != EOF)
	{
		for(i = 7; i >= 0; i--)
		{
			if(is_bit_set(c1, i))
			{
				new_tree = new_tree->right;
			}
			else{
				new_tree = new_tree->left;
			}
            
			if (is_leaf(new_tree))
            {
                fwrite(&new_tree->c, 1, 1, output);

                new_tree = tree;
            }
		}

        c1 = c2;
	}

    for(i = 7; i >= trash_size; i--)
    {
		if(is_bit_set(c1, i))
		{
			new_tree = new_tree->right;
		}
		else{
			new_tree = new_tree->left;
		}

        if(is_leaf(new_tree))
        {
            fwrite(&new_tree->c, 1, 1, output);
            new_tree = tree;
        }
    }
}


void descomprimir(FILE *input, FILE *output)
{
	int trash_size = qual_tamanho_lixo(input);
	rewind(input);
	short tree_size = qual_tamanho_arvore(input);

	TREE* tree = create_node_arvore('*', 0, NULL, NULL);

	tree = qual_e_arvore(input, tree);

	if (is_leaf(tree)){
		descomprimir_one_ascii_file(input, output, tree, trash_size);
	}
	else {
		descomprimir_arquivo(input, output, tree, trash_size);
	}
	free_tree(tree);
}