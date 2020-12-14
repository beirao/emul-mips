#include "../header/traitement_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/def_instructions.h"
#include "../header/exec_instructions.h"

void modeNonInteractif(char fichier_src[], char txt[], int memoire[], int registre[], int *PC, int HiLo[], int mode){
    strcat(fichier_src, txt);
    affichageRegistre(registre, HiLo, PC);

    char *init_chain = "";
    char chaine[TAILLE_MAX] = "";
    char *chaine_normalise = "";
    int hexa = 0;
    int argument[4];
    int index_memoire = 0;
    int option = 0;
    char continu[9];

    int type; 
    int * PCinitial;

    FILE *fichier_depart;
    fichier_depart = ouvertureFichier(fichier_src, "r");
    
    
    if(mode == 0){
        
        printf("=========================================================\n");
        printf("Conversion des instructions en hexadecimal :\n");

        while(fgets(chaine, TAILLE_MAX, fichier_depart) != NULL)
        {
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

            ecritureMemoire(memoire, index_memoire, hexa, option);
            index_memoire++;
        }
        
        memoire[index_memoire] = END; /*signifier la fin du fichier : utile dans exec_instructions.*/

        printf("=========================================================\n\n\n");
        fclose(fichier_depart);
        /*-------------------------*/
        
        PC = memoire;
        exec(registre, memoire, HiLo, PC);
            
        affichageMemoire(memoire);
        affichageRegistre(registre, HiLo, PC);
    }



    else if(mode == 1){ /*mode pas a pas*/
        printf("MODE PAS A PAS : Pour passer a l'instruction suivante appuyez sur n (pour next) puis ENTER.\n");
        printf("=========================================================\n");
        printf("Conversion des instructions en hexadecimal :\n");
        PC = memoire;

        while(fgets(chaine, TAILLE_MAX, fichier_depart) != NULL)
        {
            hexa = 0;
            chaine[TAILLE_MAX] = *init_chain;

            /* Recuperation et traitement de l'instruction */
            chaine_normalise = traitementChaine(chaine); /*Normalise la chaine en enlevant tout les espaces inutiles*/

            /*mode pas a pas*/
            if(mode == 1){
                scanf("%s", continu);
            }

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
            printf("-------------------------------------\n");

            ecritureMemoire(memoire, index_memoire, hexa, option);
            index_memoire++;

            PC = exec_pas(registre, memoire, HiLo, PC);

            printf("pc = %p\n", PC);
                    
            affichageMemoire(memoire);
            affichageRegistre(registre, HiLo, PC);
        }
        
        memoire[index_memoire] = END; /*signifier la fin du fichier : utile dans exec_instructions.*/

        fclose(fichier_depart);

    }
}


void modeInteractif(int memoire[], int registre[], int *PC, int HiLo[]){
    
}