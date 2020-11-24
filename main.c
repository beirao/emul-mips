#include "header/convertion_hexa.h"
#include "header/traitement_instructions.h"

int main(int argc, char const *argv[])
{
  char fichier_src[TAILLE_MAX] = "src/";
  char fichier_out[TAILLE_MAX] = "out/";

  strcat(fichier_src, argv[1]);
  strcat(fichier_out, argv[2]);
  lireDonnees(fichier_src,fichier_out);

  return 0;
}
