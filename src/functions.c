#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/**
* procedure qui initialise en dictionnaire en associant à chaque indice son charcatère ascii correspondant
* la taille du tableau doit etre la même que la variable global ASCII (255)
**/
void init_dictionnaire(char* dictionnaire){

  for(int i=0; i<TAILLE_TAB ; i++){
    dictionnaire[i]=(char)i;
  }
}

int max( int a , int b){
  return (a>b)?a:b;
}

int nb_feuilles(huffman_tree *tree)
{
    if (tree == NULL)
        return 0;

    if (tree->fils_gauche == NULL && tree->fils_droite == NULL)
        return 1;

    else
        return (nb_feuilles(tree->fils_gauche) + nb_feuilles(tree->fils_droite));
}

/* racine a profondeur 0 */
int tree_depth(huffman_tree *a)
{
    if (a == NULL)
        return -1;

    return (1 + max(tree_depth(a->fils_gauche), tree_depth(a->fils_droite)));
}


/**
* écrit dans un fichier un octet codé stocké dans chaine
**/ 
void ecrire_octet(FILE* fichier_ecriture, char chaine){
  fprintf(fichier_ecriture, "%c", chaine);
}


/**
* lire_symbole : lit un charactère (8bits) dans le fichier source
* renvoit un int, pour prendre en compte la valeur EOF (-1)
* Aucun traitement sur l'entrée lue
**/
int lire_symbole(FILE* f){
	char c;
	if (fscanf(f, "%c", &c)){
		return (int)c;
	}
	else return -1;
}
