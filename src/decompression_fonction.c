#include <stdio.h>
#include "../header/decompression_fonction.h"

char* read_compressed_huffman_code(char* src_file_name) {
  FILE* f = fopen(src_file_name, "r");

  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier compressé.\n");
    exit(1);
  }

  char* tab = malloc(sizeof(char) * 256);

  for (int i = 0; i < 256; i++) {
    fscanf(f, "%c", tab[i]);
  }
}