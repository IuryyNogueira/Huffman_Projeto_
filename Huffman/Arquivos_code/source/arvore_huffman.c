#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_extras.h"

#include "arvore_huffman.h"
#include "heap.h"

// Cria um nó da árvore de Huffman com os parâmetros passados em 
// compactar: func_extras.c --> criacao_fila_prioridade linha 17
// e durante a criação da árvore de Huffman
TREE *create_node_arvore(u_char character, lli frequency, TREE *left, TREE *right)
{
	TREE *new_node = (TREE*)malloc(sizeof(TREE));
	mallocou(new_node);

	// caso o (caractere/byte) atual 
	new_node->c = character;
	
	new_node->frequency = frequency;
	
	new_node->left = left;
	new_node->right = right;

	return new_node;
}

int is_empty(TREE *tree)
{
	return tree == NULL;
}

int is_leaf(TREE *tree)
{
	return (tree->left == NULL) && (tree->right == NULL);
}

int is_escape_char(TREE *tree, u_char c)
{
	if (is_leaf(tree))
	{
		return (c == '*' || c == '\\');
	}

	return  0;
}

u_short pegar_tamanho_tree(TREE *tree)
{
	if (is_empty(tree)) return 0;
   
	if (is_escape_char(tree, tree->c))
    {
        return 2;
    }

	return 1 + pegar_tamanho_tree(tree->left) + pegar_tamanho_tree(tree->right);
}

void free_tree(TREE *tree)
{
	if (!is_empty(tree))
    {
        free_tree(tree->left);
        free_tree(tree->right);

        free(tree);
    }
}

lli get_parent_frequencia(TREE *tree)
{
	return tree->left->frequency + tree->right->frequency;
}

TREE *criar_arvore_huffman(HEAP *heap)
{
	//até a arvore ser formada 
	while (heap->size > 1)
	{
		TREE *left_child_tree = dequeue(heap);

		TREE *right_child_tree = dequeue(heap);

        TREE *parent_tree = create_node_arvore('*', 0, left_child_tree, right_child_tree);
		
		//soma das 2 frequencias 
		parent_tree->frequency = get_parent_frequencia(parent_tree);

		enqueue(heap, parent_tree->frequency, parent_tree);
	}


	TREE *t = dequeue(heap);

	return t;
}

void mapear_caminhos(TREE *tree, HASH *hash, char *path, int i)
{	
	//se a arvore não for vazia
	if (!is_empty(tree))
    {
		// se o no for uma folha --> achamos um caractere/byte
        if (is_leaf(tree))
        {
			// indica fim do caminho
            path[i] = '\0';
			
			// aloca espaço com tamnho do correto para o caminho completo
            char *finish_path = (char *) malloc(sizeof(char) * (strlen(path) + 1));
            mallocou(finish_path);

			// Copia o caminho completo para a nova string finish_path
            strcpy(finish_path, path);

			//Insere o caractere tree->c(int) e seu caminho completo na tabela de hash 
            put(hash, (int) tree->c, finish_path);
        }
        else
        {
			// Verifica se há um filho à esquerda do nó atual.
            if (!is_empty(tree->left))
            {
                path[i] = '0';
                mapear_caminhos(tree->left, hash, path, i + 1);
            }

			// Verifica se há um filho à direita do nó atual.
            if (!is_empty(tree->right))
            {
                path[i] = '1';
                mapear_caminhos(tree->right, hash, path, i + 1);
            }
        }
    }
}

void escrita_arvore_pre_ordem(TREE *tree, FILE *output)
{
	if (is_empty(tree)) return;
	
	if (is_escape_char(tree, tree->c))
	{
	    fprintf(output, "%c", '\\');
	}
	fwrite(&tree->c, 1, 1, output);
	escrita_arvore_pre_ordem(tree->left, output);
	escrita_arvore_pre_ordem(tree->right, output);
}