#ifndef FUNCTIONS_ADD
#define FUNCTIONS_ADD
#include "huffman.h"

void init_dictionnaire(char* dictionnaire);
int max( int a , int b);
void ecrire_octet(FILE* fichier_ecriture, char chaine);
int lire_symbole(FILE* f);
int nb_feuilles(huffman_tree *tree);
int tree_depth(huffman_tree *a);


#endif