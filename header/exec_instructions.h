#ifndef EI
#define EI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

void exec(int registre[], int memoire[], int HiLo[], int *PC);
int  *exec_pas(int registre[], int memoire[], int HiLo[], int *PC);
void appelR(int registre[], int hexa, int HiLo[], int *PC);
void appelI(int registre[], int memoire[], int *PC, int hexa);
void appelJ(int registre[], int hexa, int *PC);
int masque(int bit_haut, int bit_bas, int hexa);


#endif
