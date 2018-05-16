#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"
#ifndef COMPRESSION_FUN
int* frequencies_of_occurences(char* file_name);
huffman_tree* build_huffman_tree(int* frequencies);
void write_compressed_huffman_code(FILE* dst_file, canonical_tree* tree);
void write_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree);
#define COMPRESSION_FUN
#endif