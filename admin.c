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
			fgets(req.nome,20,stdin);


			printf("\nQual o pin do novo Cliente? ");
			__fpurge(stdin);
			fgets(req.pin2,4,stdin);
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

			return;

			break;

//		printf("Sair?                (s)\n");
		case 's':
		case 'S':
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
