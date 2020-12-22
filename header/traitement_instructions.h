#ifndef TI
#define TI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#define TAILLE_MAX 200
#define END 999


FILE *ouvertureFichier(char *chemin_fichier, char *mode);
char *traitementChaine(char *chaine);
void argumentToTab(char *chaine, int *argument);


#endif
