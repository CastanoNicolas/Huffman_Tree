#ifndef HUFFMAN
#define HUFFMAN

typedef struct n { 
	float poid ; 
  int caractere ;
	struct n* fils_gauche ; 
	struct n* fils_droite ; 
	struct n* pere ; 
} noeud, huffman_tree, canonical_tree;

#endif