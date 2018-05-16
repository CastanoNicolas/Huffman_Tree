#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/**
* procedure qui initialise en dictionnaire en associant à chaque indice son charcatère ascii correspondant
* la taille du tableau doit etre la même que la variable global ASCII (255)
**/
void init_dictionnaire(char* dictionnaire){

  for(int i=0; i<TAILLE_TAB ; i++){
    dictionnaire[i]=(char)i;
  }
}

int max( int a , int b){
  return (a>b)?a:b;
}