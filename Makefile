CC = gcc
CFLAGS = -std=c2x -ggdb

SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}

all: ada

.c.o:
	$(CC) $(CFLAGS) -c $<

ada: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ) ada
