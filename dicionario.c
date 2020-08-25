#include "dicionario.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readDict(char ***dict, char *path) {
  // Abre arquivo e testa se teve sucesso em abrir o arquivo
  FILE *dictFile = fopen(path, "r");
  if (!dictFile) {
    return -1;
  }

  *dict = malloc(sizeof(char *) * ALLOCSIZE); // Alocar espaco para os ponteiros das strings no dicionario
  int dictAllocs = 1;                         // Variavel para guardar quantas vezes for alocado espaco para linhas no dicionario

  int currentLine = 0; // Variavel para marcar onde deve ser salva cada palavra

  (*dict)[0] = malloc(sizeof(char) * MAXCHARSINWORD);
  while (fgets((*dict)[currentLine], MAXCHARSINWORD, dictFile)) {
    // Remove o '\n' no final da palavra
    (*dict)[currentLine][strcspn((*dict)[currentLine], "\n")] = '\0';

    currentLine++;
    // Alocar mais linhas para o dicionario caso precise
    if (currentLine >= dictAllocs * ALLOCSIZE) {
      dictAllocs++;
      *dict = realloc(*dict, sizeof(char *) * dictAllocs * ALLOCSIZE);
    }
    // Alocagem de espaco para a linha a ser lida na proxima passagem do loop
    (*dict)[currentLine] = malloc(sizeof(char) * MAXCHARSINWORD);
  }

  fclose(dictFile);
  return currentLine;
}

void dictToLower(char ***dict, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; (*dict)[i][j] != '\0'; j++) {
      (*dict)[i][j] = tolower((*dict)[i][j]);
    }
  }
}

int strcmp_2(const void *a, const void *b) {
  const char *pa = *(const char **)a;
  const char *pb = *(const char **)b;
  return (strcmp(pa, pb));
}

int dictBsearch(char *key, char **dict, int dictSize) {
  int first = 0, last = dictSize - 1;

  while (first <= last) {
    int middle = (first + last) / 2;
    int cmpresult = strcmp(key, dict[middle]);
    if (cmpresult == 0)
      return middle;
    else if (cmpresult < 0)
      last = middle - 1;
    else
      first = middle + 1;
  }

  return -1;
}

// Funcao para visualizar o dicionario
void printDict(char **dict, int size) {
  for (int i = 0; i < size; i++) {
    printf("Line: %d Word: %s\n", i, dict[i]);
  }
}