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

void lireDonnees(char fichier_commande[], char fichier_hexa[])
{
    /*int rd, rs, rt;
    char* com = "oui"; */
    char *init_chain = "";
    char chaine[TAILLE_MAX] = "";
    int hexa = 0;

    FILE *fichier_depart;
    FILE *fichier_arrive;
    
    fichier_depart = ouvertureFichier(fichier_commande, "r");
    fichier_arrive = ouvertureFichier(fichier_hexa, "w");

    while(!feof(fichier_depart))
    {
        
        chaine[TAILLE_MAX] = *init_chain;
        fgets(chaine, TAILLE_MAX, fichier_depart);
        printf("%s\n", chaine);

        
        /*ADD*/
        if(test_chaine(0, 3, chaine, "ADD ")){
            hexa += 32;
            hexa += (chaine[5]-'0') << 11;
            hexa += (chaine[11]-'0') << 16;
            hexa += (chaine[8]-'0') << 21;
        }
        /*ADDI*/
        else if(test_chaine(0, 3, chaine, "ADDI")){
            hexa += (chaine[11]-'0');
            hexa += (chaine[6]-'0') << 16;
            hexa += (chaine[9]-'0') << 21;
            hexa += 8 << 26;
        }

        else{
            printf("erreur");
        }

        push_hexa(hexa, fichier_arrive);
        hexa = 0;
    }
    
    

    fclose(fichier_depart);
    fclose(fichier_arrive);
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

void push_hexa(int hexa, FILE *fichier_arrive){

    /*padding*/
    if(hexa < 0xFFFFF) fprintf(fichier_arrive, "0");
    if(hexa < 0xFFFFFF) fprintf(fichier_arrive, "0");
    if(hexa < 0xFFFFFFF) fprintf(fichier_arrive, "0");

    fprintf(fichier_arrive, "%x\n", hexa);
}