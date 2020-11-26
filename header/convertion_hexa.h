#ifndef CE
#define CE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>


int testChaine(char chaine[], char mot[]);
int conversionHexa(char chaine[], int argument[]);
int rType(int rd, int rs, int rt, int sa, int function);
int iType(int op_code, int rt, int rs, int immediate);
int jType(int op_code, int target);

#endif