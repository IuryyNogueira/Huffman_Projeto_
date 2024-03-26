#include <stdio.h>
#include <stdlib.h>

#include "func_extras.h"
#include "comprimir.h"
#include "descomprimir.h"
#include "opcoes.h"

#define FILE_PATH "../../Arquivos_teste/"

void print_opcoes(){
    printf("1 ---- Comprimir Arquivo\n");
    printf("2 ---- Descomprimir Arquivo\n");
    printf("3 ---- Saida\n\n");
}

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
        
        if (opcao == 1) escolha_comprimir();
       
        else if (opcao == 2) escolha_descomprimir();
       
        else if (opcao == 3)
        {
            printf("Volte sempre ᕙ(`▿´)ᕗ !!! :)\n");
            exit(0);
        }
        else
        {
            printf("Opcao inválida (╥﹏╥)\n");
        }
        printf("\n");
    }
}

void escolha_comprimir()
{
    char arquivo[1000];
    
    printf("Digite o nome do arquivo:\n");
    
    scanf("%s", arquivo);
    
    // Limpa o buffer do teclado, evita.
    getchar();

    abrir_arquivo_comprimir(concat(FILE_PATH, arquivo));
}

void escolha_descomprimir()
{
    char arquivo_comp[1000], descomprimido[1000];
    // arquivo_comp = nome do arquivo comprimido
    // descomprimido = nome para o novo arquivo descomprimido
    
    printf("Digite o nome do arquivo:\n");
    scanf("%s", arquivo_comp);
    
    // Limpa o buffer do teclado
    getchar();

    printf("Digite o nome do novo arquivo:\n");
    scanf("%s", descomprimido);
    getchar();

    // comeca processo descomprimir, passando o nome do arquivo comprimido e o nome do arquivo 
    // descomprimido concatenados com o caminho do arquivo
    abrir_arquivo_descomprimir (concat(FILE_PATH, arquivo_comp), concat(FILE_PATH, descomprimido));
}

void abrir_arquivo_comprimir(char *nome_arquivo)
{
    // Abre o arquivo para leitura
    FILE *input = fopen(nome_arquivo, "rb");
   
   // Verifica se o arquivo foi encontrado
    if (input == NULL) printf("\nArquivo nao encontrado (╥﹏╥)\n");
    
    else{
        // Cria um novo arquivo para escrita com .HUFF
        char *output_nome = concat(nome_arquivo, ".huff");
        
        // Abre o arquivo para escrita
        FILE *output = fopen(output_nome, "w+b");
        
        mallocou(output);

        // ----------------Comprime o arquivo ------------------------
        comprimir(input, output);

        // Fecha o arquivo de saida
        fclose(output);

        printf("\nArquivo comprimido ᕙ(`▿´)ᕗ\n");
    }
}

void abrir_arquivo_descomprimir(char *arquivo_comprimido, char *local_descomprimir)
{

    // Abre o arquivo para leitura em binario E ja compactado
    FILE *input = fopen(arquivo_comprimido, "rb");
    
    // Verifica se o arquivo foi encontrado
    if (input == NULL)  printf("\nArquivo nao encontrado (╥﹏╥)\n");

else{
    // Cria um novo arquivo para escrita, descompactado
    FILE *output = fopen(local_descomprimir, "w+b");
    
    mallocou(output);

    // ---------------- Descomprime o arquivo ------------------------
    descomprimir(input, output);

    fclose(output);

    printf("\nArquivo descomprimido ᕙ(`▿´)ᕗ\n");
    }
}
