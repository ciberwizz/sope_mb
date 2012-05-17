#include "util.h"

#include <stdio.h>
#include <stdlib.h>

void interface();


int main() {

	pid_t pid = getpid();
	char spid[11];

	sprintf(spid,"ans%ld",(long int) pid);
	if( createFifo(spid) != 0) {
		printf("\nimpossivel criar FIFO.\n");
		return 1;
	}

	interface();

	remove(spid);
	return 0;
}

void interface(){
    printf("interface\n");

    unsigned int numconta;
    char pin[5];
    char accao;

    printf("Introduza o numero da conta: ");
    fscanf (stdin, "%ud", &numconta);

    __fpurge(stdin);

    printf("Introduza o pin da conta: ");
    fscanf (stdin, "%s", pin);

    while(strlen(pin) != 4)
    {
            printf("erro pin nao tem 4 caracteres\n");
            printf("Introduza o pin da conta: ");
            fscanf (stdin, "%s", pin);
    }


    printf("num da conta foi : %d\n", numconta);

    printf("pin da conta foi : %s\n", pin);

    do {
		printf("\n\n");
		printf("Que operacao deseja efectuar?\n");
		printf("Depositar dinheiro?  (d)\n");
		printf("Levantar dinheiro?   (l)\n");
		printf("Transferir dinheiro? (t)\n");
		printf("Consultar saldo?     (c)\n");
		printf("Sair?                (s)\n");

		__fpurge(stdin);
		accao = getchar();

		switch(accao){

//		printf("Depositar dinheiro?  (d)\n");
		case 'd':
		case 'D':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Levantar dinheiro?   (l)\n");
		case 'l':
		case 'L':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Transferir dinheiro? (t)\n");
		case 't':
		case 'T':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Consultar saldo?     (c)\n");
		case 'c':
		case 'C':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Sair?                (s)\n");
		case 's':
		case 'S':
			return;
			break;

		}

    } while(1);

}

