#include <stdio.h>
#include "../header/utilitaire_compression.h"

void parcours_arbre(canonical_tree* tree, char* tableau, int profondeur) {
  if (tree == NULL) {
    return;
  } else {
    if (tree->caractere != -1) {
      tableau[tree->caractere] = profondeur;
    }
    parcours_arbre(tree->fils_gauche, tableau, profondeur + 1);
    parcours_arbre(tree->fils_droite, tableau, profondeur + 1);
  }
}

char* tree_to_length_table(canonical_tree* tree) {
  char* table = malloc(sizeof(char) * 256);
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }

  parcours_arbre(tree, table, 1);

  return table;
}