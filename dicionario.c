#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>

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