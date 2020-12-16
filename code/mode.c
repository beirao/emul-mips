#include "../header/traitement_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/def_instructions.h"
#include "../header/exec_instructions.h"
#include "../header/conversion_hexa.h"
#include "../header/mode.h"

void modeNonInteractif(char fichier_src[], const char txt[], int memoire[], int registre[], int *PC, int HiLo[], int mode){
    char chaine[TAILLE_MAX];
    char *chaine_normalise;
    int hexa = 0;
    int argument[4];
    int index_memoire = 0;
    int option = 0;

    char continu[TAILLE_MAX] = "";
    FILE *fichier_depart;

    strcat(fichier_src, txt);
    fichier_depart = ouvertureFichier(fichier_src, "r");
    PC = memoire;


    if(mode == 1)        printf("\nMODE PAS A PAS : Pour passer a l'instruction suivante appuyez sur ENTER.\n\n");
    else if(mode == 0)   printf("\nMODE NON INTERACTIF\n\n");

    printf("=======================================================================\n");
    printf("Execution du programme :\n\n");

    while(fgets(chaine, TAILLE_MAX, fichier_depart) != NULL)
    {
        hexa = 0;
    
        /* Traitement de l'instruction */
        chaine_normalise = traitementChaine(chaine); /*Normalise la chaine en enlevant tout les espaces inutiles*/

        /* Conversion de l'instruction en hexadecimal */
        argumentToTab(chaine_normalise, argument); /* Met les arguments de l'instruction dans le tableau argument */
        hexa = conversionHexa(chaine_normalise, argument); /* Fonction qui produit le code hexa avec les arguments et la chaine normalisee */

        /* Traitement des lignes de commentaires, des lignes vides et des instructions invalides (hexa = 0 sauf NOP) => pas d'ecriture dans le fichier hexa, retour au debut du while */
        if(chaine_normalise[0] == '#') continue;



        /* Mode pas a pas */
        if(mode == 1){
            fgets(continu, TAILLE_MAX, stdin);
        }

        /* Execution programme */
        ecritureMemoire(memoire, index_memoire, hexa, option);  
        PC = exec(registre, memoire, HiLo, PC);
        index_memoire++;



        /* Affichage console */
        printf("-------------------------------------\n");
        printf("%s\n", chaine_normalise);
        printf("%x\n", hexa);
        printf("-------------------------------------\n");
        affichageMemoire(memoire);
        affichageRegistre(registre, HiLo, PC);
    }
    printf("END FILE\n");
    printf("=======================================================================\n\n\n");
    fclose(fichier_depart);
}



void modeInteractif(int memoire[], int registre[], int *PC, int HiLo[]){
    char instruction[TAILLE_MAX];
    char *chaine_normalise;
    int hexa = 0;
    int argument[4];
    int index_memoire = 0;
    int option = 0;

    PC = memoire;

    printf("\nMODE INTERACTIF\n\n\n");

    while(strcmp(instruction, "exit\n") && strcmp(instruction, "EXIT\n"))
    {   
        /* Recuperation de l'instruction rentree par l'utilisateur */
        printf("Rentrez l'instruction = ");
        fgets(instruction, TAILLE_MAX, stdin);
        printf("\n");

        /* Empeche d'effectuer la suite de la boucle si on souhaite quitter le programme */
        if(strcmp(instruction, "exit\n") == 0 || strcmp(instruction, "EXIT\n") == 0) continue;


        
        /* Traitement de l'instruction */
        chaine_normalise = traitementChaine(instruction);

        /* Conversion de l'instruction en hexadecimal */
        argumentToTab(chaine_normalise, argument); /* Met les arguments de l'instruction dans le tableau argument */
        hexa = conversionHexa(chaine_normalise, argument); /* Fonction qui produit le code hexa avec les arguments et la chaine normalisee */

        /* Execution de l'instruction */
        ecritureMemoire(memoire, index_memoire, hexa, option);
        PC = exec(registre, memoire, HiLo, PC);
        index_memoire++;



        /* Affichage console */
        printf("-------------------------------------\n");
        printf("%s\n", chaine_normalise);
        printf("%x\n", hexa);
        printf("-------------------------------------\n");
        affichageMemoire(memoire);
        affichageRegistre(registre, HiLo, PC);
    }
}
