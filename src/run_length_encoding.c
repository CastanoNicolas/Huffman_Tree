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


void run_length_encoding(FILE* fichier_source, FILE* fichier_destination)
{
	uint8_t occurence =1;
    uint8_t courant;
    uint8_t prec;
    uint8_t un = 1;

    if(fichier_destination == NULL)
    {
    	printf("Probleme");
    	return;
    }
	


	if (fichier_source != NULL)
	{	
		prec=lire_symbole(fichier_source);
		if(!(feof(fichier_source)))
			courant=lire_symbole(fichier_source);

		while(!(feof(fichier_source)))
		{
			if(prec!=courant)
			{
				fprintf(fichier_destination,"%c%c",un,prec);
			}
			else{
				while(prec==courant && occurence<=255 && !(feof(fichier_source)))
				{
					occurence++;
					prec=courant;
					courant = lire_symbole(fichier_source);
				}
				printf("occurence: %d\n",occurence );
				fprintf(fichier_destination, "%c%c", occurence, prec);
				occurence=1;
			}
			prec=courant;
			if(!(feof(fichier_source)))
			{
				courant = lire_symbole(fichier_source);
			}
		}
	}
	else printf("Probleme lecture fichier");
}



int main()
{
	FILE* fichier_source = NULL;
	FILE* fichier_destination = NULL;
    fichier_source = fopen("test", "r"); // ouverture en lecture
	fichier_destination=fopen("rle.txt","w");
	run_length_encoding(fichier_source,fichier_destination);
}