#ifndef DECOMPRESSION_FUN
#define DECOMPRESSION_FUN

uint8_t* read_compressed_huffman_code(FILE* f, uint8_t* nb_bit_invalide);

canonical_tree* length_table_to_canonical_tree(tableau_constructif* tab, int taille);


void read_and_store_compressed_file(FILE* fsource, char* dst_file_name, canonical_tree* tree, int nb_bit_invalide);

/**
* Décompresse un fichier modifié avec la methode Move to Front
* le tableau initial (dictionnaire) doit être le même que celui donné à la fonction de compression
**/
void move_to_front_decompression(FILE* fichier_lecture, FILE* fichier_ecriture);
#endif