#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definine o tamanho de de cada alloc no programa
#ifndef ALLOCSIZE
#define ALLOCSIZE 100
#endif

// Ajusta LC_ALL para ser ISO 8859-1 e fecha o programa e da um aviso em caso de erro
void makeLocale() {
  if (!setlocale(LC_ALL, "pt_BR.ISO8859-1")) {
    fprintf(stderr, "< Nao foi possivel ajustar o programa ao locale \"pt_BR.ISO8859-1\". Certifique-se de ter esse locale instalado na sua maquina.\n");
    exit(1);
  }
}

// Funcao que le o dicionario e salva na variavel passada
// Retorna a quantida de linhas do dicionario e -1 em caso de erro
// Le dicionario que esta salvo em path
// Funcao assume que a variavel "dict" ainda nao tem espaco alocado
int readDict(char ***dict, char *path) {
  // Abre arquivo e testa se teve sucesso em abrir o arquivo
  FILE *dictFile = fopen(path, "r");
  if (!dictFile) {
    return -1;
  }

  *dict = malloc(sizeof(char *) * ALLOCSIZE); // Alocar espaco para os ponteiros das strings no dicionario
  int dictAllocs = 1;                         // Variavel para guardar quantas vezes for alocado espaco para linhas no dicionario

  const int wordSize = 100; //define como 100 o tamanho maximo de cada palavra
  int currentLine = 0;      // Variavel para marcar onde deve ser salva cada palavra

  (*dict)[0] = malloc(sizeof(char) * wordSize);
  while (fgets((*dict)[currentLine], wordSize, dictFile)) {
    currentLine++;
    // Alocar mais linhas para o dicionario caso precise
    if (currentLine >= dictAllocs * ALLOCSIZE) {
      dictAllocs++;
      *dict = realloc(*dict, sizeof(char *) * dictAllocs * ALLOCSIZE);
    }
    // Alocagem de espaco para a linha a ser lida na proxima passagem do loop
    (*dict)[currentLine] = malloc(sizeof(char) * wordSize);
  }

  fclose(dictFile);
  return currentLine;
}

// Funcao com proposito de teste
void printDict(char **dict, int lines) {
  printf("- Imprimindo dicionario\n");
  for (int i = 0; i < lines; i++) {
    printf("- %s\n", dict[i]);
  }
}

int main(int argc, char *argv[]) {
  printf("- Program started.\n");
  makeLocale();

  printf("- Started reading the dictionary\n");
  // Leitura do dicionario
  char **dict;
  // Faz dictLines ser -1 para poder acessar o dicionario do sistema
  int dictLines = -1;
  // Caso o usuario queria usar outro dicionario que nao e o do sistema ele pode passar como argumento para o programa
  if (argc == 2)
    dictLines = readDict(&dict, argv[1]);

  if (dictLines == -1) {
    // fprintf(stderr, "< Deu ruim no dicionario %s . Tentando com dicionario do sistema\n", argv[1]);
    dictLines = readDict(&dict, "/usr/share/dict/brazilian");
    if (dictLines == -1) {
      fprintf(stderr, "< Nao foi possivel acessar dicionario do sistema e nem o passado como argumento, fechando programa\n");
      exit(1);
    }
  }
  // Fim da leitura do dicionario
  printf("- Successfully read the dictionary\n");

  // Leitura da entrada
  // Inicializacao de variaveis para a entrada
  char *input = malloc(0);
  int allocsInput = 0, inputSize = -1;
  char curChar = fgetc(stdin);
  // Loop de leitura ate ser encontrado EOF
  while (curChar != EOF) {
    inputSize++;
    // Teste se eh necessario mais espaco para a string da entrada
    if (inputSize >= allocsInput * ALLOCSIZE) {
      input = realloc(input, ++allocsInput * ALLOCSIZE * sizeof(char));
    }
    input[inputSize] = curChar;
    curChar = fgetc(stdin);
  }
  input[++inputSize] = '\0';
  // Fim da leitura da entrada

  // printDict(dict, dictLines);
  printf("- Terminando o programa\n");
  return 0;
}