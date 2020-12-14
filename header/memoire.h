#ifndef MM
#define MM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define TAILLE_MEMOIRE 128 /* Correpsond a la taille totale de la memoire */
#define SEPARATION 100 /* Correspond a l'adresse memoire a partir de laquelle les intructions LW et SW peuvent s'effectuer, l'espace memoire precedent correspond a l'espace memoire des instructions */

int lireMemoire(int memoire[], int index_memoire, int option);
void ecritureMemoire(int memoire[], int index_memoire, int valeur, int option);
void affichageMemoire(int memoire[]);

#endif
