#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"


/* JULIETTE */
/**
* lire_symbole : lit un charactère (8bits) dans le fichier source
* renvoit un int, pour prendre en compte la valeur EOF (-1)
* Aucun traitement sur l'entrée lue
**/
int lire_symbole(FILE* f){
	char c;
	if (fscanf(f, "%c", &c)){
		return (int)c;
	}
	else return -1;
}

/**
* encoder_symbole : renvoit le code d'un symbole (char ascii) dans un arbre quelconque
* On renvoit un octet (char).
* Le code du symbole est placé dans les bits de poids faible.
* Le pointeur sur entier lg contient la longueur (en nombre de bit) du symbole codé. 
* Attention : Le resultat peut donc etre plus court qu'un octet.
* Convention : le poid d'un fils_gauche est mis à 0 et celui d'un fils_droit à 1. 
**/
char encoder_symbole(tree* tree, char symbole, int* lg){
	noeud *n;
	int res;
	*lg =0;

	//parcours de l'arbre en recherchant sym
	n=recherche_symbole_arbre(tree,symbole);

	//ecriture du code de sym
	//tant qu'on ne pointe pas sur la tete, c'est à dire qu'on a fini de remonter l'arbre
	while ( n != tree ){
		//si la branche vaut 1 (fils droit)
		if (n == n->parent->fils_droit)
			res +=  1 << (*lg); //on ecrit 1 (bit) décallé en fonction de la profondeur 
		//si la branche vaut 0  (fils gauche)
		else res += 0 << (*lg); //on ecrit 0 (bit) décallé en fonction de la profondeur 

		//on incremente
		n = n->parent;
		(*lg)++;
	}

	return (char)res;

}

/**
* Parcours d'un arbre en recherchant un symbole (char ascii)
* fonction recursive
renvoit NULL si le symbole n'est pas trouvé
* renvoit le noeud correspondant au symbole
**/
noeud* recherche_symbole_arbre(tree* tree, char symbole){
	noeud* n;

	//si on arrive en fin d'arbre
	if(tree == NULL){
		return NULL;
	}

	//si on a trouvé le charactère
	if(tree->caractere == symbole){
		return tree;
	}
	//sinon on parcours le fils droit pour le trouver
	else if(n = recherche_symbole_arbre(tree->fils_droit, symbole) != NULL){
		return n;
	}
	//et si il n'est pas dans le fils droit on parcours le fils gauche
	else return recherche_symbole_arbre(tree->fils_gauche, symbole);

}

/**
* écrit dans un fichier un octet codé stocké dans chaine
**/ 
void ecrire_octet(FILE* fichier_ecriture, char chaine){
	fprintf(fichier_ecriture, "%c", chaine);
}

/* ARIANE */


void parcours_arbre(canonical_tree* tree, char* tableau, int profondeur) {
	if (tree == NULL) {
		return;
	} else {
		if (tree->caractere != -1) {
			tableau[tree->caractere] = profondeur;
		}
		parcours_arbre(tree->fils_gauche, tableau, profondeur + 1);
		parcours_arbre(tree->fils_droite, tableau, profondeur + 1);
	}
}

char* tree_to_length_table(canonical_tree* tree) {
	char* table = malloc(sizeof(char) * 256);
	for (int i = 0; i < 256; i++) {
		table[i] = 0;
	}
}

/* QUENTIN */


void tricroissant( int** tab, int tab_size){
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

/* RAPHAEL */

/* NICOLAS */

/* Ergi */
int nb_feuilles(huffman_tree *tree)
{
    if (tree == NULL)
        return 0;

    if (tree->fils_gauche == NULL && tree->fils_droite == NULL)
        return 1;

    else
        return (nb_feuilles(tree->fils_gauche) + nb_feuilles(tree->fils_droite));
}

/* racine a profondeur 0 */
int tree_depth(huffman_tree *a)
{
    if (a == NULL)
        return -1;

    return (1 + max(tree_depth(a->fils_gauche), tree_depth(a->fils_droite)));
}

void construction_par_niveau(huffman_tree *tree, int level, int longueur,
                             int *p_indice, tableau_constructif *tab)
{
    if (tree == NULL)
        return;

    if (level == 0)
    {
        if (tree->fils_gauche == NULL && tree->fils_droite == NULL)
        {
            tab[*p_indice].caractere = tree->caractere;
            tab[*p_indice].longueur = longueur;
            (*p_indice)++;
        }
    }

    else if (level > 0)
    {
        construction_par_niveau(tree->fils_gauche, level - 1, longueur, p_indice, tab);
        construction_par_niveau(tree->fils_droite, level - 1, longueur, p_indice, tab);
    }
}

void tri_tableau(tableau_constructif *tab, int nbf)
{
    int indice_car_min;
    int temp;
    int inf = 0;
    int sup = 0;
    int longueur;

    while (sup < nbf)
    {
        longueur = tab[inf].longueur;
        while (longueur == tab[sup].longueur)
            sup++;

        while (inf < sup)
        {
            indice_car_min = inf;
            int i = inf;
            while (i < sup)
            {
                if (tab[i].caractere < tab[indice_car_min].caractere)
                    indice_car_min = i;
                i++;
            }
            temp = tab[inf].caractere;
            tab[inf].caractere = tab[indice_car_min].caractere;
            tab[indice_car_min].caractere = temp;
            inf++;
        }
    }
}

