#include <stdlib.h>
#include <stdio.h>



char* read_compressed_huffman_code(char* src_file_name) {
  FILE* f = fopen(src_file_name, "r");

  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier compressé.\n");
    exit(1);
  }

  char* tab = malloc(sizeof(char) * 256);

  for (int i = 0; i < 256; i++) {
    fscanf(f, "%c", &tab[i]);
  }

  return tab;
}

void read_and_store_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree){

	FILE* fsrc = fopen(src_file_name,"r");
	FILE* fdst = fopen(dst_file_name,"w");

	char c, c_ascii;
	canonical_tree* t=tree;
	int i =0;
	do(){
		t=tree;
		fscanf(fsrc,"%c",&c);

		while(t != NULL && !feof(fsrc) && t->caractere == -1){
			if( (c & 0x1<< i) == 0 )
				t=t->fils_gauche;
			else 
				t=t->fils_droite;
			i++;
			if(i == 8){
				i=0;
				fscanf(fsrc,"%c",&c);				
			} 
		}
		
		if(t == NULL)
			printf("Erreur lors du decodage\n");
		
		if(feof(fsrc) && t->caractere == -1){
			printf("Erreur lors de la lecture du dernier symbole\n");
			exit(1);
		}
		else if (feof(fsrc) && t->caractere !=-1)
			printf("Pas de fichiers résiduels\n");


		c_ascii = (t->caractere) & 0xFF;
		ecrire_octet(fdst, c_ascii);

	}while(!feof(fsrc));

	// il faut tester les derniers bits
	while(i < 8){
		t=tree;
		while(t->caractere == -1 && i<8 ){
			if( (c & 0x1<< i) == 0 )
				t=t->fils_gauche;
			else 
				t=t->fils_droite;
			i++;
		}
		if(t->caractere != -1){
			c_ascii = (t->caractere) & 0xFF;
			ecrire_octet(fdst, c_ascii);
		}

	}

	close(fsrc);
	close(fdst);
	return;
}
