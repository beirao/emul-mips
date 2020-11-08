#ifndef __EXERCICE_H__
#define __EXERCICE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAILLE_MAX 50

FILE *ouvertureFichier(char *chemin_fichier, char *mode);	
void lireDonnees(char fichier_commande[], char fichier_hexa[]);
int test_chaine(int arrive, char chaine[], char mot[]);
void push_hexa(int hexa, FILE *fichier_arrive);
void argument_to_tab(char *chaine, int *argument);


#endif