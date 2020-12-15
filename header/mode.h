#ifndef M
#define M

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

void modeInteractif(int memoire[], int registre[], int *PC, int HiLo[]);
void modeNonInteractif(char fichier_src[], const char *txt, int memoire[], int registre[], int *PC, int HiLo[], int mode);

#endif