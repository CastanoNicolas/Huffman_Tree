#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "huffman.h"
#include "utilitaire_compression.h"

/**
 * implemente la methode de pretraitement Move to Front
 * compare octet par octet, en suivant la table ascii
 * le tableau dictionnaire contient les caractères présent dans le fichier
 * il associe chaque indice à un charactère du fichier
 * l'ordre du dictionnaire au début n'importe pas
 * Le fichier source contient le code à encoder
 * le fichier destination doit être vide, il contiendra le fichier encodé
 * Attention : ce tableau sera modifié au cours du parcours move_to_front
 **/
void move_to_front_compression(FILE* fichier_lecture, FILE* fichier_ecriture) {
  int symbole;
  uint8_t dictionnaire[TAILLE_TAB];
  int i = 0;

  init_dictionnaire(dictionnaire);

  // on lit le symbole une première fois
  symbole = lire_symbole(fichier_lecture);

  while (!(feof(fichier_lecture))) {
    // on recherche l'indice correspondant au symbole
    while (dictionnaire[i] != (uint8_t)symbole && i < TAILLE_TAB) {
      i++;
    }

    // on ecrit l'indice correspondant au symbole dans le fichier de sortie
    ecrire_octet(fichier_ecriture, (uint8_t)i);

    // on decale le tableau pour mettre à jour la frequence des derniers
    // caractères lu
    if (i != 0) {
      for (int j = i; j >= 1; j--) {
        dictionnaire[j] = dictionnaire[j - 1];
      }
      dictionnaire[0] = symbole;
    }

    // reinitialise i
    i = 0;
    // on traite le symbole suivant
    symbole = lire_symbole(fichier_lecture);
  }
}

/**
* implemente la methode de pretraitement RLE
* Les fichier source et destination doivent être ouvert au préalable
* Le fichier source contient le code à encoder
* le fichier destination doit être vide, il contiendra le fichier encodé
* le fichier destination contiendra une alternance de un octet a considerer comme un nombre et un octet à considerer comme un caractère ASCII
**/
void run_length_encoding(FILE* fichier_source, FILE* fichier_destination) {
  uint8_t occurence = 1;
  uint8_t courant;
  uint8_t prec;
  uint8_t un = 1;

  if (fichier_destination == NULL) {
    printf("Probleme");
    return;
  }

  if (fichier_source != NULL) {
    prec = lire_symbole(fichier_source);
    if (!(feof(fichier_source))) courant = lire_symbole(fichier_source);

    while (!(feof(fichier_source))) {
      //si il y a a seulement une occurence d'un caractère
      if (prec != courant) {
        fprintf(fichier_destination, "%c%c", un, prec);
      //sinon il y a plusieur occurence du caractère
      } else {
        //on compte le nombre d'occurence du caractère
        while (prec == courant && occurence <= 255 && !(feof(fichier_source))) {
          occurence++;
          prec = courant;
          courant = lire_symbole(fichier_source);
        }
        //maximum 255 occurences, si il y en plus, on les réecrit a la suite
        //par exemple, 510 * e, donnera dans le fichier 255e255e
        fprintf(fichier_destination, "%c%c", occurence, prec);
        occurence = 1;
      }
      //on avance
      prec = courant;
      if (!(feof(fichier_source))) {
        courant = lire_symbole(fichier_source);
      }
    }
  } else
    printf("Probleme lecture fichier");
}

// 3C analyse statique : calcul + tri des fréquences de symboles
/**
 * prend un nom de fichier en paramètre, l'ouvre en lecture.
 *  alloue (malloc) un tableau "frequences" de taille 256 -- si et seulement si
 * on considere que tous les char ascii sont utilisés. Sinon  on fait un tableau
 * a deux dimensions avec le caractere ascii, suivit de sa frequence --
 * incrémente frequences[caractère_lu] a chaque caractere lu.
 * ferme le fichier précedement ouvert.
 * retourne le tableau frequence.
 */
int* frequencies_of_occurences(char* file_name) {
  // raph
  FILE* fichier = NULL;
  int* tab = malloc(TAILLE_TAB *
                    sizeof(int));  // Malloc des 256 cases du tableau en mémoire
  for (int i = 0; i < TAILLE_TAB; i++)  // Initialisation des cases du tab à 0
  {
    tab[i] = 0;
  }
  fichier = fopen(file_name, "r");  // ouverture en lecture
  if (fichier != NULL) {
    uint8_t lecture = lire_symbole(fichier);  // Appel fonction
    while (feof(fichier) == 0) {  // tant qu'on est pas à la fin du fichier
      tab[lecture]++;
      lecture = lire_symbole(fichier);  // Appel fonction
    }
    fclose(fichier);  // Fermeture du fichier
    /*for(int i=0; i < TAILLE_TAB; i++){
      if( tab[i] != 0) printf("%d,%d",(int)i,tab[i]);
    }*/

    return tab;
  } else {
    printf("Erreur de fichier\n");
    return NULL;
  }
}

