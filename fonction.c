#include "fonction.h"


FILE *ouvertureFichier(char *chemin_fichier, char *mode)
{
    FILE *fichier;
    fichier = NULL;
    fichier = fopen(chemin_fichier, mode);

    if (fichier == NULL)
    {
    printf("ERROR : le fichier n'a pas pu être ouvert\n");
    exit(0);
    }
    return fichier;
}

void lireDonnees(char fichier_commande[])
{
    /*int rd, rs, rt;
    char* com = "oui"; */
    char chaine[TAILLE_MAX] = "";
    char binaire[31] = "";

    FILE *fichier;
    fichier = ouvertureFichier(fichier_commande, "r");

    while(!feof(fichier))
    {
        fgets(chaine, TAILLE_MAX, fichier);
        printf("%s", chaine);

        /*ADDI*/
        if(test_chaine(0, 3, chaine, "ADDI")){
            
            
        }
        
        
    }

    

    fclose(fichier);
}

int test_chaine(int depart, int arrive, char chaine[], char mot[]){
    int i;

    for(i = depart; i <= arrive; i++){
        if(chaine[i] != mot[i-depart]){
            return 0;
        }
    }
    return 1;
}

int remplir_chaine(char chaine[], char mot[]){

}
  

