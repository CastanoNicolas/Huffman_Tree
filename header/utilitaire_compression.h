#ifndef UTIL_C
#define	UTIL_C


int lire_symbole(FILE* f);


void tricroissant( int** tab, int tab_size);

noeud** tableau_noeud( int **tabCara,int nbCara);

void tricroissantNoeud( noeud** tab, int tab_size);

void afficher_arbre (noeud* tete, int niveau);


#endif
