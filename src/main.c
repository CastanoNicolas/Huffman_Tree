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
  int p=0;
  char* input = malloc(100*sizeof(char));
  char* output = malloc(100*sizeof(char));
  char* outputCompressed = malloc(strlen(input)+1);
  
  int nbParam=0;
  int source=0;
  
  if(argc == 1){
    printf("Exemple d'execution :\n");
    printf("./argc0 -c fichier_entree -o fichier_compresse\n");
    printf("./argc0 -d fichier_compresse -o fichier_decompresse\n");
    printf("./argc0 -c fichier_entree -d -o fichier_decompresse\n");
    printf("./argc0 -c fichier_entree -o fichier_compresse -p\n");
    return -1;
  }
  int erreur = shell(&file_source,input,&source,argc,argv,&c,&d,&p,&nbParam,output);
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

      if(d==1){
        sprintf(outputCompressed,"%s%s%c",input,".chf",'\0');
        if(p==0){
          printf("On effectue la compression de %s vers %s\n",input,outputCompressed);
          compression(input,outputCompressed);
        }
        else{
          printf("On effectue la compression avec pretraitement de %s vers %s\n",input,outputCompressed);
          compression_avec_pretaitement(input,outputCompressed);
        }
        
      }
      else{
        if(p==0){
          printf("On effectue la compression de %s vers %s\n",input,output);
          compression(input,output);
        }
        else{
          printf("On effectue la compression avec pretraitement de %s vers %s\n",input,output);
          compression_avec_pretaitement(input,output);
        }  
      }
      
    }
    if (d == 1){
      if(c == 0){
        if(p==0){
          printf("On effectue la decompression sur %s vers %s\n",input,output);
          decompression(input,output);
        }
        else{
          printf("On effectue la decompression avec pretraitement sur %s vers %s\n",input,output);
          decompression_avec_pretraitement(input,output);
        }
      }
      else{
        if(p==0){
          printf("On effectue la decompression sur %s vers %s\n",outputCompressed,output);
          decompression(outputCompressed,output);
        }
        else{
          printf("On effectue la decompression pretraitement sur %s vers %s\n",outputCompressed,output);
          decompression_avec_pretraitement(outputCompressed,output);
        }
      }
    }
    
  }

  return 0;
}
