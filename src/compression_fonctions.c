/** COMPRESSION **/

//Structure arbre//
typedef struct n { 
	float poid ; 
  int caractere ;
	noeud* fils_gauche ; 
	noeud* fils_droite ; 
	noeud* pere ; 
} noeud ;




//1C prétraitement optionel des données : MTF
/**
 * A faire une fois la suite réalisée
 **/


//2C prétraitement optionel des données : RLE
/**
 * A faire une fois la suite réalisée
 **/



//3C analyse statique : calcul + tri des fréquences de symboles
/**
 * prend un nom de fichier en paramètre, l'ouvre en lecture.
 *  alloue (malloc) un tableau "frequences" de taille 256 -- si et seulement si on considere que tous les char ascii sont utilisés.
 * Sinon  on fait un tableau a deux dimensions avec le caractere ascii, suivit de sa frequence --
 * incrémente frequences[caractère_lu] a chaque caractere lu.
 * ferme le fichier précedement ouvert.
 * retourne le tableau frequence.
 */
int* frequencies_of_occurences(char* file_name, int symbole_number)
{
// raph
	FILE* fichier = NULL;
	    int * tab = malloc(TAILLE_TAB*sizeof(int)); // Malloc des 256 cases du tableau en mémoire
	    for (int i=0; i<TAILLE_TAB; i++) // Initialisation des cases du tab à 0
	    {
	    	tab[i]=0;
	    }
	    fichier = fopen(file_name, "r"); // ouverture en lecture
	    if (fichier != NULL)
	    {	
	        do
	        {
	            char lecture = lire_symbole(fichier); // Appel fonction
	            tab[lecture]++;	// Compter les occurences
	        } while (feof(fichier)==0); // tant qu'on est pas à la fin du fichier
		    
		    fclose(fichier); // Fermeture du fichier
		    return tab;
	    }
	    else
	    {
	    	printf("Erreur de fichier\n");
	    }
}




//4C détermination des longueurs des codes des symboles
//  -- Il faut préalablement crere la structure de donnée huffman_tree
/**
 * Prend en entrée un tableau de frequences, tableaux donnée par la fonction frequencies_of_occurences
 * construit et store dans une structure de donnée (malloc) l'arbre résultat
 **/
huffman_tree* build_huffman_tree(int* frequencies);
//quentin





//5C génération de arbre/codes canoniques des symboles
//  -- Il faut préalablement creer la structure de donnée canonical_tree
/**
 * Prend un arbre de Huffman en entrée (donné par la fonction build_huffman_tree)
 * Construit l'arbre canonique correspondant.
 * Alloue (malloc) et store dans une structure canonical_tree l'abre canonique créé
 * retourne cet arbre canonique
 **/
canonical_tree* normal_tree_to_canonical_tree(huffman* tree);
// Ergi





//6C écriture de table des longueurs (après compression RLEoptionnelle)
// -- Il faut préalablement choisir le format d'écriture des longueur
/**
 * Ecrit dans le fichier dst_file_name la table des longueurs 
 * de l'arbre canonique donné en paramètre (donné par la fonction normal_tree_to_canonical_tree)
 * Le fichier est ouvert en ecriture avec effacement préalable du contenu
 * Le fichier doit etre ouvert et fermé dans la fonction
 * le format d'écriture doit etre reflechi (potentiellement avec le groupe)
 **/
void write_compressed_huffman_code(char* dst_file_name,canonical_tree* tree);
// Ariane



//7C transcodage + écriture, symbole par symbole.
// -- Il faut absolument encapsuler le code pour qu'il n'y ai pas de traitement bas niveau
// ex: - lire_symbole qui va lrie un caractere ascii dans le fichier source
//	   - encoder_symbole qui va chercher la correspondance dans l'arbe canonique d'un symbole ( le resultat peut etre plus court qu'un octet)
//	   - ecrire_octet qui ecrit un octet de donnée
// Il faut donc faire  attention a ne pas ecrire les symbole un par un, puisqu'il peut y avoir deux symbole dans un octet
// Il n'y pas de moyen en C d'ecrire bit par bit
/**
 * Ecrit dans le fichier dst_file_name les caractère lu dans le fichier src_file_name
 * Les caractère lus sont encodé selon le code donné par l'arbre canonique "tree"
 * Tout les caractère lu et encodé sont directement écrit dans le fichier de destination sans caractère de séparation
 * Le fichier de destination est ouvert en "écriture a la suite"
 * le fichier source est ouvert en lecture seule.
 * Tout les fichiers sont fermé a la fin de la fonction.
 **/
void write_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree);
//Nicolas et Juliette



/** DECOMPRESSION **/

// 1D lecture (et décompression éventuelle) de la table des longueurs de codes.
/**
 * Le fichier compressé est ouvert en lecture seule.
 * Lit la table des longueurs dans le fichier.
 * Alloue (malloc) et store dans une structure length_table la table lue
 * Le fichier est fermé a la fin du traitement.
 **/
length_table* read_compressed_huffman_code(char* src_file_name);




// 2D reconstruction des codes et de l'arbre canoniques
/**
 * Reconstruit l'arbre de Huffman canonique a partar de la table des longueurs 
 * alloue (malloc) et store dans la structure de donnée canonical tree le resultat de la reconstruction 
 **/
canonical_tree* length_table_to_canonical_tree(length_table* table);




// 3D. lecture bit à bit et décodage des symboles :
// -- Il faut absolument encapsuler le code pour qu'il n'y ai pas de traitement bas niveau
// ex: - lecture_et_decodage_symbole qui lit un seul symbole et donne son equivalent ascii (Il faut faire attention si elle lit plus qu'un symbole, a garder en mémoire les bits en plus)
//
/**
 * Fonction qui lit un fichier compressé octet par octet et le decode.
 * Le fichier source est decodé et stocké immédiatement dans le fichier destination.
 **/
/**
 *	Indication du prof:
 *		départ à la racine de larbre
 *		sur chaque bit lu, transition d un niveau dans larbre
 *		arrivée sur feuille : émission symbole + retour à la racine
 **/
void read_and_store_compressed_file(char* src_file_name, char* dst_file_name, canonical_tree* tree);






//4D. opération inverse de prétraitement optionnel : RLE
/**
 * A faire une fois le 1C réalisé




 **/


//5D. opération inverse de prétraitement optionnel : MTF
/**
 * A faire une fois le 2C réalisé
 **/


main.c 
	huffman.h 								-> contient les structure de données utilisées

	compression.c 							-> contient la fonction qui comrpesse un fichier
		compression_fonction.c 				-> contient les fonctions de compression detaillées dans  le fichier plan
			utilitaire_compression.c  		-> contient les fonctions bas niveau utilisées par decomrpession_fonction.c
      

	decompression.c 						-> contient la fonction qui decompresse un fichier
		decompression_fonction.c 			-> contient les fonctions de decompression detaillées dans  le fichier plan
			utilitaire_decompression.c 		-> contient les fonctions bas niveau utilisées par decomrpession_fonction.c