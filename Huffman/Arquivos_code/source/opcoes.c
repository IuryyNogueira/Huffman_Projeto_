#include <stdio.h>
#include <stdlib.h>

#include "opcoes.h"
#include "func_extras.h"
#include "comprimir.h"
#include "descomprimir.h"

#define FILE_PATH "Arquivos_code/files/"

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
            escolha_comprimir();
            break;
        case 2:
            escolha_descomprimir();
            break;
        case 3:
            printf("Volte sempre ᕙ(`▿´)ᕗ !!! :)\n");
            exit(0);
            break;
        default:
            printf("Opcao inválida (╥﹏╥)\n");
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

void escolha_comprimir()
{
    char arquivo[1000];
    printf("Digite o nome do arquivo:\n");
    scanf("%s", arquivo);
    getchar();

    abrir_arquivo_comprimir(concat(FILE_PATH, name));
}

void escolha_descomprimir()
{
    char arquivo_comp[1000], descomprimido[1000];

    printf("Digite o nome do arquivo:\n");
    scanf("%s", arquivo_comp);
    getchar();

    printf("Digite o nome do novo arquivo:\n");
    scanf("%s", descomprimido);
    getchar();

    open_files_decompress(concat(FILE_PATH, arquivo_comp), concat(FILE_PATH, descomprimido));
}

void abrir_arquivo_comprimir(char *nome_arquivo)
{
    FILE *input = fopen(nome_arquivo, "rb");
    if (input == NULL)
    {
        printf("Arquivo nao encontrado (╥﹏╥)\n");
    }
    else
    {
        char *output_nome = concat(nome_arquivo, ".huff");
        FILE *output = fopen(output_nome, "w+b");
        
        mallocou(output);

        comprimir(input, output);

        fclose(output);

        free(input);
        free(output);
        printf("Arquivo comprimido ᕙ(`▿´)ᕗ\n");
    }

    void abrir_arquivo_descomprimir(char *arquivo_comprimido, char *local_descomprimir)
    {
        FILE *input = fopen(arquivo_comprimido, "rb");
        if (input == NULL)
        {
            printf("Arquivo nao encontrado (╥﹏╥)\n");
        }
        else
        {
            FILE *output = fopen(local_descomprimir, "w+b");
            
            mallocou(output);

            descoprimir(input, output);

            fclose(output);

            free(input);
            free(output);
            printf("Arquivo descomprimido ᕙ(`▿´)ᕗ\n");
        }
    }
}