#include "../header/huffman.h"
#include "../header/utilitaire_compression.h"
#include <stdio.h>
#include <stdlib.h>

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