/* QUENTIN */

// 4C détermination des longueurs des codes des symboles
//  -- Il faut préalablement crere la structure de donnée huffman_tree
/**
 * Prend en entrée un tableau de frequences, tableaux donnée par la fonction
 *frequencies_of_occurences construit et store dans une structure de donnée
 *(malloc) l'arbre résultat
 **/
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

  if (nbCara > 1) {
    tricroissant(
        tabCara,
        nbCara);  // on tri notre tableau a double entrée dans l'ordre croissant
  }
  noeud** tabNoeud = tableau_noeud(
      tabCara,
      nbCara);  // on créer un tableau de noeuds à partir de notre tableau trié

  noeud* tete = malloc(
      sizeof(noeud));  // on declare un noeud qui sera la tete de l'arbre final

  if (nbCara > 1) {
    while (nbCara > 1) {
      int i = 0;

      noeud* tmp =
          malloc(sizeof(noeud));  // on initialise un noeud qui va etre créer
      tmp->poid =
          tabNoeud[i]->poid +
          tabNoeud[i + 1]
              ->poid;  // on défini son poid comme la somme des 2 plus faibles
      tmp->caractere = -1;             // son caractere vaut -1 car il n'est pas
                                       // exploitable comme caractere
      tmp->fils_gauche = tabNoeud[i];  // son fils_gauche est le fils le plus
                                       // bas
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

      noeud** tabNoeudTmp =
          malloc(nbCara * sizeof(noeud*));  // on fait un tableau de taille la
                                            // taille de tabNoeud -1
      int indicetmp = 0;  // on declare des indices pour effectuer un parcours
                          // sur tabNoeud et tabNoeudTmp
      int indice = 0;

      while (indicetmp < nbCara) {  // tant qu"on a pas rempli tabNoeudTmp
        if (tabNoeud[indice] !=
            NULL) {  // si l'element courant de tabNoeud n'est pas null
          tabNoeudTmp[indicetmp] =
              tabNoeud[indice];  // on l'ajoute au tabNoeudTmp
          indicetmp++;           // on avance dans tabNoeudTmp
        }
        indice++;  // on avance dans tabNoeud quoi qu'il arrive
      }

      free(tabNoeud);
      tabNoeud = tabNoeudTmp;  // on dit que tabNoeud pointe sur tabNoeudTmp

      tricroissantNoeud(tabNoeud, nbCara);  // on tri le nouveau tableau
    }

  }

  else {  // dans le cas où on a un seul caractere
    tete->poid =
        tabNoeud[0]->poid;  // on défini son poid comme le poid de l'unique
    tete->caractere =
        tabNoeud[0]
            ->caractere;       // son caractere vaut celui de l'unique caractere
    tete->fils_gauche = NULL;  // son fils_gauche est NULL
    tete->fils_droite = NULL;  // son fils droit est NULL
    tete->pere = NULL;         // il n'a pas de pere
  }
  return tete;  // on retourne la tete de l'arbre soit l'arbre en entier car les
                // noeuds sont liés entre eux
}

/* Ergi */
// 5C génération de arbre/codes canoniques des symboles
//  -- Il faut préalablement creer la structure de donnée canonical_tree
/**
 * Prend un arbre de Huffman en entrée (donné par la fonction
 * build_huffman_tree) Construit l'arbre canonique correspondant. Alloue (malloc)
 * et store dans une structure canonical_tree l'abre canonique créé. 
 * @return le pointeur vers la racine de cet arbre canonique
**/

