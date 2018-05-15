CC=gcc
CFLAGS=-fPIC -Wall -Werror -std=c99 -g 
INCDIR=../header/
EXECS=test

default: $(EXECS)

%.o : %.c $(INCDIR)%.h $(INCDIR)huffman.h
	$(CC) $(CFLAGS) -c $< -I$(INCDIR)

test.o : test.c 
	$(CC) $(CFLAGS) -c $< -I$(INCDIR)

test : $(OBJS) test.o decompression_fonction.o compression_fonctions.o
	$(CC) $(CFLAGS) -o $(BINDIR)$@ $^

clean :
	rm -rf *.o $(EXECS)