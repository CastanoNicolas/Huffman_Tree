#include <stdlib.h>
#include <stdio.h>

int lire_symbole(FILE* f){
    char c;
    if (fscanf(f,"%c", &c))
    {
      return (int)c;  
    }
    else return -1;   
}


void run_length_encoding(char *file_name)
{
	FILE* fichier = NULL;
	FILE* fichier_bis = NULL;
    fichier = fopen(file_name, "r"); // ouverture en lecture
	fichier_bis=fopen("rle.txt","w");

	int occurence =1;
    char courant;
    char prec;

    if(fichier_bis == NULL){
    	printf("Probleme");
    	return;
    }
	


	if (fichier != NULL)
	{	
		prec=lire_symbole(fichier);
		courant=lire_symbole(fichier);

		while(!(feof(fichier)))
		{
			
			if(prec!=courant)
			{
				fprintf(fichier_bis,"1%c",prec);
			}
			else{
				while(prec==courant && occurence<=255 && !(feof(fichier)))
				{
					occurence++;
					prec=courant;
					courant = lire_symbole(fichier);
				}
				fprintf(fichier_bis, "%c%c", (char)(occurence + '0'), prec);
				occurence=1;
			}
			prec=courant;
			if(!(feof(fichier))){
				courant = lire_symbole(fichier);
			}
			
		}
	}
	else printf("Probleme lecture fichier");
	
}



int main()
{
run_length_encoding("test");

}