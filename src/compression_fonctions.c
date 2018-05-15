#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "utilitaire_compression.h"

void write_compressed_huffman_code(FILE* dst_file, canonical_tree* tree) {
  if (dst_file == NULL) {
    printf("Il y a eu une erreur lors de l'écriture du fichier compressé.\n");
    exit(1);
  }

  char* code_length = tree_to_length_table(tree);

  for (int i = 0; i < 256; i++) {
    fprintf(dst_file, "%c", code_length[i]);
  }
}

void write_compressed_file(char* src_file_name, char* dst_file_name,
                           canonical_tree* tree) {
  FILE* src = fopen(src_file_name, "r");
  FILE* dst = fopen(dst_file_name, "w");

  write_compressed_huffman_code(dst, tree);

  char c = lire_symbole(src);

  char octet = 0;
  char buffer;
  int cmp = 0;
  int lg;

  while (c != EOF) {
    buffer = encoder_symbole(tree, c, &lg);
    if (cmp + lg > 8) {
      octet = (octet << lg) | buffer;
      cmp = cmp + lg;
    } else if (cmp + lg == 8) {
      octet = (octet<<lg) | buffer;
      ecrire_symbole(dst, octet);
      octet = 0;
      cmp = 0;
    } else {
      char temp = buffer;
      temp = temp >> (lg - (8-cmp));
      octet = (octet<<(lg - (8-cmp))) | temp;
      ecrire_symbole(dst, octet);
      octet = (buffer << cmp) >> cmp;
      cmp = 8 - cmp;
    }
    c = lire_symbole(src);
  }

  if (!cmp) {
    ecrire_symbole(dst, octet);
  }

  fclose(src);
  fclose(dst);
}
