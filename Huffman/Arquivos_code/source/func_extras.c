#include "func_extras.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "arvore_huffman.h"

void criacao_fila_prioridade(lli frequencia[], HEAP *heap) {
    int i;

    for (i = 0; i < 256; i++) {
        // passsar apenas os bytes que apareceram no arquivo
        if (frequencia[i] != 0) 
        {
            enqueue(heap, frequencia[i], create_node_arvore((u_char) i, frequencia[i], NULL, NULL));
        }
    }
}

lli *contador_de_frequencia(FILE *file) {

    //array de 256 elementos de tipo long long int( pra nao faltar)
    //representando as frequências de cada byte possível
    lli *frequencia = calloc(256, sizeof(lli));
    mallocou(frequencia);

    //para cada byte lido do arquivo.
    // unsigned_char para que o valor seja sempre positivo
    u_char item;

    //lê cada byte do arquivo 
    while (fscanf(file, "%c", &item) != EOF) 
    {
        // O byte lido é convertido para um int
        // A frequência correspondente ao byte lido é então incrementada.
        // ex : 'h' -- >(int) = 104
        frequencia[(int) item]++;
    }
    return frequencia;
}

void mallocou(void *mem)
{
    if (!mem)
    {
        printf("Erro ao alocacar\n");
        exit(1);
    }
}

HEAP *montar_heap(FILE *arquivo_entrada)
{
    // prepara a heap para o trabalho --> NULL em geral 
    HEAP *heap = criar_heap();
    
    //endereço array da frequencia de cada (byte)
    lli *frequencia = contador_de_frequencia(arquivo_entrada);
    
    // juncao sinistra
    criacao_fila_prioridade(frequencia, heap);

    return heap;
}

char* concat(char *s1, char *s2)
{
    //aloca espaço para a string final + 1 para o '\0'
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    mallocou(result);

    // copia a primeira string  para a nova string 
    strcpy(result, s1);
    strcat(result, s2);

    return result;
}