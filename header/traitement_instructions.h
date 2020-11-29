#ifndef TI
#define TI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#define TAILLE_MAX 50
#define END 999 /*correspond a la fin dans un tableau de int dans la fonction chaine*/


FILE *ouvertureFichier(char *chemin_fichier, char *mode);
void lireDonnees(char fichier_commande[], int memoire[]);
char *traitementChaine(char *chaine);
void argumentToTab(char *chaine, int *argument);

/*void lireDonnees(char fichier_commande[], char fichier_hexa[]);
void pushHexa(int hexa, FILE *fichier_arrive, int sw_lw);*/


#endif
