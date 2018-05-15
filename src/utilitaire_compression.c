#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"



/**
* lire_symbole : lit un charactère (8bits) dans le fichier source
* renvoit un int, pour prendre en compte la valeur EOF (-1)
* Aucun traitement sur l'entrée lue
**/
int lire_symbole(FILE* f){
	int c;
	fscanf("%c", &c);
	return c;
}

/**
* encoder_symbole : renvoit le code d'un symbole (char ascii) dans un arbre quelconque
* On renvoit un octet (char).
* Le code du symbole est placé dans les bits de poids faible.
* Le pointeur sur entier lg contient la longueur (en nombre de bit) du symbole codé. 
* Attention : Le resultat peut donc etre plus court qu'un octet.
* Convention : le poid d'un fils_gauche est mis à 0 et celui d'un fils_droit à 1. 
**/
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

/**
* Parcours d'un arbre en recherchant un symbole (char ascii)
* fonction recursive
renvoit NULL si le symbole n'est pas trouvé
* renvoit le noeud correspondant au symbole
**/
noeud* parcours_arbre(tree* tree, char symbole){
	noeud* n;

	//si on arrive en fin d'arbre
	if(tree == NULL){
		return NULL;
	}

	//
	if(tree->caractere == symbole){
		return tree;
	}
	else if(n = parcours_arbre(tree->fils_droit, symbole) != NULL){
		return n;
	}
	else return parcours_arbre(tree->fils_gauche, symbole);

}
