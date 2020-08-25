CC = gcc
CFLAGS = -Wall

all: ortografia

ortografia: ortografia.o dicionario.o
	${CC} ${CFLAGS} -o ortografia ortografia.o dicionario.o

ortografia.o: ortografia.c dicionario.h
	${CC} ${CFLAGS} -c ortografia.c

dicionario.o: dicionario.c dicionario.h
	${CC} ${CFLAGS} -c dicionario.c

clean:
	rm -f *.o

purge: clean
	rm -f ortografia