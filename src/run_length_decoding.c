#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


int lire_symbole(FILE* f){
    char c;
    if (fscanf(f,"%c", &c))
    {
      return (int)c;  
    }
    else return -1;   
}


void run_length_decoding(FILE* fichier_source, FILE* fichier_destination)
{
    uint8_t prec,courant;

    if(fichier_destination == NULL)
    {
    	printf("Probleme sur rld.txt");
    	return;
    }
	

	if (fichier_source != NULL)
	{	
		prec=lire_symbole(fichier_source);
		courant=lire_symbole(fichier_source);

		while(!(feof(fichier_source)))
		{		
			for(int i=0; i<prec; i++)
			{
				fprintf(fichier_destination,"%c",courant);
			}

			prec=lire_symbole(fichier_source);
			courant=lire_symbole(fichier_source);			
		}
	}
	else printf("Probleme lecture fichier");	
}

int main()
{
	FILE* fichier_source = NULL;
	FILE* fichier_destination = NULL;
    fichier_source = fopen("rle.txt", "r"); // ouverture en lecture
	fichier_destination=fopen("rld.txt","w");
	run_length_decoding(fichier_source, fichier_destination);
}