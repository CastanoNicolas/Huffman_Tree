int shell( FILE** fichier_entree, int argc, char *argv[], int *g, int *b, char output[]){
	
	int erreur = 0;
	int fichier_present=0;
	int custom_name=0;
	char nom_fichier[100];
	int i =1;

	while(i < argc && !erreur){
		if( *argv[i] == '-' ){
			// on regarde s'il y a un -g
			if(argv[i][1] == 'g'){
				if(*g ==1) erreur = 1;
				else *g=1;
			}
			// on regarde s'il y a un -b
			else if(argv[i][1] == 'b'){
				if(*b == 1) erreur = 2;
				else{
					*b=1;	
				} 
			}
			// on regarde s'il y a un -o
			else if(argv[i][1] == 'o'){
				if(custom_name ==1) erreur = 3;
				else {
					custom_name=1;
					if(i != (argc-1) && argv[i+1][0] != '-'){
						sprintf(output,"%s%c",argv[i+1],'\0');
						i++;
					}
					else
						erreur = 5;
				}
			}
		}
		else{
			if(fichier_present ==1){
				erreur =  4;
			}
			else{
				fichier_present = 1;
				sprintf(nom_fichier,"%s%c", argv[i],'\0');
			}
		}
		i++;
	}

	if( (*fichier_entree = fopen(nom_fichier,"r")) == NULL) *fichier_entree = stdin;
	if(custom_name == 0) sprintf(output,"image%c",'\0');
	return erreur;
}