#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "huffman.h"
#include "functions.h"
#include "decompression_fonction.h"

void decompression(char* file_source, char* file_destination){

	uint8_t nb_bit_invalide=0;
	FILE* f= fopen(file_source,"r");

	uint8_t* table = read_compressed_huffman_code(f,&nb_bit_invalide);
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

	printf("\n");
	canonical_tree* arbreCanonical = length_table_to_canonical_tree(tab,nbf);
	read_and_store_compressed_file(f,file_destination,arbreCanonical,(int)nb_bit_invalide);
}

void decompression_avec_pretraitement(char* file_source, char* file_destination){

	uint8_t nb_bit_invalide=0;
	FILE* f= fopen(file_source,"r");

	uint8_t* table = read_compressed_huffman_code(f,&nb_bit_invalide);
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

	canonical_tree* arbreCanonical = length_table_to_canonical_tree(tab,nbf);
	read_and_store_compressed_file(f,file_destination,arbreCanonical,(int)nb_bit_invalide);

	FILE* dest = fopen(file_destination,"r");
	FILE* temp = fopen("temp.txt","w");

	run_length_decoding(dest,temp);
	fclose(dest);
	fclose(temp);
	temp = fopen("temp.txt","r");
	dest = fopen(file_destination,"w");

	move_to_front_decompression(temp, dest);
	fclose(dest);
	fclose(temp);

	remove("temp.txt");

}