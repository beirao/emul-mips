#include "../header/def_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"

void add(int registre[], int hexa)
{
  int add = 0;
  add = (lireRegistre(registre, rs(hexa)) + lireRegistre(registre, rt(hexa)));

  if((lireRegistre(registre, rs(hexa)) >= 0) && (lireRegistre(registre, rt(hexa)) >= 0) && (add < 0)) printf("IntegerOverflow pour ADD\n");
  else if((lireRegistre(registre, rs(hexa)) < 0) && (lireRegistre(registre, rt(hexa)) < 0) && (add >= 0)) printf("IntegerOverflow pour ADD\n");
  else ecritureRegistre(registre, rd(hexa), add);
}


void addi(int registre[], int hexa)
{
  int add = 0;
  add = (lireRegistre(registre, rs(hexa)) + immediate(hexa));

  if((lireRegistre(registre, rs(hexa)) >= 0) && (immediate(hexa) >= 0) && (add < 0)) printf("IntegerOverflow pour ADDI\n");
  else if((lireRegistre(registre, rs(hexa)) < 0) && (immediate(hexa) < 0) && (add >= 0)) printf("IntegerOverflow pour ADDI\n");
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

int *j(int hexa, int *PC)
{
  /* On decide de legerement modifier l'utilisation de Jump : pour obtenir notre adresse de saut, on ajoute la valeur dans immediate à l'adresse de la premiere instruction en memoire */
  /* Exemple : J 2 effectue un saut a la deuxième instruction du programme, sachant que le programme commence a l'instruction 0 (le calcul decrit dans l'annexe nous faisait sortir de la memoire et etait difficile a utiliser) */
  PC += immediate(hexa);
  return PC;
}

int *jal(int registre[], int hexa, int *PC, int *retour)
{
  /* On utilise le meme principe que pour Jump */
  ecritureRegistre(registre, 31, (retour+1));
  PC += immediate(hexa);
  return PC;
}


int *jr(int registre[], int hexa, int *PC)
{
  int temp = 0;
  /* Les registres n'ont pas assez de bit pour contenir une adresse de saut valide, on combine donc leurs valeurs avec l'adresse du debut de la memoire */
  temp = PC;
  PC = (PC - temp/4) + lireRegistre(registre, rs(hexa))/4;

  return PC;
}


void lui(int registre[], int hexa)
{
  ecritureRegistre(registre, rt(hexa), (immediate(hexa) << 16));
}


void lw(int registre[], int hexa, int memoire[])
{
  int index = 0;
  if(immediate(hexa)%4 == 0)
  {
    index = lireRegistre(registre, rs(hexa)) + (immediate(hexa)/4);
    ecritureRegistre(registre, rt(hexa), lireMemoire(memoire, index, 1));
  }
  else
  {
    printf("Address Error : l'offset doit être un multiple de 4\n");
  }
}


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
  if(hexa != 0) /* Condition qui permet de ne pas afficher d'erreur pour NOP */
  {
    ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rt(hexa)) << sa(hexa)));
  }
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
  int sub = 0;
  sub = (lireRegistre(registre, rs(hexa)) - lireRegistre(registre, rt(hexa)));

  if((lireRegistre(registre, rs(hexa)) < 0) && (lireRegistre(registre, rt(hexa)) >= 0) && (sub >= 0)) printf("IntegerOverflow pour SUB\n");
  else if((lireRegistre(registre, rs(hexa)) >= 0) && (lireRegistre(registre, rt(hexa)) < 0) && (sub < 0)) printf("IntegerOverflow pour SUB\n");
  else ecritureRegistre(registre, rd(hexa), sub);
}


void sw(int registre[], int hexa, int memoire[])
{
  int index = 0;
  if(immediate(hexa)%4 == 0)
  {
    index = lireRegistre(registre, rs(hexa)) + (immediate(hexa)/4);
    ecritureMemoire(memoire, index, lireRegistre(registre, rt(hexa)), 1);
  }
  else
  {
    printf("Address Error : l'offset doit être un multiple de 4\n");
  }

}


void xor(int registre[], int hexa)
{
  ecritureRegistre(registre, rd(hexa), (lireRegistre(registre, rs(hexa)) ^ lireRegistre(registre, rt(hexa))));
}
