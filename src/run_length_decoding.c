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


void run_length_decoding(char *file_name)
{
	FILE* fichier = NULL;
	FILE* fichier_bis = NULL;
    fichier = fopen(file_name, "r"); // ouverture en lecture
	fichier_bis=fopen("rld.txt","w");
	int convert_int;
    char prec,courant;

    if(fichier_bis == NULL)
    {
    	printf("Probleme sur rld.txt");
    	return;
    }
	

	if (fichier != NULL)
	{	
		prec=lire_symbole(fichier);
		courant=lire_symbole(fichier);
		convert_int= prec - '0';

		while(!(feof(fichier)))
		{		
			for(int i=0; i<convert_int; i++)
			{
				fprintf(fichier_bis,"%c",courant);
			}

			prec=lire_symbole(fichier);
			courant=lire_symbole(fichier);
			convert_int= prec - '0';			
		}
	}
	else printf("Probleme lecture fichier");	
}

int main()
{
	run_length_decoding("rle.txt");
}