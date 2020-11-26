#include "../header/traitement_instructions.h"
#include "../header/convertion_hexa.h"


void lireDonnees(char fichier_commande[], char fichier_hexa[])
{
    char *init_chain = "";
    char chaine[TAILLE_MAX] = "";
    char *chaine_normalise = "";
    int hexa = 0;
    int argument[4];
    int sw_lw = 0;

    FILE *fichier_depart;
    FILE *fichier_arrive;

    fichier_depart = ouvertureFichier(fichier_commande, "r");
    fichier_arrive = ouvertureFichier(fichier_hexa, "w");

    while(fgets(chaine, TAILLE_MAX, fichier_depart) != NULL)
    {
        sw_lw = 0;
        hexa = 0;
        chaine[TAILLE_MAX] = *init_chain;

        /* Recuperation et traitement de l'instruction */
        chaine_normalise = traitementChaine(chaine); /*Normalise la chaine en enlevant tout les espaces inutiles*/

        /* Affichage console */
        printf("-------------------------------------\n");
        printf("%s\n", chaine_normalise);

        /* Conversion de l'instruction en hexadecimal */
        argumentToTab(chaine_normalise, argument); /*met les arguments de l'instruction dans le tableau argument */
        hexa = conversionHexa(chaine_normalise, argument); /*fonction qui produit le code hexa avec les arguments et la chaine normalisée*/

        /* Traitement des lignes de commentaires, des lignes vides et des instructions invalides (hexa = 0 sauf NOP) => pas d'ecriture dans le fichier hexa, retour au debut du while */
        if(chaine_normalise[0] == '#' || (chaine_normalise[0] != 'N' && hexa == 0)) continue;

        /* Affichage console */
        printf("%x\n", hexa);

        /* Ecriture dans le fichier hexa */
        if(testChaine(chaine_normalise, "LW ") || testChaine(chaine_normalise, "SW ")) sw_lw = 1; /* Resolution d'un bug d'ecriture avec ces deux instructions */
        pushHexa(hexa, fichier_arrive, sw_lw);

    }

    printf("-------------------------------------\n");
    fclose(fichier_depart);
    fclose(fichier_arrive);
}

char *traitementChaine(char *chaine){
    int i_chaine = 0, i_ie = 0, i_resultat = 0, i_temp = 0, nb_if = 0;
    int index_espace[TAILLE_MAX] = {0}; /*tableau qui repertorie tout les index dans la chaine des caractères : ' ', '#' (et la suite),*/
    char *resultat;
    int break_while = 0;

    resultat =  chaine;

    /*cette premiere boucle repertorie l'index des espaces inutile dans le tableau index_espace*/
    while(resultat[i_chaine] != '\0' && break_while == 0){ /*Boucle jusqu'a la fin de la chaine (fin des instructions) */
        break_while = 0;
        if(i_chaine >= 1){ /*condition pour ne pas tester chaine[-1]*/
            if(resultat[i_chaine] == ' ' && (chaine[i_chaine-1] < 'A' || chaine[i_chaine-1] > 'Z')) {
                index_espace[i_ie] = i_chaine;
                i_ie++;
            }
            else if (resultat[i_chaine] == '#'){
                index_espace[i_ie] = END;
                break_while = 1;
            }
        }

        else{
            if(resultat[i_chaine] == ' ' ||  resultat[i_chaine] == '\t'){
                index_espace[i_ie] = i_chaine;
                i_ie++;
            }
            else if (resultat[i_chaine] == '#'){
                index_espace[i_ie] = END;
                break_while = 1;
            }
        }
        index_espace[i_ie] = END;
        i_chaine++;
    }

    if(index_espace[0] == END) return resultat; /*si c'est un commentaire ou ligne vide renvoie {0}*/

    i_ie = 0;
    nb_if = 0;

    /*cette deuxieme boucle enleve les espaces inutiles graces au tableau index_espace*/
    while(index_espace[i_ie] != END ){

        if(index_espace[i_ie] ==  i_resultat){
            i_temp = index_espace[i_ie] - nb_if;

            while(resultat[i_temp] != '\0'){
                resultat[i_temp] = resultat[i_temp + 1];
                i_temp++;
            }
            nb_if++;
            i_ie++;
        }

        else{
            i_resultat++;
        }
    }
    return resultat;

}

void argumentToTab(char *chaine, int *argument){
    int i_chaine = 2;
    int i_arg = 0;
    argument[0] = 0;
    argument[1] = 0;
    argument[2] = 0;

    /*boucle qui rempli le tableau argument en fonction des differentes configuration*/
    while(chaine[i_chaine] != '\0'){
        if(chaine[i_chaine-1] == '$'){
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){/*cas d'un registre */
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            i_arg++;
        }

        else if(chaine[i_chaine-1] == ',' && chaine[i_chaine] != '$' && chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){/*cas d'un argument qui n'est pas un registe*/
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            i_arg++;
        }

        else if(chaine[i_chaine-2] >= 'A' && chaine[i_chaine-2] <= 'Z' && chaine[i_chaine-1] == ' ' && chaine[i_chaine] != '$'){ /*cas d'un premier argument qui n'est pas un registre*/
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            i_arg++;
        }

        else if(chaine[i_chaine-2] == ',' && chaine[i_chaine-1] == '-'){/*cas d'un nombre negatif en argument */
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            argument[i_arg] = -1 * argument[i_arg];    
            i_arg++;
        }

        else{
            i_chaine++;
        }
    }

    argument[i_arg] = '\0';
}

void pushHexa(int hexa, FILE *fichier_arrive, int sw_lw){

    if(sw_lw == 0){
        /*padding*/

        if(hexa < 0xF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFFFFF) fprintf(fichier_arrive, "0");
    }

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

