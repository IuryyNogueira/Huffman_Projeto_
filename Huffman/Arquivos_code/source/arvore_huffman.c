#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_extras.h"

#include "arvore_huffman.h"
#include "heap.h"


TREE *create_node_arvore(u_char character, lli frequency, TREE *left, TREE *right)
{
	TREE *new_node = (TREE*)malloc(sizeof(TREE));
	check_malloc(new_node);

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
	if (is_empty(tree))
    {
        return 0;
    }

	if (is_escape_char(tree, tree->c))
    {
        return 2;
    }

	return 1 + get_tree_size(tree->left) + get_tree_size(tree->right);
}

lli get_parent_frequencia(TREE *tree)
{
	return tree->left->frequency + tree->right->frequency;
}

TREE *criar_arvore_huffman(HEAP *heap)
{
	while (heap->size > 1)
	{
		TREE *left_child_tree = dequeue(heap);

		TREE *right_child_tree = dequeue(heap);

        TREE *parent_tree = create_node_arvore('*', 0, left_child_tree, right_child_tree);
		parent_tree->frequency = get_parent_frequencia(parent_tree);

		enqueue(heap, parent_tree->frequency, parent_tree);
	}


	TREE *t = dequeue(heap);

	return t;
}

void map_paths(TREE *tree, HASH *hash, char *path, int i)
{
	if (!is_empty(tree))
    {
        if (is_leaf(tree))
        {
            path[i] = '\0';

            char *finish_path = (char *) malloc(sizeof(char) * (strlen(path) + 1));
            check_malloc(finish_path);

            strcpy(finish_path, path);

            put(hash, (int) tree->c, finish_path);
        }
        else
        {
            if (!is_empty(tree->left))
            {
                path[i] = '0';
                map_paths(tree->left, hash, path, i + 1);
            }

            if (!is_empty(tree->right))
            {
                path[i] = '1';
                map_paths(tree->right, hash, path, i + 1);
            }
        }
    }
}