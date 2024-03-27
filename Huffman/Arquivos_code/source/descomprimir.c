#include <stdio.h>
#include <stdlib.h>

#include "../headers/descomprimir.h"


int qual_tamanho_lixo(FILE *input)
{
	int trash_size = 0;
	u_char byte;

	fscanf(input, "%c", &byte);

	// so quero os 3 primeiros bits do byte
	trash_size = byte >> 5;
	// retorna o tamanho do lixo
	return trash_size;
}

int is_bit_set(u_char c, int i)
{
	// posição do bit atual 
    u_char mask = 1 << i;

	// operaçao AND para verificar se o bit esta setado	como 1 de fato 
	// se for 1 retorna 1 vamos pra direita pra percorrer a arvore
	// se for 0 retorna 0 vamos pra esquerda 
    return mask & c;
}

short qual_tamanho_arvore(FILE *input)
{
	short tree_size = 0;
	u_char byte;

	//le o primeiro byte do arquivo
	fscanf(input, "%c", &byte);

	//limpa o tamanho do lixo e volta para a posicao correta
	byte <<= 3;
	byte >>= 3;

	// como pegamos o primeiro byte do texto temos que passar para a posicao correta   
	// short 2 bytes
	tree_size = byte << 8;

	//le o proximo byte
	fscanf(input, "%c", &byte);
	
	//junta os dois com o operador OU  = pra formar nosso short de 2 bytes do tamanho da arvore
	tree_size = tree_size | byte;
	
	// retorna o tamanho da arvore
	return tree_size;
}

TREE* qual_e_arvore(FILE* input, TREE* tree)
{
	u_char c;
	fscanf(input, "%c",&c);
	
	// cria um nó com o caracter lido
	tree = create_node_arvore(c, 0, NULL, NULL);

	// traducao da arvore recursivamente
	if(c == '*'){
		tree->left = qual_e_arvore(input, tree->left);
		tree->right = qual_e_arvore(input, tree->right);
	}
	// se for folha
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
	// novo nó para percorrer a arvore
	TREE* new_tree = tree;

	int i;
    u_char c1, c2;

	// le o primeiro byte do arquivo
    fscanf(input, "%c", &c1);

	// le o proximo byte / 'c2 
	// usamos C1 e C2 dessa forma até o byte do lixo
	while(fscanf(input, "%c", &c2) != EOF)
	{	
		// percorre os bits do byte 
		for(i = 7; i >= 0; i--)
		{
			// 1 ou 0 para direita ou esquerda / caminhos / percorrendo arvore
			// is_bit_set esta presente para ______ conferir o caminho pra percorrer a arvore
			// 1 = direita / 0 = esquerda
			if(is_bit_set(c1, i))
			{
				new_tree = new_tree->right;
			}
			else{
				new_tree = new_tree->left;
			}
            
			// quando chegarmos na folha escreve no arquivo o (caracter/byte) atual
			if (is_leaf(new_tree))
            {
                fwrite(&new_tree->c, 1, 1, output);

				// volta para a raiz
                new_tree = tree;
            }
		}
		
		// proximo byte
        c1 = c2;
	}

	// caso o arquivo tenha lixo final
	// so trabalha com os bits que nao são lixo
    for(i = 7; i >= trash_size; i--)
    {	
		// Lidando ultimo byte que pode ter lixo
		if(is_bit_set(c1, i))
		{
			new_tree = new_tree->right;
		}
		else{
			new_tree = new_tree->left;
		}

        if(is_leaf(new_tree))
        {
			// escreve no arquivo o (caracter/byte) atual || ultimo
            fwrite(&new_tree->c, 1, 1, output);

			// volta para a raiz
            new_tree = tree;
        }
    }
}


void descomprimir(FILE *input, FILE *output)
{	
	//3 primeiros bits do arquivo
	int trash_size = qual_tamanho_lixo(input);
	rewind(input);

	//2 primeiros bytes, tratamos do lixo, para pegar corretamente apenas o tamanho da arvore
	short tree_size = qual_tamanho_arvore(input);

	//cria nó receber a arvore
	TREE* tree = create_node_arvore('*', 0, NULL, NULL);

	//cria a arvore traduzindo a pre_ordem escrita no arquivo
	tree = qual_e_arvore(input, tree);

	// caso arvore seja 1 folha / caso especifico /
	if (is_leaf(tree)){
		descomprimir_one_ascii_file(input, output, tree, trash_size);
	}
	// normal
	else {
		descomprimir_arquivo(input, output, tree, trash_size);
	}

	// libera a arvore da memoria e é necessario fazer isso porque nosso programa 
	//esta em loop
	free_tree(tree);
}