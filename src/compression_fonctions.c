#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"

#define TAILLE_TAB 256

int* frequencies_of_occurences(char* file_name) {
  FILE* fichier = NULL;
  int* tab = malloc(TAILLE_TAB *
                    sizeof(int));  // Malloc des 256 cases du tableau en mémoire
  for (int i = 0; i < TAILLE_TAB; i++)  // Initialisation des cases du tab à 0
  {
    tab[i] = 0;
  }
  fichier = fopen(file_name, "r");  // ouverture en lecture
  if (fichier != NULL) {
    do {
      char lecture = lire_symbole(fichier);  // Appel fonction
      tab[(int)lecture]++;
    } while (feof(fichier) == 0);  // tant qu'on est pas à la fin du fichier

    fclose(fichier);  // Fermeture du fichier
    return tab;
  } else {
    printf("Erreur de fichier\n");
    return NULL;
  }
}

huffman_tree* build_huffman_tree(int* frequencies) {
  int nbCara = 0;  // On initialise une variable qui va contenir le nombre de
                   // caractere a plus de 1 occurence

  for (int i = 0; i < TAILLE_TAB;
       i++) {                   // on parcours le tableau de fréquences issu de
                                // frequencies_of_occurences
    if (frequencies[i] != 0) {  // si l'élement courant est supérieur a 0
      nbCara++;                 // on incrémente nbCara
    }
  }

  int** tabCara = malloc(
      nbCara *
      sizeof(int*));  // on déclare une tableau a 2 dimensions de taille nbCara
  int y = 0;  // on déclare une variable intermédiaire pour remplie tabCara
  for (int i = 0; i < TAILLE_TAB;
       i++) {  // on reparcourt le tableau de fréquences (A OPTI SI POSSIBLE
               // POUR LIMITER LES PARCOURS)
    if (frequencies[i] != 0) {
      tabCara[y] = malloc(2 * sizeof(int));
      tabCara[y][0] = i;
      tabCara[y][1] = frequencies[i];
      y++;
    }
  }

  tricroissant(
      tabCara,
      nbCara);  // on tri notre tableau a double entrée dans l'ordre croissant
  noeud** tabNoeud = tableau_noeud(
      tabCara,
      nbCara);  // on créer un tableau de noeuds à partir de notre tableau trié

  noeud* tete = malloc(
      sizeof(noeud));  // on declare un noeud qui sera la tete de l'arbre final

  while (nbCara > 1) {
    int i = 0;

    noeud* tmp =
        malloc(sizeof(noeud));  // on initialise un noeud qui va etre créer
    tmp->poid =
        tabNoeud[i]->poid +
        tabNoeud[i + 1]
            ->poid;  // on défini son poid comme la somme des 2 plus faibles
    tmp->caractere = -1;  // son caractere vaut -1 car il n'est pas exploitable
                          // comme caractere
    tmp->fils_gauche = tabNoeud[i];  // son fils_gauche est le fils le plus bas
    tmp->fils_droite =
        tabNoeud[i + 1];  // son fils droit est l'autre fils un peu supérieur
    tmp->pere = NULL;     // il n'a pas de pere

    tabNoeud[i]->pere =
        tmp;  // le pere du fils gauche et droit devienne ce nouveau noeud
    tabNoeud[i + 1]->pere = tmp;

    tabNoeud[i] = NULL;     // on supprime le fils gauche du tableau
    tabNoeud[i + 1] = tmp;  // on remplace le fils droit par le nouveau noeud
                            // pour le traitement suivant
    tete = tmp;             // on fait pointé la tête sur ce nouveau noeud.

    nbCara--;  // on diminu le nombre de cara a traiter

    noeud** tabNoeudTmp = malloc(
        nbCara *
        sizeof(
            noeud*));   // on fait un tableau de taille la taille de tabNoeud -1
    int indicetmp = 0;  // on declare des indices pour effectuer un parcours sur
                        // tabNoeud et tabNoeudTmp
    int indice = 0;

    while (indicetmp < nbCara) {  // tant qu"on a pas rempli tabNoeudTmp
      if (tabNoeud[indice] !=
          NULL) {  // si l'element courant de tabNoeud n'est pas null
        tabNoeudTmp[indicetmp] = tabNoeud[indice];  // on l'ajoute au
                                                    // tabNoeudTmp
        indicetmp++;  // on avance dans tabNoeudTmp
      }
      indice++;  // on avance dans tabNoeud quoi qu'il arrive
    }

    free(tabNoeud);
    tabNoeud = tabNoeudTmp;  // on dit que tabNoeud pointe sur tabNoeudTmp

    tricroissantNoeud(tabNoeud, nbCara);  // on tri le nouveau tableau
  }

  return tete;
}

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

  fprintf(dst, "%c", 0);

  write_compressed_huffman_code(dst, tree);

  char c = lire_symbole(src);

  char octet = 0;
  char buffer;
  int cmp = 0;
  unsigned int nb_bits = 0;
  int lg;
  while (!feof(src)) {
    buffer = encoder_symbole(tree, c, &lg);
    if (cmp + lg < 8) {
      octet = (octet << lg);
      octet = octet | buffer;
      cmp = cmp + lg;
      nb_bits += lg;
    } else if (cmp + lg == 8) {
      octet = (octet << lg) | buffer;
      ecrire_symbole(dst, octet);
      octet = 0;
      cmp = 0;
      nb_bits += lg;
    } else {
      char temp = buffer;
      temp = temp >> (8 - cmp);
      octet = (octet << (8 - cmp)) | temp;
      ecrire_symbole(dst, octet);
      octet = (buffer << cmp) >> cmp;
      cmp = lg - (8 - cmp);
      nb_bits += lg - (8 - cmp);
    }
    c = lire_symbole(src);
  }

  if (cmp) {
    octet = octet<< (8-cmp);
    ecrire_symbole(dst, octet);
    nb_bits += cmp;
  }

  nb_bits = nb_bits % 8;

  rewind(dst);

  fprintf(dst, "%c", nb_bits);

  fclose(src);
  fclose(dst);
}
