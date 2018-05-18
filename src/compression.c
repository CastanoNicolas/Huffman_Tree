#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "compression_fonctions.h"

void compression(char* file_source, char* file_destination){

  double size_before;
  FILE* f = fopen (file_source, "r");
  fseek(f, 0, SEEK_END); // seek to end of file
  size_before = ftell(f);       // get current file pointer
  fseek(f, 0, SEEK_SET);
  fclose(f);

  int* frequence = frequencies_of_occurences(file_source);
  huffman_tree* arbre = build_huffman_tree(frequence);
  canonical_tree* arbreCanonical = normal_tree_to_canonical_tree(arbre);

  write_compressed_file(file_source, file_destination, arbreCanonical);

  double size_after;
  f = fopen (file_destination, "r");
  fseek(f, 0, SEEK_END); // seek to end of file
  size_after = ftell(f);       // get current file pointer
  fseek(f, 0, SEEK_SET);
  fclose(f);

  printf("\nTaux de comrpession: %lf%%.\n",(1-(size_after/size_before))*100);
}

void compression_avec_pretaitement(char* file_source, char* file_destination){

  double size_before;
  FILE* f = fopen (file_source, "r");
  fseek(f, 0, SEEK_END); // seek to end of file
  size_before = ftell(f);       // get current file pointer
  fseek(f, 0, SEEK_SET);
  fclose(f);


  FILE* src = fopen(file_source,"r");
  FILE* temp = fopen("temp.txt","w");

  move_to_front_compression(src, temp);
  fclose(src);
  fclose(temp);
  src = fopen("temp.txt","r");
  FILE* final = fopen("temp2.txt","w");

  run_length_encoding(src,final);
  fclose(src);
  fclose(final);


  int* frequence = frequencies_of_occurences("temp2.txt");
  huffman_tree* arbre = build_huffman_tree(frequence);
  canonical_tree* arbreCanonical = normal_tree_to_canonical_tree(arbre);


  write_compressed_file("temp2.txt", file_destination, arbreCanonical);

  double size_after;
  f = fopen (file_destination, "r");
  fseek(f, 0, SEEK_END); // seek to end of file
  size_after = ftell(f);       // get current file pointer
  fseek(f, 0, SEEK_SET);
  fclose(f);

  printf("\nTaux de comrpession: %lf%%.\n",(1-(size_after/size_before))*100);

  remove("temp.txt");
  remove("temp2.txt");

}