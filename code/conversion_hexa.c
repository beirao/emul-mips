#include "../header/conversion_hexa.h"


int conversionHexa(char chaine[], int argument[]){
    int hexa = 0, function = 0, op_code = 0;

    /* ___R-TYPE___ */

    /* Nous avons regroupé les instructions de même format ensemble */
    /* Format : Mnemonic rd, rs, rt (ADD - AND - OR - SLT - SUB - XOR) */
    if(testChaine(chaine, "ADD ") || testChaine(chaine, "AND ") || testChaine(chaine, "OR ") || testChaine(chaine, "SLT ") || testChaine(chaine, "SUB ") || testChaine(chaine, "XOR ")){
        if(testChaine(chaine, "ADD ")) function = 32;
        else if(testChaine(chaine, "AND ")) function = 36;
        else if(testChaine(chaine, "OR ")) function = 37;
        else if(testChaine(chaine, "SLT ")) function = 42;
        else if(testChaine(chaine, "SUB ")) function = 34;
        else if(testChaine(chaine, "XOR ")) function = 38;

        hexa = rType(argument[0], argument[1], argument[2], 0, function);
    }

    /* Format : Mnemonic rs, rt (DIV - MULT) */
    else if(testChaine(chaine, "DIV ") || testChaine(chaine, "MULT ")){
        if(testChaine(chaine, "DIV ")) function = 26;
        else if(testChaine(chaine, "MULT ")) function = 24;

        hexa = rType(0, argument[0], argument[1], 0, function);
    }

    /* Format : Mnemonic rs (JR) */
    else if(testChaine(chaine, "JR ")){
        hexa = rType(0, argument[0], 0, 0, 8);
    }

    /* Format : Mnemonic rd (MFHI - MFLO) */
    else if (testChaine(chaine, "MFHI ") || testChaine(chaine, "MFLO ")){
        if(testChaine(chaine, "MFHI ")) function = 16;
        else if(testChaine(chaine, "MFLO ")) function = 18;

        hexa = rType(argument[0], 0, 0, 0, function);
      }

    /* Format : Mnemonic (NOP - SYSCALL) */
    else if(testChaine(chaine, "NOP") || testChaine(chaine, "SYSCALL ")){
        if(testChaine(chaine, "NOP")) function = 0;
        else if(testChaine(chaine, "SYSCALL ")) function = 12;

        hexa = rType(0, 0, 0, 0, function);
    }

    /* Format : Mnemonic rd, rt, sa (bit 21 à '1')(ROTR) */
    else if(testChaine(chaine, "ROTR ")){
        hexa = rType(argument[0], 1, argument[1], argument[2], 2);
    }

    /* Format : Mnemonic rd, rt, sa (SLL - SRL) */
    else if(testChaine(chaine, "SLL ") || testChaine(chaine, "SRL ")){
        if(testChaine(chaine, "SLL ")) function = 0;
        else if(testChaine(chaine, "SRL ")) function = 2;

        hexa = rType(argument[0], 0, argument[1], argument[2], function);
    }


    /* ___I-Type___ */

    /* Format : Mnemonic rt, rs, immediate (ADDI) */
    else if(testChaine(chaine, "ADDI ")){
        hexa = iType(8, argument[0], argument[1], argument[2]);
    }

    /* Format : Mnemonic rs, rt, offset (BEQ - BNE) */
    else if(testChaine(chaine, "BEQ ") || testChaine(chaine, "BNE ")){
        if(testChaine(chaine, "BEQ ")) op_code = 4;
        else if(testChaine(chaine, "BNE ")) op_code = 5;

        hexa = iType(op_code, argument[1], argument[0], argument[2]);
    }

    /* Format : Mnemonic rs, offset (BGTZ - BLEZ) */
    else if(testChaine(chaine, "BGTZ ") || testChaine(chaine, "BLEZ ")){
        if(testChaine(chaine, "BGTZ ")) op_code = 7;
        else if(testChaine(chaine, "BLEZ ")) op_code = 6;

        hexa = iType(op_code, 0, argument[0], argument[1]);
    }

    /* Format : Mnemonic rt, immediate (LUI) */
    else if(testChaine(chaine, "LUI ")){
        hexa = iType(15, argument[0], 0, argument[1]);
    }

    /* Format : Mnemonic rt, offset(base) (LW - SW) */
    else if(testChaine(chaine, "LW ") || testChaine(chaine, "SW ")){
        if(testChaine(chaine, "LW ")) op_code = 35;
        else if(testChaine(chaine, "SW ")) op_code = 43;

        hexa = iType(op_code, argument[0], argument[2], argument[1]);
    }


    /* ___J-Type___ */

    /* Format : Mnemonic target (J - JAL) */
    else if(testChaine(chaine, "J ") || testChaine(chaine, "JAL ")){
        if(testChaine(chaine, "J ")) op_code = 2;
        else if(testChaine(chaine, "JAL ")) op_code = 3;

        hexa = jType(op_code, argument[0]);
    }


    /* ___Ligne vide ou Commentaire__ */
    else if(chaine[0] == '#' || chaine[0] == '\r' || (chaine[0] == '\n')){
        hexa = 0;
    }


    /* ___ERREUR___ */
    else{
        hexa = 0;
        printf("erreur : commande inconnue\n");
    }

    return hexa;
}



int rType(int rd, int rs, int rt, int sa, int function){
    int hexa = 0;

    if((rd < 32) && (rt < 32) && (rs < 32) && (sa < 32))
    {
      hexa += function;
      hexa += sa << 6;
      hexa += rd << 11;
      hexa += rt << 16;
      hexa += rs << 21;
    }
    else
    {
      printf("Erreur : Overflow valeur (registre ou sa)\n");
    }

    return hexa;
}

int iType(int op_code, int rt, int rs, int immediate){
    int hexa = 0;

    if((immediate < pow(2,15)) && (rt < 32) && (rs < 32))
    {
      hexa += immediate;
      hexa += rt << 16;
      hexa += rs << 21;
      hexa += op_code << 26;
    }
    else
    {
      printf("Erreur : Overflow valeur (immediate, offset ou registre)\n");
    }

    return hexa;
}

int jType(int op_code, int target){
    int hexa = 0;

    if(target < pow(2,25))
    {
      hexa += target;
      hexa += op_code << 25;
    }
    else
    {
      printf("Erreur : Overflow valeur\n");
    }

    return hexa;
}



int testChaine(char chaine[], char mot[]){
    long unsigned int i;

    for(i = 0; i <= (strlen(mot)-1); i++){
        if(chaine[i] != mot[i])  return 0;
    }
    return 1;
}
