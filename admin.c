#include "util.h"

// nr conta de admin =000 000 0;
void interface();

int main() {

	interface();
	return 0;
}

void interface(){
    printf("interface admin\n");

    // nr conta de admin =000 000 0;
    unsigned int numconta = 0;
    char pin[5];
    char accao;

    __fpurge(stdin);

    printf("Introduza o pin da conta de administrador: ");
    fscanf (stdin, "%s", pin);

    while(strlen(pin) != 4)
    {
            printf("erro pin nao tem 4 caracteres\n");
            printf("Introduza o pin da conta: ");
            fscanf (stdin, "%s", pin);
    }


    printf("num da conta foi : %ud\n", numconta);

    printf("pin da conta foi : %s\n", pin);

    do {
		printf("\n\n");
		printf("Que operacao deseja efectuar?\n");
		printf("Listar contas?     (l)\n");
		printf("Criar nova conta?  (c)\n");
		printf("Remover conta?     (r)\n");
		printf("Desligar servidor? (d)\n");
		printf("Sair?              (s)\n");

		__fpurge(stdin);
		accao = getchar();

		switch(accao){

//		printf("Listar contas?     (l)\n");
		case 'l':
		case 'L':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Criar nova conta?  (c)\n");
		case 'c':
		case 'C':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Remover conta?     (r)\n");
		case 'r':
		case 'R':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Desligar servidor? (d)\n");
		case 'd':
		case 'D':
			//TODO enviar comando para o fifo request e esperar pela resposta
			break;

//		printf("Sair?              (s)\n");
		case 's':
		case 'S':
			return;
			break;

		}

    } while(1);

}

