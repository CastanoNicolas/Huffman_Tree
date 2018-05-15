CC=gcc

OBJ_FOLDER=../bin/
HDR_FOLDER=../header/

EXEC=test

SRCS= $(wildcard $(SRC_FOLDER)*.c)
OBJS=$(SRC:.c=.o)

CFLAGS=-Wall -g -Werror -I$(HDR_FOLDER)
LDFLAGS=
all: test

test: $(OBJ_FOLDER)compression_fonctions.o $(OBJ_FOLDER)main.o $(OBJ_FOLDER)utilitaire_compression.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_FOLDER)main.o: main.c $(HDR_FOLDER)huffman.h
	gcc -c main.c $(CFLAGS)

rien: $(OBJ_FOLDER)compression_fonctions.o $(OBJ_FOLDER)main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: ./%.c %.h
	$(CC) -o $(OBJ_FOLDER)$@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ_FOLDER)*.o $(EXEC)
