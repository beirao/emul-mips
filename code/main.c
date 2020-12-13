#include "../header/traitement_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/def_instructions.h"
#include "../header/exec_instructions.h"


int main(int argc, char const *argv[])
{
  char fichier_src[TAILLE_MAX] = "src/";

  int *registre, *HiLo, *memoire;
  int *PC = NULL;

    /* Variables de test */
  int hexa = 0;
    /* Fin */

  memoire = malloc(TAILLE_MEMOIRE*sizeof(int));
  registre = malloc(TAILLE_REGISTRE*sizeof(int));
  HiLo = malloc(TAILLE_HILO*sizeof(int));

  if(registre == NULL || HiLo == NULL || memoire == NULL ) printf("ERREUR : malloc\n");


  affichageRegistre(registre, HiLo, PC);

  strcat(fichier_src, argv[1]);

  lireDonnees(fichier_src,memoire);
  PC = memoire;


    /* Zone de Tests */
  hexa = lireMemoire(PC, 0);
  PC++;
  addi(registre, hexa);
  hexa = lireMemoire(PC, 0);
  PC++;
  addi(registre, hexa);
  hexa = lireMemoire(PC, 0);
  PC++;
  and(registre, hexa);
  hexa = lireMemoire(PC, 0);
  PC++;
  add(registre, hexa);
    /* Fin */


  affichageMemoire(memoire);
  affichageRegistre(registre, HiLo, PC);

  free(registre);
  free(HiLo);
  free(memoire);

  return 0;
}
