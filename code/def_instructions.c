#include "../header/def_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"

void add(int registre[], int hexa)
{
  long add = 0;
  add = (lireRegistre(registre, rs(hexa)) + lireRegistre(registre, rt(hexa)));

  if(add >= pow(2,31)) printf("IntegerOverflow pour ADD\n");
  else ecritureRegistre(registre, rd(hexa), add);
}


void addi(int registre[], int hexa)
{
  long add = 0;
  add = (lireRegistre(registre, rs(hexa)) + immediate(hexa));

  if(add >= pow(2,31)) printf("IntegerOverflow pour ADDI\n");
  else ecritureRegistre(registre, rt(hexa), add);
}


void and(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rs(hexa)) & lireRegistre(registre, rt(hexa))));
}


int *beq(int registre[], int hexa, int *PC)
{
  if(lireRegistre(registre, rs(hexa)) == lireRegistre(registre, rt(hexa)))
  {
    PC += immediate(hexa);
  }
  return PC;
}


int *bgtz(int registre[], int hexa, int *PC)
{
  if(lireRegistre(registre, rs(hexa)) > 0)
  {
    PC += immediate(hexa);
  }
  return PC;
}


int *blez(int registre[], int hexa, int *PC)
{
  if(lireRegistre(registre, rs(hexa)) <= 0)
  {
    PC += immediate(hexa);
  }
  return PC;
}


int *bne(int registre[], int hexa, int *PC)
{
  if(lireRegistre(registre, rs(hexa)) != lireRegistre(registre, rt(hexa)))
  {
    PC += immediate(hexa);
  }
  return PC;
}


int *j(int registre[], int hexa, int *PC)
{
  if(lireRegistre(registre, rs(hexa)) == lireRegistre(registre, rt(hexa)))
  {
    PC = (immediate(hexa) << 2) + ((unsigned int)PC & 4026531840);
  }
  return 0;
}


int *jal(int registre[], int hexa, int *PC)
{
  printf("lol");
  return 0;
}


int *jr(int registre[], int hexa, int *PC)
{
  printf("lol");
  return 0;
}


void lui(int registre[], int hexa)
{
  ecritureRegistre(registre, rt(hexa), (immediate(hexa) << 16));
}


void lw(int registre[], int hexa, int memoire[])
{
  printf("lol");
}


void mfhi(int registre[], int hexa)
{
  printf("lol");
}


void mflo(int registre[], int hexa)
{
  printf("lol");
}


void mult(int registre[], int hexa, int HiLo[])
{
  printf("lol");
}


void divi(int registre[], int hexa, int HiLo[])
{
  printf("lol");
}


void or(int registre[], int hexa)
{
  printf("lol");
}


void rotr(int registre[], int hexa)
{
  printf("lol");
}


void sll(int registre[], int hexa)
{
  printf("lol");
}


void slt(int registre[], int hexa)
{
  printf("lol");
}


void srl(int registre[], int hexa)
{
  printf("lol");
}


void sub(int registre[], int hexa)
{
  printf("lol");
}


void sw(int registre[], int hexa, int memoire[])
{
  printf("lol");
}


void xor(int registre[], int hexa)
{
  printf("lol");
}

