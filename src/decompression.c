#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "compression_fonctions.h"

void decompression(char* file_source, char* file_destination){
  char* table = read_compressed_huffman_code(file_source);
  canonical_tree* arbreCanonical = length_table_to_canonical_tree(table);
  read_and_store_compressed_file(file_source,file_destination,arbreCanonical);
}