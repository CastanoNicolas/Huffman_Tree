#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "decompression_fonction.h"

void decompression(char* file_source, char* file_destination){

	char nb_bit_invalide=0;
	FILE* f= fopen(file_source,"r");

  char* table = read_compressed_huffman_code(f,file_source,&nb_bit_invalide);
  canonical_tree* arbreCanonical = length_table_to_canonical_tree(table);
  read_and_store_compressed_file(f,file_destination,arbreCanonical,(int)nb_bit_invalide);
}