#include "../header/exec_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/def_instructions.h"
#include "../header/traitement_instructions.h"


int *exec(int registre[], int memoire[], int HiLo[], int *PC)
{
  int type;
  int *PCinitial;

  PCinitial = PC;
  type = masque(31,26,*PC);

  if(type == 0){                                    /*Rtype*/
    PC = appelR(registre, *PC, HiLo, PC);
  }

  else if(type == 3 || type == 2){                  /*Jtype*/
    PC = appelJ(registre, memoire, PC, *PC);
  }

  else{                                             /*Itype*/
    PC = appelI(registre, memoire, PC, *PC);
  }

  if(PCinitial == PC){
    PC++;
  }
  return PC;
}



int *appelR(int registre[], int hexa, int HiLo[], int *PC)
{
  int fonction;
  fonction = masque(5,0,hexa);

  switch (fonction)
  {
  case 32: add(registre, hexa); break;
  case 36: and(registre, hexa); break;
  case 0: sll(registre, hexa);  break;
  case 2: if(masque(21,21, hexa) == 1) rotr(registre, hexa);
          else                         srl(registre, hexa);
          break;
  case 16: mfhi(registre, hexa, HiLo); break;
  case 18: mflo(registre, hexa, HiLo); break;
  case 26: divi(registre, hexa, HiLo); break;
  case 24: mult(registre, hexa, HiLo); break;
  case 37: or(registre, hexa);         break;
  case 42: slt(registre, hexa);        break;
  case 34: sub(registre, hexa);        break;
  case 38: xor(registre, hexa);        break;
  case 8: PC = jr(registre, hexa, PC); break;
  case 12 : break;

  default: printf("ERREUR : instruction non definie\n"); break;
  }
  return PC;
}


int *appelI(int registre[], int memoire[], int *PC, int hexa)
{
  int opcode;
  opcode = masque(31,26,hexa);

  switch (opcode)
  {
  case 8 : addi(registre, hexa);          break;
  case 4 : PC = beq(registre, hexa, PC);  break;
  case 7 : PC = bgtz(registre, hexa, PC); break;
  case 6 : PC = blez(registre, hexa, PC); break;
  case 5 : PC = bne(registre, hexa, PC);  break;
  case 35 : lw(registre, hexa, memoire);  break;
  case 43 : sw(registre, hexa, memoire);  break;
  case 15 : lui(registre, hexa); break;

  default: printf("ERREUR : instruction non definie\n"); break;
  }
  return PC;
}


int *appelJ(int registre[], int memoire[], int *PC, int hexa)
{
  int opcode;
  opcode = masque(31,26,hexa);

  switch (opcode)
  {
  case 2 : PC = j(hexa, memoire); break;
  case 3 : PC = jal(registre, hexa, memoire, PC); break;

  default: printf("ERREUR : instruction non definie\n"); break;
  }
  return PC;
}


int masque(int bit_haut, int bit_bas, int hexa)
{
  int m = 0, i = 0;
  hexa = hexa >> bit_bas;
  for(i=0; i <= (bit_haut-bit_bas) ;i++)
  {
    m = m << 1;
    m++;
  }
  return (hexa & m);
}
