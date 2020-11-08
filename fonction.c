#include "fonction.h"




void lireDonnees(char fichier_commande[], char fichier_hexa[])
{
    /*int rd, rs, rt;
    char* com = "oui"; */
    char *init_chain = ""; 
    char chaine[TAILLE_MAX] = "";
    int hexa = 0;
    int argument[4]; 

    FILE *fichier_depart;
    FILE *fichier_arrive;
    
    fichier_depart = ouvertureFichier(fichier_commande, "r");
    fichier_arrive = ouvertureFichier(fichier_hexa, "w");

    while(!feof(fichier_depart))
    {
        
        chaine[TAILLE_MAX] = *init_chain;
        
        fgets(chaine, TAILLE_MAX, fichier_depart);
        

        printf("%s\n", chaine);
        argumentToTab(chaine, argument);

        /*ADD*/
        if(testChaine(chaine, "ADD ")){
            hexa += 32;
            hexa += argument[0] << 11;
            hexa += argument[2] << 16;
            hexa += argument[1] << 21;
        }
        /*ADDI*/
        else if(testChaine(chaine, "ADDI ")){
            hexa += argument[2];
            hexa += argument[0] << 16;
            hexa += argument[1] << 21;
            hexa += 8 << 26;
        }
        /*AND*/
        else if(testChaine(chaine, "AND ")){
            hexa += 9;
            hexa += argument[0] << 11;
            hexa += argument[2] << 16;
            hexa += argument[1] << 21;
        }

        else{
            printf("erreur\n");
        }

        pushHexa(hexa, fichier_arrive);
        hexa = 0;
    }
    
    

    fclose(fichier_depart);
    fclose(fichier_arrive);
}

void argumentToTab(char *chaine, int *argument){
    int i_chaine = 2;
    int i_arg = 0;
    argument[0] = 0;
    argument[1] = 0;
    argument[2] = 0;

    while(chaine[i_chaine] != '\0'){
        if(chaine[i_chaine-1] == '$'){
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            i_arg++;
        }

        else if(chaine[i_chaine-1] == ',' && chaine[i_chaine] != '$'){
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            i_arg++;
        }

        else{
            i_chaine++;
        }
    }

    argument[i_arg] = '\0';
    /*printf("%d ", argument[0]);
    printf("%d ", argument[1]);
    printf("%d ", argument[2]);
    printf("%d \n", argument[3]);*/
}



void pushHexa(int hexa, FILE *fichier_arrive){

    /*padding*/
    if(hexa < 0xFFFFF) fprintf(fichier_arrive, "0");
    if(hexa < 0xFFFFFF) fprintf(fichier_arrive, "0");
    if(hexa < 0xFFFFFFF) fprintf(fichier_arrive, "0");

    fprintf(fichier_arrive, "%x\n", hexa);
}

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


int testChaine(char chaine[], char mot[]){
    long unsigned int i;

    for(i = 0; i <= (strlen(mot)-1); i++){
        if(chaine[i] != mot[i])  return 0;
    }
    return 1;
}