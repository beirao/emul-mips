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
    printf("Conversion des instructions en code hexadecimal et ecriture en memoire :\n\n");

    while(fgets(chaine, TAILLE_MAX, fichier_depart) != NULL)
    {
        hexa = 0;

        /* Traitement de l'instruction */
        chaine_normalise = traitementChaine(chaine); /*Normalise la chaine en enlevant tout les espaces inutiles*/

        /* Empeche d'effectuer la suite du programme pour les lignes de commentaires et les lignes vides */
        if(chaine_normalise[0] != '#' && chaine_normalise[0] != '\n' && chaine_normalise[0] != '\r')
        {
              /* Affichage console */
          printf("-------------------------------------\n");
          printf("%s\n", chaine_normalise);

          /* Conversion de l'instruction en hexadecimal */
          argumentToTab(chaine_normalise, argument); /* Met les arguments de l'instruction dans le tableau argument */
          hexa = conversionHexa(chaine_normalise, argument); /* Fonction qui produit le code hexa avec les arguments et la chaine normalisee */

              /* Affichage console */
          printf("%x\n", hexa);
          printf("-------------------------------------\n");

          /* Ecriture en memoire du code hexa de l'instruction */
          ecritureMemoire(memoire, index_memoire, hexa, option);
          index_memoire++;
        }
    }
    printf("Fin du fichier\n\n");
    ecritureMemoire(memoire, index_memoire, END, option);
    affichageMemoire(memoire);
    affichageRegistre(registre, HiLo, PC);



    printf("\nExecution du programme :\n\n");

    while(*PC != END)
    {
      /* Mode pas a pas */
      if(mode == 1) fgets(continu, TAILLE_MAX, stdin);

          /* Affichage console */
      printf("Code hexadecimal de l'instruction executee : %x\n", *PC);

      /* Execution du programme */
      PC = exec(registre, memoire, HiLo, PC);

          /* Affichage console */
      affichageMemoire(memoire);
      affichageRegistre(registre, HiLo, PC);
    }
    printf("Fin du programme\n");
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
      if(lireMemoire(memoire, index_memoire, option) == 0)
      {
        /* Recuperation de l'instruction rentree par l'utilisateur */
        printf("Rentrez l'instruction = ");
        fgets(instruction, TAILLE_MAX, stdin);
        printf("\n");

        /* Empeche d'effectuer la suite du programme si on souhaite quitter le programme */
        if(strcmp(instruction, "exit\n") != 0 && strcmp(instruction, "EXIT\n") != 0)
        {
          /* Traitement de l'instruction */
          chaine_normalise = traitementChaine(instruction);

              /* Affichage console */
          printf("-------------------------------------\n");
          printf("%s\n", chaine_normalise);

          /* Conversion de l'instruction en hexadecimal */
          argumentToTab(chaine_normalise, argument); /* Met les arguments de l'instruction dans le tableau argument */
          hexa = conversionHexa(chaine_normalise, argument); /* Fonction qui produit le code hexa avec les arguments et la chaine normalisee */

              /* Affichage console */
          printf("%x\n", hexa);
          printf("-------------------------------------\n");


          /* Ecriture en memoire du code hexa de l'instruction */
          ecritureMemoire(memoire, index_memoire, hexa, option);
        }
      }

      else
      {
            /* Affichage console */
        printf("Code hexadecimal de l'instruction executee : %x\n", *PC);
      }

      /* Execution du programme */
      PC = exec(registre, memoire, HiLo, PC);
      index_memoire = (PC - memoire);

          /* Affichage console */
      affichageMemoire(memoire);
      affichageRegistre(registre, HiLo, PC);
    }
}
