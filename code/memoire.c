#include "../header/memoire.h"



int lireMemoire(int memoire[], int index_memoire){
    return memoire[index_memoire];
}

void ecritureMemoire(int memoire[], int index_memoire, int valeur, int option){
    if(option == 0){
        memoire[index_memoire] = valeur;
    }
}

void affichageMemoire(int memoire[]){
    int i;
    printf("-------------------------------------\n");
    printf("Memoire : \n");
    for ( i = 0; i < TAILLE_MEMOIRE ; i++){
        printf("%x ", memoire[i]);
        if(i%16 == 15 ) printf("\n");
    }
    printf("-------------------------------------\n");
}