//#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int createFifo(char*);
char* readFifo(char*, int);
int writeFifo(char*, char*);


void interface();


int main() {

	pid_t pid = getpid();
	char spid[11];

	sprintf(spid,"ans%ld",(long int) pid);
	if( creatFifo(spid) != 0) {
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

int createFifo(char* ff){
	// S_IRWXU | S_IRWXO = dar todas as permissoes ao ficheiro
	return mkfifo(ff, S_IRWXU | S_IRWXO);

}

char* readFifo(char* path, int timeout){
	int fifo = open(path, O_RDONLY | O_NONBLOCK);
	char buff[1000];
	int start = time(), end = 0;

	if(timeout == 0)
		timeout = -1;

	//erro
	if( fifo == -1)
		return NULL;

	while( (end - start) != timeout){
		if(read(fifo, buff, 1000) > 0 )
			break;

		//sleep for 250 ms
		usleep(250 * 1000);

		end = time();
	}

	if( end-start == 0)
		return NULL;
	else return buff;
}

int writeFifo(char* path, char* buff){
 //TODO
}

