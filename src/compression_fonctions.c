#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "functions.h"
#include "utilitaire_compression.h"



/**
* implemente la methode de compression Move to Front
* compare octet par octet, en suivant la table ascii
* le tableau dictionnaire contient les caractères présent dans le fichier
* il associe chaque indice à un charactère du fichier
* l'ordre du dictionnaire au début n'importe pas
* Attention : ce tableau sera modifié au cours du parcours move_to_front
**/
void move_to_front_compression(FILE* fichier_lecture, FILE* fichier_ecriture){
  int symbole;
  char dictionnaire[TAILLE_TAB];
  int i=0;

  init_dictionnaire(dictionnaire);

  //on lit le symbole une première fois
  symbole = lire_symbole(fichier_lecture);

  while(!(feof(fichier_lecture))){
    //on recherche l'indice correspondant au symbole
    printf("%d ",symbole);
    while (dictionnaire[i] != (char)symbole && i < TAILLE_TAB){  
      i++;
    }

    printf(" %d \n",i);

    //on ecrit l'indice correspondant au symbole dans le fichier de sortie
    ecrire_octet(fichier_ecriture,(char)i);

    //on decale le tableau pour mettre à jour la frequence des derniers caractères lu
    if(i!=0){
      for(int j=i ; j >= 1 ; j--){
        dictionnaire[j]=dictionnaire[j-1];
      }
      dictionnaire[0]=symbole;
    }
    
    //reinitialise i
    i=0;
    //on traite le symbole suivant
    symbole = lire_symbole(fichier_lecture);
  }
  
} 

/* RAPHAEL */
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

          char lecture = lire_symbole(fichier); // Appel fonction
          while (feof(fichier)==0){ // tant qu'on est pas à la fin du fichier
            tab[(int)lecture]++;
            lecture = lire_symbole(fichier); // Appel fonction
          }
        fclose(fichier); // Fermeture du fichier
        return tab;
      }
      else
      {
        printf("Erreur de fichier\n");
        return NULL;
      }
    }


/* QUENTIN */


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

if(nbCara > 1){
  tricroissant(tabCara,nbCara);                                                 //on tri notre tableau a double entrée dans l'ordre croissant
}
  noeud** tabNoeud = tableau_noeud(tabCara,nbCara);                             //on créer un tableau de noeuds à partir de notre tableau trié

  noeud* tete = malloc(sizeof(noeud));                                          //on declare un noeud qui sera la tete de l'arbre final

if(nbCara > 1){
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

}

else{                                                                           //dans le cas où on a un seul caractere
  tete->poid = tabNoeud[0]->poid;                                                //on défini son poid comme le poid de l'unique
  tete->caractere = tabNoeud[0]->caractere;                                     //son caractere vaut celui de l'unique caractere
  tete->fils_gauche = NULL;                                                     //son fils_gauche est NULL
  tete->fils_droite = NULL;                                                     //son fils droit est NULL
  tete->pere = NULL;                                                             //il n'a pas de pere
}
  return tete;                                                                  //on retourne la tete de l'arbre soit l'arbre en entier car les noeuds sont liés entre eux

}

/* Ergi */
//5C génération de arbre/codes canoniques des symboles
//  -- Il faut préalablement creer la structure de donnée canonical_tree
/**
 * Prend un arbre de Huffman en entrée (donné par la fonction build_huffman_tree)
 * Construit l'arbre canonique correspondant.
 * Alloue (malloc) et store dans une structure canonical_tree l'abre canonique créé
 * retourne cet arbre canonique
 **/

