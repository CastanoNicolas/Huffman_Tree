#include <stdio.h>
#include <stdlib.h>

#define ASCII 255

int lire_symbole(FILE* f){
	char c;
	if (fscanf(f, "%c", &c)){
		return (int)c;
	}
	else return -1;
}

void ecrire_octet(FILE* fichier_ecriture, char chaine){
	fprintf(fichier_ecriture, "%c", chaine);
}


/**
* procedure qui initialise en dictionnaire en associant à chaque indice son charcatère ascii correspondant
* la taille du tableau doit etre la même que la variable global ASCII (255)
**/
void init_dictionnaire(char* dictionnaire){

	for(int i=0; i<ASCII ; i++){
		dictionnaire[i]=(char)i;
	}
}

/**
* implemente la methode de compression Move to Front
* compare octet par octet, en suivant la table ascii
* le tableau dictionnaire contient les caractères présent dans le fichier
* il associe chaque indice à un charactère du fichier
* l'ordre du dictionnaire au début n'importe pas
* Attention : ce tableau sera modifié au cours du parcours move_to_front
**/
void move_to_front_compression(FILE* fichier_lecture, FILE* fichier_ecriture){
	int symbole;
	char dictionnaire[ASCII];
	int i=0;

	init_dictionnaire(dictionnaire);

	//on lit le symbole une première fois
	symbole = lire_symbole(fichier_lecture);

	while(!(feof(fichier_lecture))){
		//on recherche l'indice correspondant au symbole
		printf("%d ",symbole);
		while (dictionnaire[i] != (char)symbole && i < ASCII){	
			i++;
		}

		printf(" %d \n",i);

		//on ecrit l'indice correspondant au symbole dans le fichier de sortie
		ecrire_octet(fichier_ecriture,(char)i);

		//on decale le tableau pour mettre à jour la frequence des derniers caractères lu
		if(i!=0){
			for(int j=i ; j >= 1 ; j--){
				dictionnaire[j]=dictionnaire[j-1];
			}
			dictionnaire[0]=symbole;
		}
		
		//reinitialise i
		i=0;
		//on traite le symbole suivant
		symbole = lire_symbole(fichier_lecture);
	}
	
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


int main(){

	FILE* f_mtf;
	FILE* f_lec;
	FILE* f_dec;

	if ((f_lec = fopen("f_lec","r")) == NULL){
		fprintf(stderr,"Impossible d'ouvrir le fichier données en lecture 1\n");
		return 1;
	}

	if ((f_mtf = fopen("f_mtf","w")) == NULL){
		fprintf(stderr,"Impossible d'ouvrir le fichier données en lecture 2 \n");
		return 1;
	}

	move_to_front_compression(f_lec,f_mtf);

	fclose(f_mtf);

	if ((f_mtf = fopen("f_mtf","r")) == NULL){
		fprintf(stderr,"Impossible d'ouvrir le fichier données en lecture 3 \n");
		return 1;
	}

	if ((f_dec = fopen("f_dec","w")) == NULL){
		fprintf(stderr,"Impossible d'ouvrir le fichier données en lecture 4 \n");
		return 1;
	}

	
	move_to_front_decompression(f_mtf,f_dec);

	return 0;

}
