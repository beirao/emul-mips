#include "../header/traitement_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/def_instructions.h"
#include "../header/exec_instructions.h"
#include "../header/conversion_hexa.h"

void modeNonInteractif(char fichier_src[], const char txt[], int memoire[], int registre[], int *PC, int HiLo[], int mode){
    char chaine[TAILLE_MAX];
    char *chaine_normalise;
    int hexa = 0;
    int argument[4];
    int index_memoire = 0;
    int option = 0;
    char continu[9];
    FILE *fichier_depart;

    strcat(fichier_src, txt);
    affichageRegistre(registre, HiLo, PC);
    fichier_depart = ouvertureFichier(fichier_src, "r");
    PC = memoire;


    if(mode == 1)        printf("MODE PAS A PAS : Pour passer a l'instruction suivante appuyez sur n (pour next) puis ENTER.\n");
    else if(mode == 0)   printf("MODE NON INTERACTIF\n");

    printf("=========================================================\n");
    printf("Conversion des instructions en hexadecimal :\n");

    while(fgets(chaine, TAILLE_MAX, fichier_depart) != NULL)
    {
        hexa = 0;
    
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

        ecritureMemoire(memoire, index_memoire, hexa, option);
        index_memoire++;
        printf("-------------------------------------\n");

        if(mode == 1){
            PC = exec(registre, memoire, HiLo, PC);
            affichageMemoire(memoire);
            affichageRegistre(registre, HiLo, PC);
        }        
    }
    
    memoire[index_memoire] = END; /*signifier la fin du fichier : utile dans exec_instructions.*/

    printf("=========================================================\n\n\n");
    fclose(fichier_depart);

    if(mode == 0){
        while (*PC != END){
            PC = exec(registre, memoire, HiLo, PC);  
        }
            
        affichageMemoire(memoire);
        affichageRegistre(registre, HiLo, PC);
    }
}


void modeInteractif(int memoire[], int registre[], int *PC, int HiLo[]){
    char instruction[TAILLE_MAX];
    char *chaine_normalise;
    int hexa = 0;
    int argument[4];
    int index_memoire = 0;
    int option = 0;

    PC = memoire;

    printf("MODE INTERACTIF\n");

    while(strcmp(instruction, "exit\n"))
    {   
        printf("strcomp = %d\n",strcmp(instruction, "exit"));
        printf("rentrez instruction = ");
        fgets(instruction, TAILLE_MAX, stdin);
        printf("\n");
        
        chaine_normalise = traitementChaine(instruction);

        printf("-------------------------------------\n");
        printf("%s\n", chaine_normalise);

        /* Conversion de l'instruction en hexadecimal */
        argumentToTab(chaine_normalise, argument); /*met les arguments de l'instruction dans le tableau argument */
        hexa = conversionHexa(chaine_normalise, argument); /*fonction qui produit le code hexa avec les arguments et la chaine normalisée*/

        /* Affichage console */
        printf("%x\n", hexa);

        ecritureMemoire(memoire, index_memoire, hexa, option);
        index_memoire++;
        printf("-------------------------------------\n");

        PC = exec(registre, memoire, HiLo, PC);
        affichageMemoire(memoire);
        affichageRegistre(registre, HiLo, PC);
    }

    memoire[index_memoire] = END; /*signifier la fin du fichier : utile dans exec_instructions.*/

}