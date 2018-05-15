#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"

//COMPRESSION//
//1C prétraitement optionel des données : MTF
/**
 * A faire une fois la suite réalisée
 **/


//2C prétraitement optionel des données : RLE
/**
 * A faire une fois la suite réalisée
 **/



//3C analyse statique : calcul + tri des fréquences de symboles
/**
 * prend un nom de fichier en paramètre, l'ouvre en lecture.
 *  alloue (malloc) un tableau "frequences" de taille 256 -- si et seulement si on considere que tous les char ascii sont utilisés.
 * Sinon  on fait un tableau a deux dimensions avec le caractere ascii, suivit de sa frequence --
 * incrémente frequences[caractère_lu] a chaque caractere lu.
 * ferme le fichier précedement ouvert.
 * retourne le tableau frequence.
 */
int* frequencies_of_occurences(char* file_name){
// raph
	FILE* fichier = NULL;
	    int * tab = malloc(TAILLE_TAB*sizeof(int)); // Malloc des 256 cases du tableau en mémoire
	    for (int i=0; i<TAILLE_TAB; i++) // Initialisation des cases du tab à 0
	    {
	    	tab[i]=0;
	    }
	    fichier = fopen(file_name, "r"); // ouverture en lecture
	    if (fichier != NULL)
	    {
	        do
	        {
	            char lecture = lire_symbole(fichier); // Appel fonction
	            tab[(int)lecture]++;
	        } while (feof(fichier)==0); // tant qu'on est pas à la fin du fichier

		    fclose(fichier); // Fermeture du fichier
		    return tab;
	    }
	    else
	    {
	    	printf("Erreur de fichier\n");
        return NULL;
	    }
}




//4C détermination des longueurs des codes des symboles
//  -- Il faut préalablement crere la structure de donnée huffman_tree
/**
 * Prend en entrée un tableau de frequences, tableaux donnée par la fonction frequencies_of_occurences
 * construit et store dans une structure de donnée (malloc) l'arbre résultat
 **/
huffman_tree* build_huffman_tree(int* frequencies){
  int nbCara = 0;                                                               //On initialise une variable qui va contenir le nombre de caractere a plus de 1 occurence

  for(int i=0; i < TAILLE_TAB ; i++){                                            //on parcours le tableau de fréquences issu de frequencies_of_occurences
    if(frequencies[i] != 0){                                                    //si l'élement courant est supérieur a 0
      nbCara ++;                                                                //on incrémente nbCara
    }
  }

  int** tabCara = malloc(nbCara * sizeof(int*));                                //on déclare une tableau a 2 dimensions de taille nbCara
  int y=0;                                                                      //on déclare une variable intermédiaire pour remplie tabCara
  for(int i=0; i < TAILLE_TAB ; i++){                                            //on reparcourt le tableau de fréquences (A OPTI SI POSSIBLE POUR LIMITER LES PARCOURS)
    if(frequencies[i] != 0){
      tabCara[y] = malloc(2*sizeof(int));
      tabCara[y][0] = i;
      tabCara[y][1] = frequencies[i];
      y++;
    }
  }

  tricroissant(tabCara,nbCara);                                                 //on tri notre tableau a double entrée dans l'ordre croissant
  noeud** tabNoeud = tableau_noeud(tabCara,nbCara);                             //on créer un tableau de noeuds à partir de notre tableau trié

  noeud* tete = malloc(sizeof(noeud));                                          //on declare un noeud qui sera la tete de l'arbre final

  while(nbCara > 1){
    int i = 0;

    noeud* tmp = malloc(sizeof(noeud));                                         //on initialise un noeud qui va etre créer
    tmp->poid = tabNoeud[i]->poid + tabNoeud[i+1]->poid;                        //on défini son poid comme la somme des 2 plus faibles
    tmp->caractere = -1;                                                        //son caractere vaut -1 car il n'est pas exploitable comme caractere
    tmp->fils_gauche = tabNoeud[i];                                             //son fils_gauche est le fils le plus bas
    tmp->fils_droite = tabNoeud[i+1];                                           //son fils droit est l'autre fils un peu supérieur
    tmp->pere = NULL;                                                           //il n'a pas de pere

    tabNoeud[i]->pere = tmp;                                                    //le pere du fils gauche et droit devienne ce nouveau noeud
    tabNoeud[i+1]->pere = tmp;

    tabNoeud[i] = NULL;                                                         //on supprime le fils gauche du tableau
    tabNoeud[i+1] = tmp;                                                        //on remplace le fils droit par le nouveau noeud pour le traitement suivant
    tete = tmp;                                                                 //on fait pointé la tête sur ce nouveau noeud.

    nbCara--;                                                                   //on diminu le nombre de cara a traiter

    noeud** tabNoeudTmp = malloc(nbCara*sizeof(noeud*));                        //on fait un tableau de taille la taille de tabNoeud -1
    int indicetmp = 0;                                                          //on declare des indices pour effectuer un parcours sur tabNoeud et tabNoeudTmp
    int indice = 0;

    while(indicetmp < nbCara){                                                  //tant qu"on a pas rempli tabNoeudTmp
      if(tabNoeud[indice] != NULL){                                             //si l'element courant de tabNoeud n'est pas null
        tabNoeudTmp[indicetmp] = tabNoeud[indice];                              //on l'ajoute au tabNoeudTmp
        indicetmp++;                                                            //on avance dans tabNoeudTmp
      }
      indice++;                                                                 //on avance dans tabNoeud quoi qu'il arrive
    }

    free(tabNoeud);
    tabNoeud = tabNoeudTmp;                                                     //on dit que tabNoeud pointe sur tabNoeudTmp

    tricroissantNoeud(tabNoeud,nbCara);                                         //on tri le nouveau tableau
  }

  return tete;

}






