#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"
#include "compression_fonctions.h"

void compression(char* file_source, char* file_destination){
  int* frequence = frequencies_of_occurences(file_source);
  huffman_tree* arbre = build_huffman_tree(frequence);
  canonical_tree* arbreCanonical = normal_tree_to_canonical_tree(arbre);

  afficher_arbre(arbreCanonical, 0);

  write_compressed_file(file_source, file_destination, arbreCanonical);
}

void compression_avec_pretaitement(char* file_source, char* file_destination){

  FILE* src = fopen(file_source,"r+w");
  FILE* temp = fopen("temp.txt","w+r");

  move_to_front_compression(src, temp);
  rewind(src);
  rewind(temp);
  run_length_encoding(temp,src);
  fclose(src);
  fclose(temp);

  remove("temp.txt");


  int* frequence = frequencies_of_occurences(file_source);
  huffman_tree* arbre = build_huffman_tree(frequence);
  canonical_tree* arbreCanonical = normal_tree_to_canonical_tree(arbre);

  afficher_arbre(arbreCanonical, 0);

  write_compressed_file(file_source, file_destination, arbreCanonical);
}