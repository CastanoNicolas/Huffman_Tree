#include <stdio.h>
#include <stdlib.h>
//#include "huffman.h"
//#include "compression_fonctions.h"
//#include "utilitaire_compression.h"


int shell(FILE** fichier_entree, int argc, char const *argv[], int *c, int *d, char output[]){
	
	int erreur = 0;
	int fichier_present=0;
	int custom_name=0;
	char nom_fichier[100];
	int i =1;

	while(i < argc && !erreur){
		if( *argv[i] == '-' ){
			// on regarde s'il y a un -c
			if(argv[i][1] == 'c'){
				if(*c==1) erreur = 1;
				else *c=1;
			}
			// on regarde s'il y a un -d
			else if(argv[i][1] == 'd'){
				if(*d == 1) erreur = 2;
				else{
					*d=1;	
				} 
			}
			// on regarde s'il y a un -o
			else if(argv[i][1] == 'o'){
				if(custom_name ==1) erreur = 3;
				else {
					custom_name=1;
					if(i != (argc-1) && argv[i+1][0] != '-'){
						sprintf(output,"%s%c",argv[i+1],'\0');
						i++;
					}
					else
						erreur = 5;
				}
			}
      else{
        erreur = 7;
      }
		}
		else{
			if(fichier_present ==1){
				erreur =  4;
			}
			else{
				fichier_present = 1;
				sprintf(nom_fichier,"%s%c", argv[i],'\0');
			}
		}
		i++;
	}

	if((*fichier_entree = fopen(nom_fichier,"r")) == NULL) *fichier_entree = stdin;
	if(custom_name == 0) sprintf(output,"image%c",'\0');
	return erreur;
}


void affichage_erreur(int erreur){

	switch(erreur){
		case 1:
			printf("Only one -g expected.\n");
			break;
		case 2:
			printf("Only one -b expected.\n");
			break;
		case 3:
			printf("Only one -o expected.\n");
			break;
		case 4:
			printf("Only one file expected.\n");
			break;
		case 5:
			printf("Expect a file name after -o.\n");
			break;
		case 6:
			printf("Incorrect image syntax.\n");
			break;
    case 7:
  		printf("One option invalid.\n");
  		break;
	}
	printf("Exiting program.\n");
}


int main(int argc, char const *argv[]) {

  /*int* frequence = frequencies_of_occurences("test.txt");
  for(int i=0;i<256;i++){
    if(frequence[i] != 0){
      printf("%c %d\n",i,frequence[i]);
    }
  }
  huffman_tree* arbre = build_huffman_tree(frequence);
  afficher_arbre(arbre,0);

  return 0;*/
  
  FILE* file_source;
  int c;
  int d;
  char* output = malloc(100*sizeof(char));
  
  int erreur = shell(&file_source,argc,argv,&c,&d,output);
  if(erreur != 0){
    affichage_erreur(erreur);
  }
  else{
    printf("syntaxe ok\n");
  }
  
}
