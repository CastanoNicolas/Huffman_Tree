#include "../header/huffman.h"
#include "../header/utilitaire_compression.h"
#include <stdio.h>
#include <stdlib.h>

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
canonical_tree* normal_tree_to_canonical_tree (huffman_tree* tree){
	if (tree == NULL)
		return NULL;
		
	int nbf = nb_feuilles(tree);
	tableau_constructif tab [nbf];
	int d = tree_depth(tree);
	int i = 0;
	int indice = 0;
	int* p_indice;
	p_indice = &indice;

	for (; i <= d; i++){
		construction_par_niveau(tree, i, i, p_indice, tab);
	}

    tri_tableau(tab, nbf);

    int nbf_level = 0;
    canonical_tree* can_tree = malloc(sizeof(noeud)); //malloc la racine
    can_tree->pere = NULL; 
    noeud* n;
    n = can_tree; //n = racine

    if (d == 0){
        can_tree->caractere = tab[0].caractere;
        can_tree->fils_droite = NULL;
        can_tree->fils_gauche = NULL;
    }
    else {
        int inf = 0;
        int sup = 0;
        int longueur;
        int level;

        i = 0;
        while (i < nbf){
            longueur = tab[inf].longueur;
            level = 1;
            
            while(longueur == tab[sup].longueur)
                sup++;

            nbf_level = sup - inf;

            n->fils_gauche = malloc(sizeof(noeud));
            n->fils_gauche->pere = n;            
            n->fils_droite = malloc(sizeof(noeud));
            n->fils_droite->pere = n;

        }
    }

}