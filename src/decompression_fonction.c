#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"
#include "functions.h"
#include "utilitaire_decompression.h"
#define ASCII 255


char* read_compressed_huffman_code(char* src_file_name) {
  FILE* f = fopen(src_file_name, "r");

  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier compressé.\n");
    exit(1);
  }

  char* tab = malloc(sizeof(char) * 256);

  for (int i = 0; i < 256; i++) {
    fscanf(f, "%c", &tab[i]);
  }

  return tab;
}

canonical_tree* length_table_to_canonical_tree(char* table){
	return NULL;
}

void read_and_store_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree){

	FILE* fsrc = fopen(src_file_name,"r");
	FILE* fdst = fopen(dst_file_name,"w");

	char c, c_ascii;
	canonical_tree* t=tree;
	int i =0;
	do(){
		t=tree;
		fscanf(fsrc,"%c",&c);

		while(t != NULL && !feof(fsrc) && t->caractere == -1){
			if( (c & 0x1<< i) == 0 )
				t=t->fils_gauche;
			else 
				t=t->fils_droite;
			i++;
			if(i == 8){
				i=0;
				fscanf(fsrc,"%c",&c);				
			} 
		}
		
		if(t == NULL)
			printf("Erreur lors du decodage\n");
		
		if(feof(fsrc) && t->caractere == -1){
			printf("Erreur lors de la lecture du dernier symbole\n");
			exit(1);
		}
		else if (feof(fsrc) && t->caractere !=-1)
			printf("Pas de fichiers résiduels\n");


		c_ascii = (t->caractere) & 0xFF;
		ecrire_octet(fdst, c_ascii);

	}while(!feof(fsrc));

	// il faut tester les derniers bits
	while(i < 8){
		t=tree;
		while(t->caractere == -1 && i<8 ){
			if( (c & 0x1<< i) == 0 )
				t=t->fils_gauche;
			else 
				t=t->fils_droite;
			i++;
		}
		if(t->caractere != -1){
			c_ascii = (t->caractere) & 0xFF;
			ecrire_octet(fdst, c_ascii);
		}

	}

	close(fsrc);
	close(fdst);
	return;
}


/**
* Décompresse un fichier modifié avec la methode Move to Front
* le tableau initial (dictionnaire) doit être le même que celui donné à la fonction de compression
**/
void move_to_front_decompression(FILE* fichier_lecture, FILE* fichier_ecriture){
	int indice;
	char dictionnaire[ASCII];
	int tmp;

	init_dictionnaire(dictionnaire);

	//on lit le symbole une première fois
	indice = lire_symbole(fichier_lecture);

	while(!(feof(fichier_lecture))){

		//on ecrit le symbole correspondant à l'indice dans le fichier de sortie
		tmp = dictionnaire[indice];
		ecrire_octet(fichier_ecriture,tmp);

		//on decale le tableau pour mettre à jour la frequence des derniers caractères lu
		if(indice!=0){
			for(int j=indice ; j >= 1 ; j--){
				dictionnaire[j]=dictionnaire[j-1];
			}
			dictionnaire[0]=tmp;
		}

		//on traite le symbole suivant
		indice = lire_symbole(fichier_lecture);
	}

}