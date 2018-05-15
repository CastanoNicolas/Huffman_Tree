#ifndef UTIL_C
#define	UTIL_C
#endif

/**
* lire_symbole : lit un charactère (8bits) dans le fichier source
* renvoit un int, pour prendre en compte la valeur EOF (-1)
* Aucun traitement sur l'entrée lue
**/
int lire_symbole(FILE* f);

/**
* encoder_symbole : renvoit le code d'un symbole (char ascii) dans un arbre quelconque
* On renvoit un octet (char).
* Le code du symbole est placé dans les bits de poids faible.
* Le pointeur sur entier lg contient la longueur (en nombre de bit) du symbole codé. 
* Attention : Le resultat peut donc etre plus court qu'un octet.
* Convention : le poid d'un fils_gauche est mis à 0 et celui d'un fils_droit à 1. 
**/
char encoder_symbole(tree* tree, char symbole, int* lg);

/**
* Parcours d'un arbre en recherchant un symbole (char ascii)
* fonction recursive
renvoit NULL si le symbole n'est pas trouvé
* renvoit le noeud correspondant au symbole
**/
noeud* recherche_symbole_arbre(tree* tree, char symbole);

/**
* écrit dans un fichier un octet codé stocké dans chaine
**/ 
void ecrire_octet(FILE* fichier_ecriture, char chaine);