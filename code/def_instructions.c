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

/*
int *j(int registre[], int hexa, int *PC)
{
  if(lireRegistre(registre, rs(hexa)) == lireRegistre(registre, rt(hexa)))
  {
    PC = (immediate(hexa) << 2) + ((unsigned int)PC & 4026531840);
  }
}


int *jal(int registre[], int hexa, int *PC)
{

}


int *jr(int registre[], int hexa, int *PC)
{

}
*/

void lui(int registre[], int hexa)
{
  ecritureRegistre(registre, rt(hexa), (immediate(hexa) << 16));
}

/*
void lw(int registre[], int hexa, int memoire[])
{

}


void mfhi(int registre[], int hexa)
{

}


void mflo(int registre[], int hexa)
{

}


void mult(int registre[], int hexa, int HiLo[])
{

}


void divi(int registre[], int hexa, int HiLo[])
{

}


void or(int registre[], int hexa)
{

}


void rotr(int registre[], int hexa)
{

}


void sll(int registre[], int hexa)
{

}


void slt(int registre[], int hexa)
{

}


void srl(int registre[], int hexa)
{

}


void sub(int registre[], int hexa)
{

}


void sw(int registre[], int hexa, int memoire[])
{

}


void xor(int registre[], int hexa)
{

}
*/
