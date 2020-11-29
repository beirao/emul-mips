#ifndef MM
#define MM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

void lireMemoire(int memoire[], int index_memoire);
void ecritureMemoire(int memoire[], int index_memoire, int valeur, int option);
void affichageMemoire(int memoire[]);

#endif