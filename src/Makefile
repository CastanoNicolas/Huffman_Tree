CC=gcc

OBJ_FOLDER=../bin/
HDR_FOLDER=../header/

EXEC=master

SRCS= $(wildcard $(SRC_FOLDER)*.c)
OBJS=$(SRC:.c=.o)

CFLAGS=-Wall -g -Werror -I$(HDR_FOLDER)
LDFLAGS=
	all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HDR_FOLDER)%.h
	$(CC) -o $(OBJ_FOLDER)$@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ_FOLDER)*.o $(EXEC)