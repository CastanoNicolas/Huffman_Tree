#include <stdlib.h>
#include <stdio.h>

//#define min(a,b) ((a)<(b)?(a):(b))

int lire_symbole(FILE* f){
    char c;
    if (fscanf(f,"%c", &c))
    {
      return (int)c;  
    }
    else return -1;   
}

void compare_file(FILE* fichier ,FILE* fichier_bis)
{

    int compteur_f1=0, compteur_f2=0;

    char lecture;

	// prec=lire_symbole(fichier);
 //    courant=lire_symbole(fichier);


    if (fichier != NULL)
    {
	    while(!(feof(fichier)))
	    {	
			lecture=lire_symbole(fichier);
	    	compteur_f1++;	    
	    	//printf("%c\n",lecture );	
	    }
	}
	else printf("Probleme lecture fichier");


	if (fichier_bis != NULL)
    {
	    while(!(feof(fichier_bis)))
	    {	
			lecture=lire_symbole(fichier_bis);
	    	compteur_f2++;	    
	    	//printf("%c\n",lecture );	
	    }
	}
	else printf("Probleme lecture fichier");

	//printf("%d",min(compteur_f1,compteur_f2));
	if (compteur_f1<compteur_f2)
	{
		printf("le fichier: test ,est le plus petit\n");
	}else{
		printf("le fichier: rle.txt ,est le plus petit\n");

	}
}

int main()
{
	FILE* fichier = NULL;
	FILE* fichier_bis = NULL;
    fichier = fopen("test", "r"); // ouverture en lecture
    fichier_bis = fopen("rle.txt", "r"); // ouverture en lecture
	//printf("NB car test= %d\n",compare_file(fichier,fichier_bis));
    compare_file(fichier,fichier_bis);
}