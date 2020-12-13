#include "../header/exec_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"

/*
void exec(int registre[], int memoire[], int HiLo[], int *PC)
{}*/



  /* Il faudra incrementer PC après chaque instructions SAUF s'il y a eu une instruction de branchement (faire une comparaison avec PC avant/après l'instruction) */



void appelR(int registre[], int hexa, int HiLo[], int *PC)
{
  int fonction;
  fonction = masque(5,0,hexa);

  switch (fonction)
  {
  case 0b100000: add(registre, hexa); break;
  case 0b100100: and(registre, hexa); break;
  case 0b000000: sll(registre, hexa); break;
  case 0b000010: if(masque(21,21, hexa) == 1) rotr(registre, hexa);
                 else                         srl(registre, hexa);
                 break;
  case 0b010000: mfhi(registre, hexa);       break;
  case 0b010010: mflo(registre, hexa);       break;
  case 0b011010: divi(registre, hexa, HiLo); break;
  case 0b011000: mult(registre, hexa, HiLo); break;
  case 0b100101: or(registre, hexa);         break;
  case 0b101010: slt(registre, hexa);        break;
  case 0b100010: sub(registre, hexa);        break;
  case 0b100110: xor(registre, hexa);        break;
  case 0b001000: PC = jr(registre, hexa, PC);    break;

  default: printf("ERREUR : instruction non definie"); break;
  }
}


void appelI(int registre[], int memoire[], int *PC, int hexa)
{
  int fonction;
  fonction = masque(31,26,hexa);

  switch (fonction)
  {
  case 0b001000 : addi(registre, hexa); break;
  case 0b000100 : PC = beq(registre, hexa, PC); break;
  case 0b000111 : PC = bgtz(registre, hexa, PC); break;
  case 0b000110 : PC = blez(registre, hexa, PC); break;
  case 0b000101 : PC = bne(registre, hexa, PC); break;
  case 0b100011 : lw(registre, hexa, memoire); break;
  case 0b101011 : sw(registre, hexa, memoire); break;
  case 0b001111 : lui(registre, hexa); break;
  
  default: printf("ERREUR : instruction non definie"); break;
  }
}


void appelJ(int registre[], int hexa, int *PC)
{
  int fonction;
  fonction = masque(31,26,hexa);

  switch (fonction)
  {
  case 0b000010 : PC = j(registre, hexa, PC); break;
  case 0b000011 : PC = jal(registre, hexa, PC); break;
  
  default: printf("ERREUR : instruction non definie"); break;
  }
}


/*void decalagePC(int *PC, int nb_decalage)
{

}*/


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
