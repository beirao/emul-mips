#ifndef EI
#define EI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

int *exec(int registre[], int memoire[], int HiLo[], int *PC);
int *appelR(int registre[], int hexa, int HiLo[], int *PC);
int *appelI(int registre[], int memoire[], int *PC, int hexa);
int *appelJ(int registre[], int memoire[], int *PC, int hexa);
int masque(int bit_haut, int bit_bas, int hexa);


#endif
