#include "fonction.h"

int main(int argc, char const *argv[])
{
  char fichier_test[TAILLE_MAX] = "src/";

  strcat(fichier_test, argv[1]);
  lireDonnees(fichier_test,"transcription_hexa");

  return 0;
}
