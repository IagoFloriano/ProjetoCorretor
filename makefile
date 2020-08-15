COMPILER = gcc
CFLAGS = -Wall
files = ortografia.c

all: ${files}
	${COMPILER} ${CFLAGS} -o ortografia ${files}

run: ortografia
	./ortografia ./brazilian.gz