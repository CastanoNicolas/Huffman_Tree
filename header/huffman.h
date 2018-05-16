#ifndef HUFFMAN
#define HUFFMAN

typedef struct n { 
	int poid ; 
	int caractere ;
	struct n* fils_gauche ; 
	struct n* fils_droite ; 
	struct n* pere ; 

} noeud, huffman_tree, canonical_tree;

#endif