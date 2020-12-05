#include "../header/registre.h"


/*id_registre : 
$zero    = 0
$at      = 1
$v0->$v1 = 2->3
$a0->$a3 = 4->7
$t0->$t7 = 8->15
$s0->$s7 = 16->25 
$t8->$t9 = 24->25
$k0->$k1 = 26->27
$gp      = 28
$sp      = 29
$fp      = 30
$ra      = 31
$HI      = 32
$LO      = 33
$PC      = 34
*/

int lireRegistre(int registre[], int HiLo[], int *PC , int id_registre){
    if(id_registre >= 0 && id_registre <= 31){
        return registre[id_registre];
    }
    else if(id_registre == 32){
        return HiLo[0];
    }
    else if(id_registre == 33){
        return HiLo[1];
    }
    else if(id_registre == 34){
        return PC;
    }
    else{
        fprintf(strerror, "ERREUR : id registre non definie");
    }
}


void ecritureRegistre(int registre[], int HiLo[], int *PC, int id_registre, int valeur){
    if(id_registre >= 0 && id_registre <= 31){
        registre[id_registre] = valeur;
    }
    else if(id_registre == 32){
        HiLo[0] = valeur;
    }
    else if(id_registre == 33){
        HiLo[1] = valeur;
    }
    else if(id_registre == 34){
        PC = valeur;
    }
    else{
        fprintf(strerror, "ERREUR : id registre non definie");
    }

}

/*id_registre : 
$zero    = 0
$at      = 1
$v0->$v1 = 2->3
$a0->$a3 = 4->7
$t0->$t7 = 8->15
$s0->$s7 = 16->25 
$t8->$t9 = 24->25
$k0->$k1 = 26->27
$gp      = 28
$sp      = 29
$fp      = 30
$ra      = 31
$HI      = 32
$LO      = 33
$PC      = 34
*/
void affichageRegistre(int registre[], int HiLo[], int *PC){
    
    printf("-------------------------------------\n");
    printf("Registre : \n");

    printf("$zero = %d \n",registre[0]);
    printf("$at = %d \n",registre[1]);
    printf("$v0 = %d | v1 = %d \n", registre[2], registre[3]);
    printf("$a0 = %d | a1 = %d | a2 = %d | a3 = %d\n", registre[4], registre[5], registre[6], registre[7]);
    printf("$t0 = %d | t1 = %d | t2 = %d | t3 = %d | t4 = %d | t5 = %d | t6 = %d | t7 = %d\n", registre[8], registre[9], registre[10], registre[11], registre[12], registre[13], registre[14], registre[15]);
    printf("$s0 = %d | s1 = %d | s2 = %d | s3 = %d | s4 = %d | s5 = %d | s6 = %d | s7 = %d\n", registre[8+8], registre[9+8], registre[10+8], registre[11+8], registre[12+8], registre[13+8], registre[14+8], registre[15+8]);
    printf("$t8 = %d | t9 = %d \n", registre[24], registre[25]);
    printf("$k0 = %d | k1 = %d \n", registre[26], registre[27]);
    printf("$gp = %d \n",registre[28]);
    printf("$sp = %d \n",registre[29]);
    printf("$fp = %d \n",registre[30]);
    printf("$ra = %d \n",registre[31]);
    

    printf("$HI = %d | LO = %d \n", registre[32], registre[33]);
    printf("$PC = %d \n",registre[34]);


    printf("-------------------------------------\n");
}