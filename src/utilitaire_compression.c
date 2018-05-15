#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"



int lire_symbole(FILE* f){
	char c;
	if (fscanf(f, "%c", &c)){
		return (int)c;
	}
	else return -1;
}



void tricroissant( int** tab, int tab_size)
{
  int i=0;
  int tmp0=0;
  int tmp1=0;
  int j=0;

  for(i = 0; i < tab_size; i++)          //On veut remplir la case i du tableau
    {
      for(j = i+1; j < tab_size; j++)    //On vérifie s'il n'y a pas de nombre inférieur
        {                                //Dans les cases suivantes
          if(tab[j][1] < tab[i][1])
            {

              tmp0 = tab[i][0];              //Si c'est le cas on intervertit les cases
              tab[i][0] = tab[j][0];
              tab[j][0] = tmp0;

              tmp1 = tab[i][1];              //Si c'est le cas on intervertit les cases
              tab[i][1] = tab[j][1];
              tab[j][1] = tmp1;
            }
        }
    }
}


noeud** tableau_noeud( int **tabCara,int nbCara){
	int i ;
  noeud** tabNoeud = malloc(nbCara * sizeof(noeud*));

	for ( i =0; i<nbCara ; i++) {
    noeud* temp = malloc ( sizeof (noeud) ) ;
		temp->poid = tabCara[i][1] ;
    temp->caractere = tabCara[i][0];
		temp->fils_droite = NULL;
		temp->fils_gauche = NULL;
    temp->pere = NULL;
	  tabNoeud[i] = temp ;
	}

  return tabNoeud;

}


void tricroissantNoeud( noeud** tab, int tab_size)
{
  int i=0;
  noeud* tmp;
  int j=0;

  for(i = 0; i < tab_size; i++)          //On veut remplir la case i du tableau
    {
      for(j = i+1; j < tab_size; j++)    //On vérifie s'il n'y a pas de nombre inférieur
        {                                //Dans les cases suivantes
          if(tab[j]->poid < tab[i]->poid)
            {
              tmp = tab[i];              //Si c'est le cas on intervertit les cases
              tab[i] = tab[j];
              tab[j] = tmp;

            }
        }
    }
}

void afficher_arbre (noeud* tete, int niveau) {
	int i ;
	if (tete != NULL) {
		afficher_arbre (tete->fils_droite, niveau+1);
		for ( i = 0; i < niveau ; i++){
			printf ("\t") ;
		}
		if(tete->caractere != -1){
			printf (" %d (%c)\n\n" , tete->poid, tete->caractere ) ;
		}
		else{
			printf (" %d (NULL)\n\n" ,tete->poid) ;
		}

		afficher_arbre (tete->fils_gauche , niveau+1);
	}
	return ;
}
