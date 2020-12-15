#ifndef R
#define R

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define TAILLE_REGISTRE 32
#define TAILLE_HILO 2


int lireRegistre(int reg[], int id_registre);
void ecritureRegistre(int reg[], int id_registre, int valeur);
void affichageRegistre(int registre[], int HiLo[], int *PC);

#endif