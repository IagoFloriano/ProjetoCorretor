CC = gcc
CFLAGS = -Wall
objects = ortografia.o dicionario.o

all: ortografia

# regra de ligacao
ortografia: ${objects}

# regras de compilacao
ortografia.o: ortografia.c dicionario.h
dicionario.o: dicionario.c dicionario.h

# remocao de arquivos temporario
clean:
	rm -f ${objects}

# remove tudo sem o codigo fonte
purge: clean
	rm -f ortografia