/*  ETAPES
1- Parcourir l'arbre original pour construire un tableau avec tous les
caracteres et leur longueur 2- Trier le tableau dans l'ordre alphabetique pour
chaque niveau 3- Construire l'arbre de Huffman a partir de ce tableau
*/
canonical_tree* normal_tree_to_canonical_tree(huffman_tree* tree) {
  if (tree == NULL) return NULL;

  int nbf = nb_feuilles(tree);
  tableau_constructif tab[nbf];
  int d = tree_depth(tree);
  int i = 0;
  int indice = 0;
  int* p_indice;
  p_indice = &indice;

  // construction du tableau de longueur
  for (; i <= d; i++) {
    construction_par_niveau(tree, i, i, p_indice, tab);
  }

  tri_tableau(tab, nbf);

  canonical_tree* can_tree = malloc(sizeof(noeud));  // malloc la racine
  assert(can_tree != NULL);
  can_tree->fils_gauche = NULL;
  can_tree->pere = NULL;

  if (d == 0 && nbf == 1) {
    can_tree->caractere = tab[0].caractere;
    return can_tree;
  }

  noeud* n;
  n = can_tree;  // n = racine

  int code = 0;

  int j;
  for (j = 0; j < tab[0].longueur; j++) {
    n->fils_gauche = malloc(sizeof(noeud));
    n->fils_gauche->pere = n;
    n->fils_gauche->poid = 0;
    n->caractere = -1;
    n->poid = 0;
    n->fils_droite = NULL;
    n = n->fils_gauche;
  }
  n->caractere = tab[0].caractere;
  n->fils_gauche = NULL;
  n->fils_droite = NULL;

  for (i = 0; i < nbf - 1; i++) {
    code = (code + 1) << ((tab[i + 1].longueur) - (tab[i].longueur));
    n = can_tree;  // n = racine
    for (j = 1; j <= tab[i + 1].longueur; j++) {
      if ((code & (1 << (tab[i + 1].longueur - j))) !=
          0) {  // bit = 1 --> on va a droite
        if (n->fils_droite == NULL) {
          n->fils_droite = malloc(sizeof(noeud));
          n->fils_droite->pere = n;
          n->fils_droite->poid = 0;
          n->fils_droite->fils_droite = NULL;
          n->fils_droite->fils_gauche = NULL;
          n->caractere = -1;
        }
        n = n->fils_droite;
      } else {  // bit = 0 --> on va a gauche
        if (n->fils_gauche == NULL) {
          n->fils_gauche = malloc(sizeof(noeud));
          n->fils_gauche->pere = n;
          n->fils_gauche->poid = 0;
          n->fils_gauche->fils_droite = NULL;
          n->fils_gauche->fils_gauche = NULL;
          n->caractere = -1;
        }
        n = n->fils_gauche;
      }
    }
    n->caractere = tab[i + 1].caractere;
  }
  return can_tree;
}

/**
 * Cette fonction fait appel à la fonction tree_to_length_table qui renvoie le
 * tableau des longueurs de code, puis écrit ce tableau dans le fichier
 * destination.
 **/
void write_compressed_huffman_code(FILE* dst_file, canonical_tree* tree) {
  if (dst_file == NULL) {
    printf("Il y a eu une erreur lors de l'écriture du fichier compressé.\n");
    exit(1);
  }

  uint8_t* code_length = tree_to_length_table(tree);

  for (int i = 0; i < 256; i++) {
    fprintf(dst_file, "%c", code_length[i]);
  }
}

/**
 * Cette fonction écrit dans le fichier destination la compression du fichier
 * source. Le premier octet du fichier contient le nombre de bits valides. On
 * écrit ensuite la table des longueurs. Ensuite on lit chaque symbole du
 * fichier source dont on recupère le code compressé et sur lequel on appelle la
 * fonction traitement_caractere. Le dernier octet n'est pas forcément ecrit
 *dans le fichier alors on le rajoute
 **/
void write_compressed_file(char* src_file_name, char* dst_file_name,
                           canonical_tree* tree) {
  FILE* src = fopen(src_file_name, "r");
  FILE* dst = fopen(dst_file_name, "w");
  fprintf(dst, "0");
  write_compressed_huffman_code(dst, tree);

  uint8_t c = lire_symbole(src), octet = 0, *buffer;
  // printf("symbole = %c", c);
  int cmp = 0, lg, nb_bits = 0;

  while (!feof(src)) {
    buffer = encoder_symbole(tree, c, &lg);
    if (lg <= 8) {
      nb_bits += traitement_caractere(&cmp, lg, &octet, buffer, dst);
    } else {
      int nb_octet = lg / 8;
      int i = 0;
      while (i < nb_octet) {
        nb_bits += traitement_caractere(&cmp, 8, &octet, &buffer[i], dst);
        i++;
      }
      if (lg % 8 != 0) {
        nb_bits +=
            traitement_caractere(&cmp, lg % 8, &octet, &buffer[nb_octet], dst);
      }
    }
    c = lire_symbole(src);
  }

  if (cmp) {
    octet = octet << (8 - cmp);
    ecrire_octet(dst, octet);
  }
  nb_bits = nb_bits % 8;
  rewind(dst);
  fprintf(dst, "%c", nb_bits);
  fclose(src);
  fclose(dst);
}