//5C génération de arbre/codes canoniques des symboles
//  -- Il faut préalablement creer la structure de donnée canonical_tree
/**
 * Prend un arbre de Huffman en entrée (donné par la fonction build_huffman_tree)
 * Construit l'arbre canonique correspondant.
 * Alloue (malloc) et store dans une structure canonical_tree l'abre canonique créé
 * retourne cet arbre canonique
 **/
/*canonical_tree* normal_tree_to_canonical_tree(huffman* tree){

}*/






//6C écriture de table des longueurs (après compression RLEoptionnelle)
// -- Il faut préalablement choisir le format d'écriture des longueur
/**
 * Ecrit dans le fichier dst_file_name la table des longueurs
 * de l'arbre canonique donné en paramètre (donné par la fonction normal_tree_to_canonical_tree)
 * Le fichier est ouvert en ecriture avec effacement préalable du contenu
 * Le fichier doit etre ouvert et fermé dans la fonction
 * le format d'écriture doit etre reflechi (potentiellement avec le groupe)
 **/
/*void write_compressed_huffman_code(char* dst_file_name,canonical_tree* tree);*/




//7C transcodage + écriture, symbole par symbole.
// -- Il faut absolument encapsuler le code pour qu'il n'y ai pas de traitement bas niveau
// ex: - lire_symbole qui va lrie un caractere ascii dans le fichier source
//	   - encoder_symbole qui va chercher la correspondance dans l'arbe canonique d'un symbole ( le resultat peut etre plus court qu'un octet)
//	   - ecrire_octet qui ecrit un octet de donnée
// Il faut donc faire  attention a ne pas ecrire les symbole un par un, puisqu'il peut y avoir deux symbole dans un octet
// Il n'y pas de moyen en C d'ecrire bit par bit
/**
 * Ecrit dans le fichier dst_file_name les caractère lu dans le fichier src_file_name
 * Les caractère lus sont encodé selon le code donné par l'arbre canonique "tree"
 * Tout les caractère lu et encodé sont directement écrit dans le fichier de destination sans caractère de séparation
 * Le fichier de destination est ouvert en "écriture a la suite"
 * le fichier source est ouvert en lecture seule.
 * Tout les fichiers sont fermé a la fin de la fonction.
 **/
/*void write_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree);*/
