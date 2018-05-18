#include "utilitaire_compression.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "huffman.h"

/**
* Renvoie la profondeur d'un symbole dans l'arbre
* renvoie 0 si le symbole n'est pas dans l'arbre ou que l'arbre est vide
**/
int profondeur(tree* tree, uint8_t symbole, int p) {
  int k;
  if (tree == NULL) {
    return 0;
  }

  // si on a trouvé le charactère
  if (tree->caractere == symbole) {
    return p;
  }
  // sinon on parcours le fils droit pour le trouver
  else if ((k = profondeur(tree->fils_gauche, symbole, p + 1)) != 0) {
    return k;
  }
  // et si il n'est pas dans le fils droit on parcours le fils gauche
  else {
    return profondeur(tree->fils_droite, symbole, p + 1);
  }
}

/**
 * encoder_symbole : renvoit le code d'un symbole (char ascii) dans un arbre quelconque.
 * On renvoit une chaine de caractère. 
 * Le code du symbole est placé dans une string, les bits de poids fort correspondant au debut du code (racine -> feuille)
 * Le pointeur sur entier lg contient la longueur (en nombre de bit) du symbole codé. 
 * Attention : Le resultat peut donc etre plus court qu'un octet. 
 * Convention : le poid d'un fils_gauche est mis à 0 et celui d'un fils_droite à 1.
 **/
uint8_t* encoder_symbole(tree* tree, uint8_t symbole, int* lg) {
  noeud* n;
  uint8_t* res = malloc(32);

  int i = 0;
  int j = 0;

  int prof = 0;

  // on initialise le tableau
  for (int k = 0; k < 32; k++) {
    res[k] = 0;
  }

  // parcours de l'arbre en recherchant sym
  n = recherche_symbole_arbre(tree, symbole);
  assert(n->caractere == symbole);

  // le nombre de bit necessaire pour ecrire le symbole 
  prof = profondeur(tree, symbole, 0);
  //la longueur vaut la profondeur
  (*lg) = prof;

  //on commence par ecrire la fin et on remonte dans l'arbre

  // i indique dans quelle case du tableau on doit commencer à écrire
  i = (prof) / 8 - 1;
  //si on est dans le cas d'un nombre non multiple de 8, alors on augmente de 1 la colonne (7 -> i=-1 -> i= 0)
  if (prof % 8 != 0) i++;

  // on indique a partir de quel rang on doit ecrire les bits 
  // si notre symbole fait 4 caractère, alors il sera ecrit dans la colonne 1, des bits 7 à 4, et j commence à 4. 
  j = (7 - ((prof % 8) - 1)) % 8;

  // ecriture du code de sym
  // tant qu'on ne pointe pas sur la tete, c'est à dire qu'on a fini de remonter l'arbre
  while (n != tree) {
    assert(i >= 0);
    assert(j >= 0);
    assert(j < 8);
    // si la branche vaut 1 (fils droit)
    if (n == n->pere->fils_droite) {
      res[i] += 1 << j;  // on ecrit 1 (bit) décallé en fonction de la profondeur
    }

    // si la branche vaut 0  (fils gauche) decalage inutile

    // on incremente
    n = n->pere;
    // longueur du code du symbole restant à ecrire
    j++;

    // si on commence un nouvel octet
    if (j == 8) {
      i--;
      j = 0;
    }
  }

  return res;
}

/**
 * Parcours d'un arbre en recherchant un symbole (char ascii)
 * fonction recursive
 * renvoit NULL si le symbole n'est pas trouvé
 * renvoit le noeud correspondant au symbole
 **/
noeud* recherche_symbole_arbre(tree* tree, uint8_t symbole) {
  noeud* n;

  // si on arrive en fin d'arbre
  if (tree == NULL) {
    return NULL;
  }

  // si on a trouvé le charactère
  if (tree->caractere == symbole) {
    return tree;
  }
  // sinon on parcours le fils droit pour le trouver
  else if ((n = recherche_symbole_arbre(tree->fils_droite, symbole)) != NULL) {
    return n;
  }
  // et si il n'est pas dans le fils droit on parcours le fils gauche
  else {
    return recherche_symbole_arbre(tree->fils_gauche, symbole);
  }
}

/**
 * Cette fonction parcours l'arbre canonique et rempli le tableau contenant les
 * longueurs des codes.
 * La fonction est récursive, pour chaque noeud elle regarde si le noeud
 * contient un caractère et rempli la bonne case du tableau si nécessaire puis
 * elle s'appelle sur ses fils.
 **/
void parcours_arbre(canonical_tree* tree, uint8_t* tableau, int profondeur) {
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

/**
 * Cette fonction initialise le tableau des longueurs à 0 puis effectue le
 * premier appel de la fonction récursive qui remplit le tableau
 **/
uint8_t* tree_to_length_table(canonical_tree* tree) {
  uint8_t* table = malloc(sizeof(uint8_t) * 256);
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }
  parcours_arbre(tree, table, 0);
  return table;
}

/* QUENTIN */

void tricroissant(int** tab, int tab_size) {
  int i = 0;
  int tmp0 = 0;
  int tmp1 = 0;
  int j = 0;

  for (i = 0; i < tab_size; i++)  // On veut remplir la case i du tableau
  {
    for (j = i + 1; j < tab_size;
         j++)  // On vérifie s'il n'y a pas de nombre inférieur
    {          // Dans les cases suivantes
      if (tab[j][1] < tab[i][1]) {
        tmp0 = tab[i][0];  // Si c'est le cas on intervertit les cases
        tab[i][0] = tab[j][0];
        tab[j][0] = tmp0;

        tmp1 = tab[i][1];  // Si c'est le cas on intervertit les cases
        tab[i][1] = tab[j][1];
        tab[j][1] = tmp1;
      }
    }
  }
}

