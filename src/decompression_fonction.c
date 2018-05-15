#include <stdio.h>
#include <stdlib.h>

#include "decompression_fonction.h"

char* read_compressed_huffman_code(char* src_file_name) {
  FILE* f = fopen(src_file_name, "r");

  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier compressé.\n");
    exit(1);
  }

  char* tab = malloc(sizeof(char) * 256);

  for (int i = 0; i < 256; i++) {
    fscanf(f, "%c", &tab[i]);
  }

  return tab;
}

canonical_tree* length_table_to_canonical_tree(char* table) {
  char longueur_max = 0;
  char symb[256][10];

  for (int i = 0; i < 256; i++) {
    symb[i][0] = 0;
  }

  for (int i = 0; i < 256; i++) {
    if (table[i] > longueur_max) {
      longueur_max = table[i];
    }
    if (table[i] != 0) {
      symb[(int)table[i]][(int)symb[(int)table[i]][0]] = table[i];
      symb[(int)table[i]][0]++;
    }
  }

  // int profondeur = 0;
  // char symb_courant;
  // canonical_tree* racine;
  // char anciens[10] = symb[0];

  return NULL;
}