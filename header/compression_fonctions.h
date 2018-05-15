#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"
#ifndef COMPRESSION_FUN
void write_compressed_huffman_code(char* dst_file_name, canonical_tree* tree);
#define COMPRESSION_FUN
#endif