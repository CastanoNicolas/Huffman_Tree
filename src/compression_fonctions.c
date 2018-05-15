#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"

void write_compressed_huffman_code(char* dst_file_name, canonical_tree* tree) {
  FILE* f = fopen(dst_file_name, "w");

  if (f == NULL) {
    printf("Il y a eu une erreur lors de l'écriture du fichier compressé.\n");
    exit(1);
  }

  char* code_length = tree_to_length_table(tree);

  for (int i = 0; i < 256; i++) {
    fprintf(f, "%c", code_length[i]);
  }

  fclose(f);
}