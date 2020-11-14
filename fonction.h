#ifndef __EXERCICE_H__
#define __EXERCICE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define TAILLE_MAX 50
#define END 999

FILE *ouvertureFichier(char *chemin_fichier, char *mode);
void lireDonnees(char fichier_commande[], char fichier_hexa[]);
char *traitementChaine(char *chaine);
int testChaine(char chaine[], char mot[]);
void pushHexa(int hexa, FILE *fichier_arrive, int sw_lw);
void argumentToTab(char *chaine, int *argument);
int conversionHexa(char chaine[], int argument[]);
int rType(int rd, int rs, int rt, int sa, int function);
int iType(int op_code, int rt, int rs, int immediate);
int jType(int op_code, int target);

#endif
