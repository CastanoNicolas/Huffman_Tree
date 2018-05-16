#ifndef COMPRESSION_FUN
#define COMPRESSION_FUN

/**
* implemente la methode de compression Move to Front
* compare octet par octet, en suivant la table ascii
* le tableau dictionnaire contient les caractères présent dans le fichier
* il associe chaque indice à un charactère du fichier
* l'ordre du dictionnaire au début n'importe pas
* Attention : ce tableau sera modifié au cours du parcours move_to_front
**/
void move_to_front_compression(FILE* fichier_lecture, FILE* fichier_ecriture);

/* RAPHAEL */
void run_length_encoding(char *file_name);

//3C analyse statique : calcul + tri des fréquences de symboles
/**
 * prend un nom de fichier en paramètre, l'ouvre en lecture.
 *  alloue (malloc) un tableau "frequences" de taille 256 -- si et seulement si on considere que tous les char ascii sont utilisés.
 * Sinon  on fait un tableau a deux dimensions avec le caractere ascii, suivit de sa frequence --
 * incrémente frequences[caractère_lu] a chaque caractere lu.
 * ferme le fichier précedement ouvert.
 * retourne le tableau frequence.
 */
int* frequencies_of_occurences(char* file_name);


/* QUENTIN */


//4C détermination des longueurs des codes des symboles
//  -- Il faut préalablement crere la structure de donnée huffman_tree
/**
 * Prend en entrée un tableau de frequences, tableaux donnée par la fonction frequencies_of_occurences
 * construit et store dans une structure de donnée (malloc) l'arbre résultat
 **/
huffman_tree* build_huffman_tree(int* frequencies);



/* ARIANNE */

void write_compressed_huffman_code(FILE* dst_file, canonical_tree* tree) ;

void write_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree);

#endif