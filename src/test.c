#include <stdio.h>
#include <stdlib.h>

#include "compression_fonctions.h"
#include "decompression_fonction.h"


int main(){

    canonical_tree* essaie = malloc(sizeof(canonical_tree));
    essaie->caractere = -1;

    essaie->fils_droite = malloc(sizeof(canonical_tree));
    essaie->fils_droite->caractere = 'a';
    essaie->fils_droite->fils_droite = NULL;
    essaie->fils_droite->fils_gauche = NULL;

    essaie->fils_gauche = malloc(sizeof(canonical_tree));
    essaie->fils_gauche->caractere = -1;

    essaie->fils_gauche->fils_droite = malloc(sizeof(canonical_tree));
    essaie->fils_gauche->fils_droite->caractere = 'b';
    essaie->fils_gauche->fils_droite->fils_droite=NULL;
    essaie->fils_gauche->fils_droite->fils_gauche=NULL;

    essaie->fils_gauche->fils_gauche = malloc(sizeof(canonical_tree));
    essaie->fils_gauche->fils_gauche->caractere = 'c';
    essaie->fils_gauche->fils_gauche->fils_droite=NULL;
    essaie->fils_gauche->fils_gauche->fils_gauche=NULL;



    write_compressed_huffman_code("yolo.txt", essaie);

    char* tableau = read_compressed_huffman_code("yolo.txt");

    for(int i = 0; i<256;i++){
        printf("%d\n",tableau[i]);
    }


    return 0;
}