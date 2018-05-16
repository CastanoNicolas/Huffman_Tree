#ifndef HUFFMAN
#define HUFFMAN

#define TAILLE_TAB 256

typedef struct n { 
	int poid ; 
	int caractere ;
	noeud* fils_gauche ; 
	noeud* fils_droite ; 
	noeud* pere ; 

} noeud, huffman_tree, canonical_tree;

#endif