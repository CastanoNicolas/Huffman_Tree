#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"
#include "decompression_fonction.h"

void decompression(char* file_source, char* file_destination){

	char nb_bit_invalide=0;
	FILE* f= fopen(file_source,"r");

	char* table = read_compressed_huffman_code(f,file_source,&nb_bit_invalide);
	nb_bit_invalide = 8 - nb_bit_invalide;
  /* affichage de la table des longueurs */
	int i=0;
	int nbf=0;
	while(i < TAILLE_TAB){
		if(table[i] != 0){
			nbf++;
		}
		i++;
	}
	tableau_constructif *tab = malloc(nbf*sizeof(tableau_constructif));

	int j=0;
	i=0;
	while(i < TAILLE_TAB){
		if(table[i] != 0){
			tab[j].caractere = i;
			tab[j].longueur = table[i];
			j++;
		}
		i++;
	}
	tri_tableau(tab,nbf);

	//printf("Dans decompression");
	//printf("\n");
	/*for(int k=0; k<nbf; k++){
		printf("%d,%d\n",tab[k].caractere,tab[k].longueur);
	}*/
	printf("\n");
	canonical_tree* arbreCanonical = length_table_to_canonical_tree(tab,nbf);
	afficher_arbre(arbreCanonical,0);
	read_and_store_compressed_file(f,file_destination,arbreCanonical,(int)nb_bit_invalide);
}