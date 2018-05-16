#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"
#ifndef COMPRESSION_FUN
#define COMPRESSION_FUN

int* frequencies_of_occurences(char* file_name);
huffman_tree* build_huffman_tree(int* frequencies);
canonical_tree *normal_tree_to_canonical_tree(huffman_tree *tree);

#endif