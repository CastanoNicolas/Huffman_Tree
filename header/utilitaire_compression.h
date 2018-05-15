#include "huffman.h"
#ifndef UTIL_C
void parcours_arbre(canonical_tree* tree, char* tableau, int profondeur);
char* tree_to_length_table(canonical_tree* tree);
char lire_symbole(FILE* f);
void ecrire_symbole(FILE* f,char c);
char encoder_symbole(canonical_tree* tree, char symbole, int* lg);
#define	UTIL_C
#endif