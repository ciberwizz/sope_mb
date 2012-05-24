#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void interface();


int main() {
	interface();
}

void interface(){
    printf("interface\n");

    unsigned int numconta;
    double valor;
    char pin[1024];
    char fifo[128];
    char accao;
    Request req;
    Response resp;


    sprintf(fifo,"ans%ld",getpid());
    createFifo(fifo);

	printf("Introduza o numero da conta: ");
	__fpurge(stdin);
	fscanf (stdin, "%u", &numconta);
	req.numConta = numconta % MAX_NUM_CLIENTES;



    printf("Introduza o pin da conta: ");

    fscanf (stdin, "%s", pin);
    __fpurge(stdin);

    while(strlen(pin) != 4){
            printf("erro pin nao tem 4 caracteres\n");
            printf("Introduza o pin da conta: ");
            fscanf (stdin, "%s", pin);
    }
    strcpy( req.pin, pin );


    printf("num da conta foi : %d\n", numconta);

    printf("pin da conta foi : %s\n", pin);

    do {

    	req.tipo = INVALID;

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

			do {
				printf("Que valor deseja depositar? ");
				__fpurge(stdin);
				scanf(" %lf",&valor);
			}while( valor < 0 );
			req.valor = valor;
			req.tipo = DEPOSITAR;

			break;

//		printf("Levantar dinheiro?   (l)\n");
		case 'l':
		case 'L':

			do {
				printf("Que valor deseja levantar? ");
				__fpurge(stdin);
				scanf("%lf",&valor);
			}while( valor < 0 );
			req.valor = valor;
			req.tipo = LEVANTAR;
			break;

//		printf("Transferir dinheiro? (t)\n");
		case 't':
		case 'T':

			printf("Para que conta deseja transferir? ");
			__fpurge(stdin);
			scanf("%u",&numconta);
			req.numConta2 = numconta % MAX_NUM_CLIENTES;

			do {
				printf("Que valor deseja transferir? ");
				__fpurge(stdin);
				scanf("%lf",&valor);
			}while( valor < 0 );

			req.valor = valor;
			req.tipo = TRANSFERENCIA;
			break;


			break;

//		printf("Consultar saldo?     (c)\n");
		case 'c':
		case 'C':

			req.tipo = CONSULTAR;
			break;

//		printf("Sair?                (s)\n");
		case 's':
		case 'S':
			return;
			break;
			//TODO PARA TESTES
		case 'a': //adicionar
			req.tipo = ADICIONAR;
			strcpy(req.nome, "2314");
			strcpy(req.pin2, "2314");
			break;
		case 'r':
			req.tipo = REMOVER;
			req.numConta2 = 123445;
			break;
		default:
			req.tipo = INVALID;
			break;
		}

		if(req.tipo != INVALID) {
			if(sendRequest(&req) < 0) {
				printf("ERRO: unable to send request\n");
				return;
			} else {
				sprintf(fifo,"%s%ld",FIFO_ANS,(long) req.pid_cli);

				if(req.tipo != LISTAR) {

					if(readFifo(fifo,3,resp.respOriginal) == NULL){
						printf("ERRO: Unable to get response from server\n");
						remove(fifo);
						return;
					} else {
						remove(fifo);
						//faz parce da resposta e poe os resultados nas variaveis
						//exp. "ERROR Sem fundos suficientes\n"
						// status = "ERROR", strError = "Sem fundos suficientes\n"
						sscanf(resp.respOriginal,"%s %[^\n]s",resp.status, resp.msg);
						if(strcmp(resp.status, "OK") == 0){
							printf("Operacao realizada com sucesso. Resposta: %s\n",resp.msg);
							return;
						} else {
							printf("Erro na operacao: %s\n",resp.msg);
							return;
						}
					}
				} else {

					puts("lista de clientes:");

					do {
						if(readFifo(fifo,3,resp.respOriginal) == NULL){
							printf("ERRO: Unable to get response from server\n");
							remove(fifo);
							return;
						}

						printf("%s",resp.respOriginal);
					}while(strcmp( resp.respOriginal, "end") != 0);

					return


				}

			}


			break;
		}

    } while(1);

}
