#include "funcoes_extras.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void mallocou(void *mem)
{
    if (!mem)
    {
        printf("Erro ao alocacar\n");
        exit(1);
    }
}