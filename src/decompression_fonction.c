#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "huffman.h"
#include "utilitaire_decompression.h"
#define ASCII 255
/**
 * @File decompression_fonction.c
 * @Brief contient les fonctions liée a la decompression.
 **/


uint8_t* read_compressed_huffman_code(FILE* f, uint8_t* nb_bit_invalide) {
  uint8_t* tab = malloc(sizeof(uint8_t) * 256);
  fscanf(f, "%c", nb_bit_invalide);
  for (int i = 0; i < 256; i++) {
    fscanf(f, "%c", &tab[i]);
  }

  return tab;
}

/**
 * Construit l'arbre canonique a partir a partir d'un tableau constructif
 * i.e. un tableau avec les caracteres de l'arbre et leur longueur de code
**/
canonical_tree* length_table_to_canonical_tree(tableau_constructif* tab,
                                               int taille) {
  canonical_tree* can_tree = malloc(sizeof(noeud));  // malloc la racine
  can_tree->pere = NULL;
  can_tree->fils_gauche = NULL;

  int nbf = taille;
  int d = tab[taille - 1].longueur;
  int i = 0;

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
 * Cette fonction Prend un pointeur sur fichier compressé en parametre ainsi que l'arbre canonique créé au préalable.
 * Grace a cet arbre on peut décoder le fichier compressé a la volée. On lit jusqua pouvoir decoder un symbole, puis on écrit cet octet 
 * dans le fichier ouvert en écriture nommé par le param dst_file_name. 
 * A la fin le fichier destination contient le fichier d'entrée entierement decodé.
 * Le parametre nb_bit_invalide indique combien de bit ne sont pas a considerer dans le dernier octet.
**/
void read_and_store_compressed_file(FILE* fsrc, char* dst_file_name,
                                    canonical_tree* tree, int nb_bit_invalide) {
  // ouverture des fichiers
  FILE* fdst = fopen(dst_file_name, "w");

  uint8_t c, c_suivant, c_ascii;
  canonical_tree* t = tree;
  int i = 0, est_dernier_octet = 0;

  est_dernier_octet = !fscanf(fsrc, "%c", &c);
  printf("%d", est_dernier_octet);

  fflush(stdin);

  if (!est_dernier_octet) est_dernier_octet = !fscanf(fsrc, "%c", &c_suivant);

  while (!est_dernier_octet) {
    t = tree;

    // tant que l'on parcours l'arbre, que la fin de fichier n'est pas reach, et
    // que l'on est pas dans une feuille
    while (t != NULL && t->caractere == -1 && i != 8) {
      // si le bit i de c vaut 0 alors on se deplace dans le fils gauche
      if ((c & 0x1 << (7 - i)) == 0) t = t->fils_gauche;
      // sinon il vaut 1 et on va donc dans le fils droit
      else
        t = t->fils_droite;
      i++;
      // si on a parcouru un octet entier, on passe à l'octet suivant pour lire
      // la fin du symbole
      if (i == 8 && !est_dernier_octet) {
        i = 0;
        c = c_suivant;
        fscanf(fsrc, "%c", &c_suivant);
        est_dernier_octet = feof(fsrc);
      }
    }

    // le code du symbole n'est pas valide / problème de decodage
    if (t == NULL) {
      printf("Erreur lors du decodage milieu\n");
      exit(1);
    }
    // fin de fichier et caractère non valide (on a pas attent une feuille)
    if (i == 8 && t->caractere == -1) {
      printf("Erreur lors de la lecture d'un symbole\n");
      exit(2);
    }
    assert(t->caractere != -1);
    // on recupere la valeur du symbole encodé et on l'ecrit
    c_ascii = (t->caractere) & 0xFF;
    ecrire_octet(fdst, c_ascii);
  }

  // il faut tester les derniers bits
  if (est_dernier_octet && i <= 8 - nb_bit_invalide) {
    while (i < (8 - nb_bit_invalide)) {
      // on attaque un nouveau symbole a decoder
      t = tree;
      while (t != NULL && t->caractere == -1 && i <= 8 - nb_bit_invalide) {
        if ((c & 0x1 << (7 - i)) == 0)
          t = t->fils_gauche;
        else
          t = t->fils_droite;
        i++;
      }

      // le code du symbole n'est pas valide / problème de decodage
      if (t == NULL) {
        printf("Erreur lors du decodage dernier\n");
        exit(11);
      }
      // fin de fichier et caractère non valide (on a pas attent une feuille)
      if (i == (8 - nb_bit_invalide) && t->caractere == -1) {
        printf("Erreur lors de la lecture du dernier symbole\n");
        exit(12);
      }
      assert(t->caractere != -1);

      c_ascii = (t->caractere) & 0xFF;
      ecrire_octet(fdst, c_ascii);
    }
  }

  fclose(fsrc);
  fclose(fdst);
  return;
}

/**
* implemente la methode de décodage du pretraitement RLE
* Les fichier source et destination doivent être ouvert au préalable
* le fichier destination contiendra une alternance de un octet a considerer comme un nombre et un octet à considerer comme un caractère ASCII
* Le fichier source contient le code encodé
* Le fichier destination doit être vide, il contiendra le fichier decodé
**/
void run_length_decoding(FILE* fichier_source, FILE* fichier_destination) {
  uint8_t prec, courant;

  if (fichier_destination == NULL) {
    printf("Probleme sur rld.txt");
    return;
  }

  if (fichier_source != NULL) {
    prec = lire_symbole(fichier_source);
    if (!(feof(fichier_source))) courant = lire_symbole(fichier_source);

    //on décode
    while (!(feof(fichier_source))) {
      for (int i = 0; i < prec; i++) {
        fprintf(fichier_destination, "%c", courant);
      }
      //on avance
      prec = lire_symbole(fichier_source);
      if (!(feof(fichier_source))) courant = lire_symbole(fichier_source);
    }
  } else
  printf("Probleme lecture fichier");
}

/**
 * Décompresse un fichier modifié avec la methode Move to Front
 * Le tableau initial (dictionnaire) doit être le même que celui donné à la
 * fonction de compression
 * Le fichier source contient le code encodé
 * Le fichier destination doit être vide, il contiendra le fichier decodé
 **/
void move_to_front_decompression(FILE* fichier_lecture,
                                 FILE* fichier_ecriture) {
  int indice;
  uint8_t dictionnaire[ASCII];
  int tmp;

  init_dictionnaire(dictionnaire);

  // on lit le symbole une première fois
  indice = lire_symbole(fichier_lecture);

  while (!(feof(fichier_lecture))) {
    // on ecrit le symbole correspondant à l'indice dans le fichier de sortie
    tmp = dictionnaire[indice];
    ecrire_octet(fichier_ecriture, tmp);

    // on decale le tableau pour mettre à jour la frequence des derniers
    // caractères lu
    if (indice != 0) {
      for (int j = indice; j >= 1; j--) {
        dictionnaire[j] = dictionnaire[j - 1];
      }
      dictionnaire[0] = tmp;
    }

    // on traite le symbole suivant
    indice = lire_symbole(fichier_lecture);
  }
}
