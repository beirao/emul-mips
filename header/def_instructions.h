#ifndef DI
#define DI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "../header/exec_instructions.h"

#define immediate(hexa)  (short)masque(15,0,hexa) /* Le (short) permet de respecter le signe de la valeur dans le champs "immediate" */
#define rd(hexa)  masque(15,11,hexa)
#define rs(hexa)  masque(25,21,hexa)
#define rt(hexa)  masque(20,16,hexa)

void add(int registre[], int hexa);
void addi(int registre[], int hexa);
void and(int registre[], int hexa);
int *beq(int registre[], int hexa, int *PC);
int *bgtz(int registre[], int hexa, int *PC);
int *blez(int registre[], int hexa, int *PC);
int *bne(int registre[], int hexa, int *PC);
int *j(int registre[], int hexa, int *PC);
int *jal(int registre[], int hexa, int *PC);
int *jr(int registre[], int hexa, int *PC);
void lui(int registre[], int hexa);
void lw(int registre[], int hexa, int memoire[]);
void mfhi(int registre[], int hexa);
void mflo(int registre[], int hexa);
void mult(int registre[], int hexa, int HiLo[]);
void divi(int registre[], int hexa, int HiLo[]);
void or(int registre[], int hexa);
void rotr(int registre[], int hexa);
void sll(int registre[], int hexa);
void slt(int registre[], int hexa);
void srl(int registre[], int hexa);
void sub(int registre[], int hexa);
void sw(int registre[], int hexa, int memoire[]);
void xor(int registre[], int hexa);

#endif
