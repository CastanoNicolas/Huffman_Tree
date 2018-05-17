CC=gcc

OBJ_FOLDER=../bin/
HDR_FOLDER=../header/

EXEC=master

SRCS= $(wildcard $(SRC_FOLDER)*.c)
OBJS=$(SRCS:%.c=$(OBJ_FOLDER)%.o)


CFLAGS=-Wall -g -Werror -I$(HDR_FOLDER)
LDFLAGS=

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c $(HDR_FOLDER)%.h $(HDR_FOLDER)huffman.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_FOLDER)main.o: main.c $(wildcard $(HDR_FOLDER)*.h)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ_FOLDER)*.o $(EXEC) *.chf *.dhf

