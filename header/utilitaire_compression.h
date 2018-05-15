#ifndef UTIL_C
#define	UTIL_C

typedef struct {
    int caractere;
    int longueur;
} tableau_constructif;

int nb_feuilles (huffman_tree* tree);
int tree_depth (huffman_tree* a);
void construction_par_niveau(huffman_tree* tree, int level, int longueur, 
                                int* p_indice, tableau_constructif* tab) ;
void tri_tableau(tableau_constructif *tab, int nbf);


#endif