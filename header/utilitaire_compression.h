#include "huffman.h"
#ifndef UTIL_C
void tricroissant(int** tab, int tab_size);
noeud** tableau_noeud(int** tabCara, int nbCara);
void tricroissantNoeud(noeud** tab, int tab_size);
void afficher_arbre(noeud* tete, int niveau);
void parcours_arbre(canonical_tree* tree, char* tableau, int profondeur);
noeud* recherche_symbole_arbre(canonical_tree* tree, char symbole);
char* tree_to_length_table(canonical_tree* tree);
char lire_symbole(FILE* f);
void ecrire_symbole(FILE* f, char c);
char* encoder_symbole(canonical_tree* tree, char symbole, int* lg);
int traitement_caractere(int* cmp, int lg, char* octet, char* buffer,
                          FILE* dst);
#endif