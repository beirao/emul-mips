#ifndef R
#define R

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

int lireRegistre(int registre[], int HiLo[], int *PC , int id_registre);
void ecritureRegistre(int registre[], int HiLo[], int *PC, int id_registre, int valeur);
void affichageRegistre(int registre[], int HiLo[], int *PC);

#endif