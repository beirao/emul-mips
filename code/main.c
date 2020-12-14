#include "../header/traitement_instructions.h"
#include "../header/memoire.h"
#include "../header/registre.h"
#include "../header/def_instructions.h"
#include "../header/exec_instructions.h"
#include "../header/mode.h"

int main(int argc, char const *argv[])
{
  char fichier_src[TAILLE_MAX] = "src/";

  int *registre, *HiLo, *memoire;
  int *PC = NULL;
  

  memoire = malloc(TAILLE_MEMOIRE*sizeof(int));
  registre = malloc(TAILLE_REGISTRE*sizeof(int));
  HiLo = malloc(TAILLE_HILO*sizeof(int));


  if(registre == NULL || HiLo == NULL || memoire == NULL ) printf("ERREUR : malloc\n");

  /*Commande : 
    emul_mips                  -> mode interactif
    emul_mips fichier.txt      -> mode non interactif
    emul_mips fichier.txt -pas -> mode non interactif pas à pas*/

  if(argc == 1)
  {
    modeInteractif(memoire, registre, PC, HiLo);
  }                                               
  else if(argc == 2 && argv[1] != NULL)
  {
    modeNonInteractif(fichier_src, argv[1], memoire, registre, PC, HiLo, 0);
  }                        
  else if(argc == 3 && argv[1] != NULL && strcmp("-pas", argv[2]) == 0)
  {
    modeNonInteractif(fichier_src, argv[1], memoire, registre, PC, HiLo, 1); /*1 pour le mode pas a pas*/
  }   
  else
  {
    printf("ERREUR de synthaxe dans la commande d'execution");
  }
  

  free(registre);
  free(HiLo);
  free(memoire);

  return 0;
}
