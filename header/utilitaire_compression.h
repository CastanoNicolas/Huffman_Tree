#ifndef UTIL_C
#define	UTIL_C
#endif

int lire_symbole(FILE* f);
char encoder_symbole(tree* tree, char symbole, int* lg);
noeud* parcours_arbre(tree* tree, char symbole);