/*  ETAPES
1- Parcourir l'arbre original pour construire un tableau avec tous les caracteres et leur longueur
2- Trier le tableau dans l'ordre alphabetique pour chaque niveau
3- Construire l'arbre de Huffman a partir de ce tableau

*/
canonical_tree *normal_tree_to_canonical_tree(huffman_tree *tree)
{
    if (tree == NULL)
        return NULL;

    int nbf = nb_feuilles(tree);
    tableau_constructif tab[nbf];
    int d = tree_depth(tree);
    int i = 0;
    int indice = 0;
    int *p_indice;
    p_indice = &indice;

    // construction du tableau de longueur
    for (; i <= d; i++)
    {
        construction_par_niveau(tree, i, i, p_indice, tab);
    }

    tri_tableau(tab, nbf);

/*
    for (int k = 0; k < nbf; k++)
    {
      printf("%d, ", tab[k].caractere);
      printf("%d\t", tab[k].longueur);
    }
    printf("\n");
*/
    canonical_tree *can_tree = malloc(sizeof(noeud)); //malloc la racine
    can_tree->pere = NULL;

    if (d == 0 && nbf == 1)
    {
        can_tree->caractere = tab[0].caractere;
        return can_tree;
    }

    noeud *n;
    n = can_tree; //n = racine

    int code = 0;

    int j;
    for (j = 0; j < tab[0].longueur; j++)
    {
        n->fils_gauche = malloc(sizeof(noeud));
        n->fils_gauche->pere = n;
        n->caractere = -1;
        n = n->fils_gauche;
    }
    n->caractere = tab[0].caractere;
    n->fils_gauche = NULL;
    n->fils_droite = NULL;

    for (i = 0; i < nbf - 1; i++)
    {
        code = (code + 1) << ((tab[i + 1].longueur) - (tab[i].longueur));
        n = can_tree; // n = racine
        for (j = 1; j <= tab[i+1].longueur; j++)
        {
            if ((code & (1 << (tab[i+1].longueur - j))) != 0) 
            {   // bit = 1 --> on va a droite
                if (n->fils_droite == NULL)
                {
                    n->fils_droite = malloc(sizeof(noeud));
                    n->fils_droite->pere = n;
                    n->caractere = -1;
                }
                n = n->fils_droite;
            }
            else
            {   // bit = 0 --> on va a gauche
                if (n->fils_gauche == NULL)
                {
                    n->fils_gauche = malloc(sizeof(noeud));
                    n->fils_gauche->pere = n;
                    n->caractere = -1;
                }
                n = n->fils_gauche;
            }
        }
        n->caractere = tab[i+1].caractere;
    }
    return can_tree;
}


/* ARIANNE */

void write_compressed_huffman_code(FILE* dst_file, canonical_tree* tree) {
  if (dst_file == NULL) {
    printf("Il y a eu une erreur lors de l'écriture du fichier compressé.\n");
    exit(1);
  }

  char* code_length = tree_to_length_table(tree);

  for (int i = 0; i < 256; i++) {
    fprintf(dst_file, "%c", code_length[i]);
  }
}

void write_compressed_file(char* src_file_name, char* dst_file_name,
 canonical_tree* tree) {
  FILE* src = fopen(src_file_name, "r");
  FILE* dst = fopen(dst_file_name, "w");

  write_compressed_huffman_code(dst, tree);

  char c = lire_symbole(src);

  char octet = 0;
  char buffer;
  int cmp = 0;
  int lg;

  while (c != EOF) {
    buffer = encoder_symbole(tree, c, &lg);
    if (cmp + lg > 8) {
      octet = (octet << lg) | buffer;
      cmp = cmp + lg;
    } else if (cmp + lg == 8) {
      octet = (octet<<lg) | buffer;
      ecrire_octet(dst, octet);
      octet = 0;
      cmp = 0;
    } else {
      char temp = buffer;
      temp = temp >> (lg - (8-cmp));
      octet = (octet<<(lg - (8-cmp))) | temp;
      ecrire_octet(dst, octet);
      octet = (buffer << cmp) >> cmp;
      cmp = 8 - cmp;
    }
    c = lire_symbole(src);
  }

  if (!cmp) {
    ecrire_octet(dst, octet);
  }

  fclose(src);
  fclose(dst);
}