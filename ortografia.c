#include "dicionario.h"
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

// Faz leitura da entrada e retorna tamanho da string gerada
int readStdin(char *input[]) {
  int allocsInput = 0, inputSize = -1;
  char curChar = fgetc(stdin);
  // Loop de leitura ate ser encontrado EOF
  while (curChar != EOF) {
    inputSize++;
    // Teste se eh necessario mais espaco para a string da entrada
    if (inputSize >= allocsInput * ALLOCSIZE) {
      (*input) = realloc(*input, ++allocsInput * ALLOCSIZE * sizeof(char));
    }
    (*input)[inputSize] = curChar;
    curChar = fgetc(stdin);
  }
  (*input)[++inputSize] = '\0';
  return inputSize;
}

int main(int argc, char *argv[]) {
  printf("- Program started.\n");
  makeLocale();

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

  // Leitura do stdin
  char *input = malloc(0);
  int inputSize = readStdin(&input);

  // printDict(dict, dictLines);
  printf("- Terminando o programa\n");
  return 0;
}