#include <stdio.h>
#include <stdlib.h>

#include "compression_fonctions.h"
#include "decompression_fonction.h"
#include "utilitaire_compression.c"

int main() {
  int* frequence = frequencies_of_occurences("test.txt");
  for (int i = 0; i < 256; i++) {
    if (frequence[i] != 0) {
      printf("%c %d\n", i, frequence[i]);
    }
  }
  huffman_tree* arbre = build_huffman_tree(frequence);
  //afficher_arbre(arbre, 0);

  write_compressed_file("test.txt", "yolo.txt",
                            arbre);

  /*int lg;
  printf("%x\n",encoder_symbole(arbre,'e',&lg));
  printf("%x\n",encoder_symbole(arbre,'h',&lg));
  printf("%x\n",encoder_symbole(arbre,'e',&lg));*/



  return 0;
}