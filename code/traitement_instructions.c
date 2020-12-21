#include "../header/traitement_instructions.h"
#include "../header/conversion_hexa.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/exec_instructions.h"



char *traitementChaine(char *chaine){
    int i_chaine = 0, i_ie = 0, i_resultat = 0, i_temp = 0, nb_if = 0;
    int index_espace[TAILLE_MAX] = {0}; /*tableau qui repertorie tout les index dans la chaine des caractères : ' ', '#' (et la suite),*/
    char *resultat;
    int break_while = 0;

    
    resultat = chaine;

    if(chaine[0] == 'N' && chaine[1] == 'O' && chaine[2] == 'P' ){
        resultat[3] = '#';
        return resultat;
    }
    if(chaine[0] == 'S' && chaine[1] == 'Y' && chaine[2] == 'S' && chaine[3] == 'C' && chaine[4] == 'A' && chaine[5] == 'L' && chaine[6] == 'L'){
        resultat[7] = '#';
        return resultat;
    }

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
if(index_espace[0] == END) return resultat;
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

        else if(chaine[i_chaine-2] >= 'A' && chaine[i_chaine-2] <= 'Z' && chaine[i_chaine-1] == ' ' && chaine[i_chaine] != '$' && chaine[i_chaine] != '-'){ /*cas d'un premier argument positif qui n'est pas un registre*/
            while(chaine[i_chaine] >= '0' && chaine[i_chaine] <= '9'){
                argument[i_arg] = argument[i_arg]*10;
                argument[i_arg] += chaine[i_chaine] - '0';
                i_chaine++;
            }
            i_arg++;
        }

        else if(chaine[i_chaine-1] == '-'){/*cas d'un nombre negatif en argument */
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

/*void pushHexa(int hexa, FILE *fichier_arrive, int sw_lw){

    if(sw_lw == 0){

        if(hexa < 0xF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFFFF) fprintf(fichier_arrive, "0");
        if(hexa < 0xFFFFFFF) fprintf(fichier_arrive, "0");
    }

    fprintf(fichier_arrive, "%x\n", hexa);
}*/
