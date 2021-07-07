SHELL = /bin/zsh
CC = gcc
CFLAGS = -g -lm
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all:${EXE}

%: %.c
	${CC} ${CFLAGS} $@.c -o $@

clean:
	rm ${EXE}