noeud** tableau_noeud(int** tabCara, int nbCara) {
  int i;
  noeud** tabNoeud = malloc(nbCara * sizeof(noeud*));

  for (i = 0; i < nbCara; i++) {
    noeud* temp = malloc(sizeof(noeud));
    temp->poid = tabCara[i][1];
    temp->caractere = tabCara[i][0];
    temp->fils_droite = NULL;
    temp->fils_gauche = NULL;
    temp->pere = NULL;
    tabNoeud[i] = temp;
  }

  return tabNoeud;
}

void tricroissantNoeud(noeud** tab, int tab_size) {
  int i = 0;
  noeud* tmp;
  int j = 0;

  for (i = 0; i < tab_size; i++)  // On veut remplir la case i du tableau
  {
    for (j = i + 1; j < tab_size;
         j++)  // On vérifie s'il n'y a pas de nombre inférieur
    {          // Dans les cases suivantes
      if (tab[j]->poid < tab[i]->poid) {
        tmp = tab[i];  // Si c'est le cas on intervertit les cases
        tab[i] = tab[j];
        tab[j] = tmp;
      }
    }
  }
}

void afficher_arbre(noeud* tete, int niveau) {
  int i;
  fflush(stdin);
  if (tete != NULL) {
    afficher_arbre(tete->fils_droite, niveau + 1);
    for (i = 0; i < niveau; i++) {
      printf("\t");
    }
    if (tete->caractere != -1) {
      printf(" %d (%c)\n\n", niveau, tete->caractere);
    } else {
      printf(" %d (NULL)\n\n", niveau);
    }

    afficher_arbre(tete->fils_gauche, niveau + 1);
  }
  return;
}

/* RAPHAEL */

/* NICOLAS */

/* Ergi */

/**
 * Construit un tableau constructif i.e. un tableau de caracteres avec leur 
 * longueur de code a partir d'un arbre de Huffman 
**/
void construction_par_niveau(huffman_tree* tree, int level, int longueur,
                             int* p_indice, tableau_constructif* tab) {
  if (tree == NULL) return;

  if (level == 0) {
    if (tree->fils_gauche == NULL && tree->fils_droite == NULL) {
      tab[*p_indice].caractere = tree->caractere;
      tab[*p_indice].longueur = longueur;
      (*p_indice)++;
    }
  }

  else if (level > 0) {
    construction_par_niveau(tree->fils_gauche, level - 1, longueur, p_indice,
                            tab);
    construction_par_niveau(tree->fils_droite, level - 1, longueur, p_indice,
                            tab);
  }
}

/**
 * Tri le tableau constructif d'abord par longueur corissante des codes et puis pour
 * chaque segment de longeur, par ordre alphabetique des caracteres
**/
void tri_tableau(tableau_constructif* tab, int nbf) {
  int indice_car_min;
  int temp;
  int inf = 0;
  int sup = 0;
  int longueur;

  tableau_constructif tmp;
  int indice_min;

  for (int i = 0; i < nbf; i++) {
    indice_min = i;
    tmp.longueur = tab[i].longueur;
    for (int j = i; j < nbf; j++) {
      if (tab[j].longueur < tmp.longueur) {
        tmp.longueur = tab[j].longueur;
        indice_min = j;
      }
    }
    tmp.longueur = tab[indice_min].longueur;
    tmp.caractere = tab[indice_min].caractere;
    tab[indice_min].longueur = tab[i].longueur;
    tab[indice_min].caractere = tab[i].caractere;
    tab[i].longueur = tmp.longueur;
    tab[i].caractere = tmp.caractere;
  }

  while (sup < nbf) {
    longueur = tab[inf].longueur;
    while (longueur == tab[sup].longueur) sup++;

    while (inf < sup) {
      indice_car_min = inf;
      int i = inf;
      while (i < sup) {
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

/**
 * Cette fonction prend en argument octet un entier sur 8 bits et il rajoute à
 * la fin les bits valides de buffer.
 * Si l'octet est plein, on l'écrit dans le fichier destination et l'octet est
 * réinitialisé à 0 auquel on rajoute les derniers bits de buffer le cas échéant
 **/
int traitement_caractere(int* cmp, int lg, uint8_t* octet, uint8_t* buffer,
                         FILE* dst) {
  uint8_t masque = 1;
  if (*cmp + lg < 8) {
    for (int i = 0; i < lg - 1; i++) {
      masque = (masque * 2) + 1;
    }
    *buffer = (*buffer >> (8 - lg)) & masque;
    *octet = (*octet << lg) | *buffer;
    *cmp = *cmp + lg;
  } else if (*cmp + lg == 8) {
    for (int i = 0; i < 8 - *cmp - 1; i++) {
      masque = (masque * 2) + 1;
    }
    *buffer = (*buffer >> *cmp) & masque;
    *octet = (*octet << lg) | *buffer;
    ecrire_octet(dst, *octet);
    *octet = 0;
    *cmp = 0;
  } else {
    uint8_t temp = *buffer;
    for (int i = 0; i < (8 - *cmp - 1); i++) {
      masque = (masque * 2) + 1;
    }
    temp = (temp >> *cmp) & masque;
    *octet = (*octet << (8 - *cmp)) | temp;
    ecrire_octet(dst, *octet);
    *octet = 0;
    *octet = (*buffer >> (8 - lg));
    *cmp = lg - (8 - *cmp);
    masque = 1;
    for (int i = 0; i < *cmp; i++) {
      masque = (masque * 2) + 1;
    }
    *octet = *octet & masque;
  }
  return lg;
}
