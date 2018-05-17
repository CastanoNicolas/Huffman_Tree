#include <stdio.h>
#include <stdlib.h>


int shell(FILE** fichier_entree,char* input, int* source,int argc, char const *argv[], int *c, int *d, int* nbParam,char output[]){
	
	int erreur = 0;
	int fichier_present=0;
	int custom_name=0;
	int i=1;

	while(i < argc && !erreur){
		if( *argv[i] == '-' ){
			// on regarde s'il y a un -c
			if(argv[i][1] == 'c'){
				if(*c==1){
         erreur = 1;  
        }
				else{
          *c=1; 
          *nbParam=1;
        } 
			}
			// on regarde s'il y a un -d
			else if(argv[i][1] == 'd'){
				if(*d == 1){
          erreur = 2;
        }
				else{
					*d=1;	
          *nbParam=1;
				} 
			}
			// on regarde s'il y a un -o
			else if(argv[i][1] == 'o'){
				if(custom_name ==1) erreur = 3;
				else {
					custom_name=1;
					if(i != (argc-1) && argv[i+1][0] != '-'){
						sprintf(output,"%s%s%c",argv[i+1],".dhf",'\0');
            
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
				sprintf(input,"%s%c", argv[i],'\0');
        *source = 1;
			}
		}
		i++;
	}
  
  if(*nbParam == 0){
    erreur = 8;
  } 
	if((*fichier_entree = fopen(input,"r")) == NULL){
    *fichier_entree = stdin;
  } 
	if(custom_name == 0) {
    sprintf(output,"fichier_destination.dhf%c",'\0');
  }
	return erreur;
}


void affichage_erreur(int erreur){

	switch(erreur){
		case 1:
			printf("Only one -c expected.\n");
			break;
		case 2:
			printf("Only one -d expected.\n");
			break;
		case 3:
			printf("Only one -o expected.\n");
			break;
		case 4:
			printf("-o expected before destination file.\n");
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
    case 8:
      printf("At least one option needed (-c for compression / -d for decompression)\n");
      break;
	}
	printf("Exiting program.\n");
}