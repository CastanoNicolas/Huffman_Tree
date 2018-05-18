#ifndef CLI
#define cli
int shell(FILE** fichier_entree,char* input, int* source,int argc, char const *argv[], int *c, int *d,int* p, int* nbParam,char output[]);
void affichage_erreur(int erreur);
#endif