#ifndef opcoes_h
#define opcoes_h

//mostra as opcoes disponiveis
void print_opcoes();

// loop de escolhas
void escolha_loop();

// recebe um nome de arquivo e comprime o arquivo
void escolha_comprimir();

//recebe dois nomes, um de arquivo comprimido e outro de arquivo descomprimido
void escolha_descomprimir();

void abrir_arquivo_comprimir(char *nome_arquivo);

void abrir_arquivo_descomprimir(char *arquivo_comprimido, char *local_descomprimir_descomprimir);

#endif /* opcoes_h */