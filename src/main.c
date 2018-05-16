#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "compression.h"
#include "compression_fonctions.h"
#include "utilitaire_compression.h"

int main(int argc, char const *argv[]) {

  compression("test.txt","test.txt.hf");

  /*int* frequence = frequencies_of_occurences("test.txt");
  for(int i=0;i<256;i++){
    if(frequence[i] != 0){
      printf("%c %d\n",i,frequence[i]);
    }
  }
  
  printf("\n================HUFFMAN=====================\n");
  
  huffman_tree* arbre = build_huffman_tree(frequence);
  afficher_arbre(arbre,0);

  printf("\n================CANONICAL=====================\n");

  canonical_tree* can_tree = normal_tree_to_canonical_tree (arbre);
  afficher_arbre(can_tree, 0);*/


  return 0;
}