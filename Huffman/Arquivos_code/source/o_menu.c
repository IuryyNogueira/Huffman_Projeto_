#include <stdio.h>
#include <stdlib.h>

#include "opcoes.h"
#include "func_extras.h"
#include "comprimir.h"
#include "descomprimir.h"

void escolha_loop()
{
    int opcao;
    printf(" __    __   __    __   _______  _______ .___  ___.      ___      .__   __. \n"
           "|  |  |  | |  |  |  | |   ____||   ____||   \\/   |     /   \\     |  \\ |  | \n"
           "|  |__|  | |  |  |  | |  |__   |  |__   |  \\  /  |    /  ^  \\    |   \\|  | \n"
           "|   __   | |  |  |  | |   __|  |   __|  |  |\\/|  |   /  /_\\  \\   |  . `  | \n"
           "|  |  |  | |  `--'  | |  |     |  |     |  |  |  |  /  _____  \\  |  |\\   | \n"
           "|__|  |__|  \\______/  |__|     |__|     |__|  |__| /__/     \\__\\ |__| \\__| \n\n");

    while (1)
    {
        print_opcoes();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            comprimir();
            break;
        case 2:
            descomprimir();
            break;
        case 3:
            printf("Volte sempre !!! :)\n");
            exit(0);
            break;
        default:
            printf("Opcao inválida\n");
            break;
        }
        printf("\n");
    }
}
void print_opcoes()
{
    printf("1 ---- Comprimir Arquivo\n");
    printf("2 ---- Descomprimir Arquivo\n");
    printf("3 ---- Saida\n\n");
}