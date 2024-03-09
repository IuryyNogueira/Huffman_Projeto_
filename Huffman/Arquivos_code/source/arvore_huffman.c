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