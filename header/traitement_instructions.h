#ifndef TI
#define TI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#define TAILLE_MAX 50
#define END 999 /*correspond a la fin dans un tableau de int dans la fonction chaine*/


void lireDonnees(char fichier_commande[], char fichier_hexa[]);

FILE *ouvertureFichier(char *chemin_fichier, char *mode);
char *traitementChaine(char *chaine);
int testChaine(char chaine[], char mot[]);
void pushHexa(int hexa, FILE *fichier_arrive, int sw_lw);
void argumentToTab(char *chaine, int *argument);
int testChaine(char chaine[], char mot[]);


#endif