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
1- Parcourir l'arbre original pour construire un tableau avec tous les caracteres et leur longeur
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

    int nbf_level = 0;
    canonical_tree* can_tree = malloc(sizeof(noeud));
    can_tree->pere = NULL;

    if (d == 0){
        can_tree->caractere = tab[0].caractere;
        can_tree->fils_droite = NULL;
        can_tree->fils_gauche = NULL;
    }
    else {
        while (){

            
        
            can_tree->fils_droite = malloc(sizeof(noeud));
            can_tree->fils_droite->pere = can_tree;
            can_tree->fils_gauche = malloc(sizeof(noeud));
            can_tree->fils_gauche->pere = can_tree;


        }
    }

    

    
    
}