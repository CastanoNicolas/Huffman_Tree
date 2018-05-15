#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "compression_fonctions.h"
#include "utilitaire_compression.h"

void compression(char* file_source, char* file_destination){
  int* frequence = frequencies_of_occurences("test.txt");
  huffman_tree* arbre = build_huffman_tree(frequence);
  canonical_tree* arbreCanonical = normal_tree_to_canonical_tree(arbre);
  write_compressed_file(file_source, file_destination, arbreCanonical);
}