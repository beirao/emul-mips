#include "../header/def_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"

void add(int registre[], int hexa)
{
  long add = 0;
  add = (lireRegistre(registre, rs(hexa)) + lireRegistre(registre, rt(hexa)));

  if((lireRegistre(registre, rs(hexa)) >= 0) && (lireRegistre(registre, rt(hexa)) >= 0) && (add < 0)) printf("IntegerOverflow pour ADD\n");
  else ecritureRegistre(registre, rd(hexa), add);
}


void addi(int registre[], int hexa)
{
  long add = 0;
  add = (lireRegistre(registre, rs(hexa)) + immediate(hexa));

  if((lireRegistre(registre, rs(hexa)) >= 0) && (lireRegistre(registre, rt(hexa)) >= 0) && (add < 0)) printf("IntegerOverflow pour ADDI\n");
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
*/

void mfhi(int registre[], int hexa, int HiLo[])
{
  ecritureRegistre(registre, rd(hexa), lireRegistre(HiLo, 32));
}


void mflo(int registre[], int hexa, int HiLo[])
{
  ecritureRegistre(registre, rd(hexa), lireRegistre(HiLo, 33));
}


void mult(int registre[], int hexa, int HiLo[])
{
  long op1 = 0, op2 = 0;
  op1 = lireRegistre(registre, rs(hexa));
  op2 = lireRegistre(registre, rt(hexa));

  ecritureRegistre(HiLo, 32, (op1*op2) >> 32);
  ecritureRegistre(HiLo, 33, (op1*op2) & 0x00000000FFFFFFFF);
}


void divi(int registre[], int hexa, int HiLo[])
{
  int op1 = 0, op2 = 0;
  op1 = lireRegistre(registre, rs(hexa));
  op2 = lireRegistre(registre, rt(hexa));

  ecritureRegistre(HiLo, 32, (op1%op2));
  ecritureRegistre(HiLo, 33, (op1/op2));
}


void or(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rs(hexa)) | lireRegistre(registre, rt(hexa))));
}


void rotr(int registre[], int hexa)
{
  int i = 0, b = 0, valeur = 0;
  valeur = lireRegistre(registre, rt(hexa));

  for(i=0; i < sa(hexa) ;i++)
  {
    b = valeur%2;
    valeur = masque(31,1,valeur);
    valeur += b*pow(2,31);
  }
  ecritureRegistre(registre, rd(hexa), valeur);
}


void sll(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rt(hexa)) << sa(hexa)));
}


void slt(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rs(hexa)) < lireRegistre(registre, rt(hexa))));
}


void srl(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), masque(31, sa(hexa), lireRegistre(registre, rt(hexa))));
}


void sub(int registre[], int hexa)
{
  long sub = 0;
  sub = (lireRegistre(registre, rs(hexa)) - lireRegistre(registre, rt(hexa)));

  if((lireRegistre(registre, rs(hexa)) <= 0) && (lireRegistre(registre, rt(hexa)) >= 0) && (sub > 0)) printf("IntegerOverflow pour SUB\n");
  else ecritureRegistre(registre, rd(hexa), sub);
}

/*
void sw(int registre[], int hexa, int memoire[])
{

}
*/

void xor(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rs(hexa)) ^ lireRegistre(registre, rt(hexa))));
}
