#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "huffman.h"
#include "compression.h"
#include "decompression.h"
#include "compression_fonctions.h"
#include "utilitaire_compression.h"
#include "cli.h"

int main(int argc, char const *argv[]) {


  FILE* file_source;
  int c=0;
  int d=0;
  char* input = malloc(100*sizeof(char));
  char* input2;
  char* output = malloc(100*sizeof(char));
  char* output2 = malloc(strlen(input)+1);
  char* output2Ext = malloc(strlen(input)+1);
  
  int nbParam=0;
  int source=0;
  
  int erreur = shell(&file_source,input,&source,argc,argv,&c,&d,&nbParam,output);
  if(erreur != 0){
    affichage_erreur(erreur);
  }
  else{
    if(source == 0){
      printf("Aucun nom de fichier source saisi, veuillez le faire maintenant :\n");
      scanf("%s",input);
      while(access(input,F_OK) == -1){
        printf("Nom de fichier saisi incorrect, recommencez:\n");
        scanf("%s",input);
      }
    }
    if(c == 1){
      while(access(input,F_OK) == -1){
        printf("Nom de fichier saisi incorrect, recommencez:\n");
        scanf("%s",input);
      }
      printf("appeler compression de %s vers %s\n",input,output);
      //compression(input,output);
      
      input2 = output;
      output2Ext = strrchr(input,'.');
      *output2Ext = '\0';
      sprintf(output2,"%sbis%c",input,'\0');
      
    }
    if (d == 1){
      if(c == 0)
        printf("appeler decompression sur %s vers %s\n",input,output);
      else
        printf("appeler decompression sur %s vers %s\n",input2,output2);
        //decompression(input2,output);
    }
    
  }

  return 0;
}
