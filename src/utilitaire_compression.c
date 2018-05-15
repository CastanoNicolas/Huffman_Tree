#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"

void parcours_arbre(canonical_tree* tree, char* tableau, int profondeur) {
  if (tree == NULL) {
    return;
  } else {
    if (tree->caractere != -1) {
      tableau[tree->caractere] = profondeur;
    }
    parcours_arbre(tree->fils_gauche, tableau, profondeur + 1);
    parcours_arbre(tree->fils_droite, tableau, profondeur + 1);
  }
}

char* tree_to_length_table(canonical_tree* tree) {
  char* table = malloc(sizeof(char) * 256);
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }

  parcours_arbre(tree, table, 1);

  return table;
}

char lire_symbole(FILE* f){
	char c;
	fscanf(f,"%c", &c);
	return c;
}

void ecrire_symbole(FILE* f,char c){
	fprintf(f,"%c", c);
}

char encoder_symbole(tree* tree, char symbole, int* lg){
	noeud *n;
	int res;
	*lg =0;

	//parcours de l'arbre en recherchant sym
	n=parcours_arbre(tree,symbole);

	//ecriture du code de sym
	//tant qu'on ne pointe pas sur la tete, c'est à dire qu'on a fini de remonter l'arbre
	while ( n != tree ){
		//si la branche vaut 1 (fils droit)
		if (n == n->parent->fils_droit)
			res +=  1 << (*lg); //on ecrit 1 (bit) décallé en fonction de la profondeur 
		//si la branche vaut 0  (fils gauche)
		else res += 0 << (*lg); //on ecrit 0 (bit) décallé en fonction de la profondeur 

		//on incremente
		n = n->parent;
		(*lg)++;
	}

	return (char)res;

}