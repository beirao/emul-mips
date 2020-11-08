#ifndef __EXERCICE_H__
#define __EXERCICE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAILLE_MAX 50

FILE *ouvertureFichier(char *chemin_fichier, char *mode);	
void lireDonnees(char fichier_commande[], char fichier_hexa[]);
int testChaine(char chaine[], char mot[]);
void pushHexa(int hexa, FILE *fichier_arrive);
void argumentToTab(char *chaine, int *argument);


#endif