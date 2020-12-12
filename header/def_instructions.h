#ifndef DI
#define DI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "../header/exec_instructions.h"

#define rs(hexa)  masque(25,21,hexa)
#define rt(hexa)  masque(20,16,hexa)
#define rd(hexa)  masque(15,11,hexa)



void add(int registre[], int hexa);
void addi(int registre[], int hexa);
void and(int registre[], int hexa);
void beq(int registre[], int hexa, int *PC);
void bgtz(int registre[], int hexa, int *PC);
void blez(int registre[], int hexa, int *PC);
void bne(int registre[], int hexa, int *PC);
void j(int registre[], int hexa, int *PC);
void jal(int registre[], int hexa, int *PC);
void jr(int registre[], int hexa, int *PC);
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
