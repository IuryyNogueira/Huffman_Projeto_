#ifndef OPCOES_H
#define OPCOES_H

/**
 * Loop do menu do programa
 */
void escolha_loop();

// recebe um nome de arquivo e comprime o arquivo
void escolha_comprimir();

/**
 * Lê o nome do arquivo comprimido e o nome do arquivo descomprimido e chama a função open_file_decompress
 */
void escolha_descomprimir();

/**
 * Imprime as opções do menu
 */
void print_menu();
/**
 * Abre o arquivo a ser comprimido e o arquivo em que será escrita a compactação (nome do arquivo de entrada + '.huff')
 *
 * @param *input_name      o nome do arquivo a ser comprimido
 */
void abrir_arquivo_descomprimir(char *arquivo_comprimido, char *local_descomprimir);

/**
 * Abre o arquivo comprimido e o arquivo em que serão escritos os bytes descompactados
 *
 * @param *compressed_name         o nome do arquivo comprimido
 * @param *decompressed_name       o nome do arquivo onde serão escritos os bytes descompactados
 */
void open_files_decompress (char *compressed_name, char *decompressed_name);

#endif //HUFFMAN_MENU_H
