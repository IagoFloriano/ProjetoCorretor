COMPILER = gcc
CFLAGS = -Wall
files = ortografia.c dicionario.o
desiredfile = ortografia

all: ${desiredfile}

ortografia: ${files}
	${COMPILER} ${CFLAGS} -o ortografia ${files}

dicionario.o: dicionario.c
	${COMPILER} ${CFLAGS} -c dicionario.c

run: ortografia
	./ortografia ./brazilian