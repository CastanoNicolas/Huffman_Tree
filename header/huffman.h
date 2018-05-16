#ifndef HUFFMAN
#define HUFFMAN

#define TAILLE_TAB 256

typedef struct n { 
	int poid ; 
	int caractere ;
	struct n* fils_gauche ; 
	struct n* fils_droite ; 
	struct n* pere ; 

} noeud, huffman_tree, canonical_tree,tree;

typedef struct {
    int caractere;
    int longueur;
} tableau_constructif;

#endif