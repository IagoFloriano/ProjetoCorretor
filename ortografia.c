#include "dicionario.h"
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definine o tamanho de de cada alloc no programa
#ifndef ALLOCSIZE
#define ALLOCSIZE 1000
#endif

// Define o tamanho de uma palavra para o programa
#ifndef MAXCHARSINWORD
#define MAXCHARSINWORD 100
#endif

// Ajusta LC_ALL para ser ISO 8859-1 e fecha o programa e da um aviso em caso de erro
void makeLocale() {
  if (!setlocale(LC_ALL, "pt_BR.ISO8859-1")) {
    fprintf(stderr, "< Nao foi possivel ajustar o programa ao locale \"pt_BR.ISO8859-1\". Certifique-se de ter esse locale instalado na sua maquina.\n");
    exit(1);
  }
}

// Transforma uma string em minuscula
void strlwr(char *str, int strsize) {
  for (int i = 0; i < strsize; i++) {
    str[i] = tolower(str[i]);
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

// Imprime a palavra iniciada em sentence[i] e terminada no proximo caracter nao letra
// Se a palvra estiver em dict sera impressa normalmente. exemplo
// Caso contrario sera impressa com [] em sua volta. [esemplo]
// Retorna indice da ultima letra da palavra impressa
int printWord(char **dict, int dictSize, char *sentence, int i) {
  // Salvar palavra na memoria
  char word[MAXCHARSINWORD];
  int newi;
  for (newi = i; isalpha(sentence[newi]); newi++) {
    word[newi - i] = sentence[newi];
  }
  word[newi - i] = '\0';
  strlwr(word, newi - i);

  // Ver se esta no dicionario e imprimir de acordo
  int found = dictBsearch(word, dict, dictSize);
  if (found == -1)
    printf("[");
  for (int j = i; j < newi; j++)
    printf("%c", sentence[j]);
  if (found == -1)
    printf("]");

  return newi - 1;
}

int main(int argc, char *argv[]) {
  makeLocale();

  // Leitura do dicionario
  char **dict;
  // Faz dictLines ser -1 para poder acessar o dicionario do sistema
  int dictLines = -1;
  // Caso o usuario queria usar outro dicionario que nao e o do sistema ele pode passar como argumento para o programa
  if (argc == 2)
    dictLines = readDict(&dict, argv[1]);

  if (dictLines == -1) {
    dictLines = readDict(&dict, "/usr/share/dict/brazilian");
    if (dictLines == -1) {
      fprintf(stderr, "< Nao foi possivel acessar dicionario do sistema e nem o passado como argumento, fechando programa\n");
      exit(1);
    }
  }
  // Fim da leitura do dicionario

  // Deixa todas as palavras do dicionario em letra minuscula e ordena o dicionario novamente
  dictToLower(&dict, dictLines);
  qsort(dict, dictLines, sizeof(char *), strcmp_2);

  // Leitura do stdin
  char *input = malloc(0);
  int inputSize = readStdin(&input);

  // Impressao corrigida da entrada
  for (int i = 0; i < inputSize; i++) {
    if (!isalpha(input[i]))
      fputc(input[i], stdout);
    else {
      i = printWord(dict, dictLines, input, i);
    }
  }

  // printDict(dict, dictLines);
  return 0;
}