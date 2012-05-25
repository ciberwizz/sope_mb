#include "util.h"

// nr conta de admin =000 000 0;
void interface();

int main() {

	interface();
	return 0;
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
		printf("Administrador que operacao deseja efectuar?\n");
		printf("(l) - Listar utilizadores?  \n");
		printf("(a) - Adicionar utilizadores?   \n");
		printf("(r) - Remover utilizadores?   \n");
		printf("(d) - Desligar Servidor?     \n");
		printf("(s) - Sair?                \n");

		__fpurge(stdin);
		accao = getchar();

		switch(accao){

		//adicionar
		case 'a':
		case 'A':
			req.tipo = ADICIONAR;

			printf("Qual o nome do novo Cliente? ");
			__fpurge(stdin);
			scanf(" %20s", req.nome);

			printf("\nQual o pin do novo Cliente? ");
			__fpurge(stdin);
			scanf(" %4s", req.pin2);
			break;

		//remover
		case 'r':
		case 'R':
			req.tipo = REMOVER;
			do {
				printf("Qual o numero de conta a remover? ");
				__fpurge(stdin);
				scanf(" %d", &req.numConta2);
			}while(req.numConta2 < 1);

			break;

//		Listar
		case 'l':
		case 'L':
			req.tipo = LISTAR;

			break;


//		desligar server
		case 'd':
		case 'D':

			if( writeFifo(FIFO_REQ,"shutdown")<1 )
				printf("ERRO ao mandar comando");
			remove(fifo);

			return;

			break;

//		printf("Sair?                (s)\n");
		case 's':
		case 'S':
			remove(fifo);
			return;
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



				if(readFifo(fifo,3,resp.respOriginal) == NULL)
					printf("ERRO: Unable to get response from server\n");
				 else {

					//faz parce da resposta e poe os resultados nas variaveis
					//exp. "ERROR Sem fundos suficientes\n"
					// status = "ERROR", strError = "Sem fundos suficientes\n"
					sscanf(resp.respOriginal,"%s %[^\n]s",resp.status, resp.msg);
					if(strcmp(resp.status, "OK") == 0)
						printf("Operacao realizada com sucesso. \nResposta: %s\n",resp.msg);
					else
						printf("Erro na operacao: %s\n",resp.msg);



					if(req.tipo != LISTAR || strcmp(resp.status,"OK") != 0 ){
						remove(fifo);
						return;
					} else {

						puts("lista de clientes:");

						do {
							memset(resp.respOriginal,0,128);
							if(readFifo(fifo,0,resp.respOriginal) == NULL){
								printf("ERRO: Unable to get response from server\n");
								break;
							}

							printf("%s\n",resp.respOriginal);
						}while(strcmp( resp.respOriginal, "end") != 0);

						puts("FIM DA LISTA");
						remove(fifo);
						return;


					}
				 }



			}


			break;
		}

    } while(1);

}
