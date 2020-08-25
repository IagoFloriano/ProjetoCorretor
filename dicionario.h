#ifndef ALLOCSIZE
#define ALLOCSIZE 1000
#endif

// Funcao que le o dicionario e salva na variavel passada
// Retorna a quantida de linhas do dicionario e -1 em caso de erro
// Le dicionario que esta salvo em path
// Funcao assume que a variavel "dict" ainda nao tem espaco alocado
int readDict(char ***dict, char *path);

// Funcao para deixar todas as palavras do dicionario apenas com letras minusculas
void dictToLower(char ***dict, int size);

// Funcao para ordenar o dicionario
void dictSort(char **dict, int size);

// Funcao para visualizar o dicionario
void printDict(char **dict, int size);