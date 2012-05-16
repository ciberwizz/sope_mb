#include "util.h"


void interface();

int main() {



}

void interface(){
    printf("interface\n");

    unsigned int numconta;
    char pin[4];

    printf("Introduza o numero da conta: ");
    fscanf (stdin, "%d", &numconta);

    __fpurge(stdin);

    printf("Introduza o pin da conta: ");
    fscanf (stdin, "%s", &pin);

    while(strlen(pin) != 4)
    {
            printf("erro pin nao tem 4 caracteres\n");
            printf("Introduza o pin da conta: ");
            fscanf (stdin, "%s", &pin);
    }


    printf("num da conta foi : %d\n", numconta);

    printf("pin da conta foi : %s\n", pin);

}

