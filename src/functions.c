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
