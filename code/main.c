#include "../header/traitement_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"


int main(int argc, char const *argv[])
{
  char fichier_src[TAILLE_MAX] = "src/";

  int *registre, *HiLo, *memoire;
  int *PC = 0;

  
  memoire = malloc(128*sizeof(int));
  registre = malloc(32*sizeof(int));
  HiLo = malloc(2*sizeof(int)); 
  
  affichageRegistre(registre, HiLo, PC);

  if(registre == NULL || HiLo == NULL || memoire == NULL ) printf("ERREUR : malloc");
  
  strcat(fichier_src, argv[1]);

  lireDonnees(fichier_src,memoire);
  
  affichageMemoire(memoire);
  affichageRegistre(registre, HiLo, PC);
  
  free(registre);
  free(HiLo);
  free(memoire);

  return 0;
  
}
