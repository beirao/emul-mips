#include "../header/exec_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"

/*
void exec(int registre[], int memoire[], int HiLo[], int *PC)
{*/



  /* Il faudra incrementer PC après chaque instructions SAUF s'il y a eu une instruction de branchement (faire une comparaison avec PC avant/après l'instruction) */
/*}


void appelR(int registre[], int hexa, int HiLo[])
{

}


void appelI(int registre[], int memoire[], int *PC, int hexa)
{

}


void appelJ(int registre[], int hexa, int *PC)
{

}


void decalagePC(int *PC, int nb_decalage)
{

}
*/

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
