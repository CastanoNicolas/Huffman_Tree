#ifndef HUFFMAN
#define HUFFMAN

typedef struct n { 
	int poid ; 
	int caractere ;
	noeud* fils_gauche ; 
	noeud* fils_droite ; 
	noeud* pere ; 
} noeud, huffman_tree, canonical_tree;

#endif