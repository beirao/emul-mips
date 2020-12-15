#include "../header/memoire.h"



int lireMemoire(int memoire[], int index_memoire, int option){
    if(option == 0 && index_memoire < SEPARATION && index_memoire >= 0){
        return memoire[index_memoire];
    }
    else if(option == 1 && index_memoire+SEPARATION >= SEPARATION && index_memoire+SEPARATION < TAILLE_MEMOIRE){
        return memoire[index_memoire+SEPARATION];
    }
    else{
        printf("ERREUR : lecture memoire impossible (aucune adresse ne correspond à l'index)\n");
        return 0;
    }
}


void ecritureMemoire(int memoire[], int index_memoire, int valeur, int option){
    /* L'option 0 correspond a la partie de la memoire dediee aux instructions */
    if(option == 0 && index_memoire < SEPARATION && index_memoire >= 0){
        memoire[index_memoire] = valeur;
        if(index_memoire == SEPARATION-1)
        {
          printf("WARNING : Memoire instruction pleine, desormais la memoire va s'ecraser au fur et à mesure (augmentez la TAILLE_MEMOIRE et SEPARATION pour ecrire plus d'instructions sans effacer les précédentes)\n");
        }
    }

    else if(option == 0 && index_memoire >= SEPARATION){
        memoire[index_memoire%SEPARATION] = valeur;
        if(index_memoire == SEPARATION)
        {
          printf("WARNING : Overflow memoire instruction, la memoire s'ecrase au fur et à mesure\n");
        }
    }

    /* L'option 1 correspond a la partie de la memoire dediee a l'execution des commandes SW et LW */
    else if(option == 1 && index_memoire+SEPARATION >= SEPARATION && index_memoire+SEPARATION < TAILLE_MEMOIRE){
        memoire[index_memoire + SEPARATION] = valeur;  /* On fait commencer l'ecriture en mémoire par les instructions LW et SW à l'adresse mémoire 100 au minimum */
    }

    else if(option == 1 && index_memoire+SEPARATION >= TAILLE_MEMOIRE){
        printf("ERREUR : Overflow memoire (memoire dediee a SW et LW trop petite, aucune case ne correspond à l'index %d)\n", index_memoire+SEPARATION);
    }

    else{
        printf("ERREUR : ecriture memoire impossible (aucune adresse ne correspond à l'index)\n");
    }
}

/* Nous avons décidé d'afficher la mémoire sur plusieures lignes de 16 éléments chacune, elle se lit donc de gauche à droite et de haut en bas */
void affichageMemoire(int memoire[]){
    int i;
    printf("=========================================================\n");
    printf("Memoire : \n");
    for ( i = 0; i < TAILLE_MEMOIRE ; i++){
        printf("%x ", memoire[i]);
        if(i%16 == 15 ) printf("\n");
    }
    printf("=========================================================\n\n");
}
