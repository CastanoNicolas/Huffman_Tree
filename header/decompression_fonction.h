#ifndef DECOMPRESSION_FUN
#define DECOMPRESSION_FUN

char* read_compressed_huffman_code(char* src_file_name);

canonical_tree* length_table_to_canonical_tree(char* table);


void read_and_store_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree);

/**
* Décompresse un fichier modifié avec la methode Move to Front
* le tableau initial (dictionnaire) doit être le même que celui donné à la fonction de compression
**/
void move_to_front_decompression(FILE* fichier_lecture, FILE* fichier_ecriture);
#endif