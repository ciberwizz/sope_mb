#include "util.h"
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAXTHREADS 4

/*
 * TESTAR ESTRUTURA COM FIFOS + THREADS
 *
 * done - main:cria fifo requests
 * done - main:espera que algo seja escrito na fifo
 * done - main:loop para 2 ate receber shutdown
 * 4- thread:spawn de uma thread para tratar do request
 * 5- thread:spawn escreve numa estrutura o pedido passado
 * 6- thread:spawn escreve o retorno num FIFO de resposta
 * 7- thread:spawn sai
 *
 */

ListaCliente clientes;

pthread_mutex_t mlista = PTHREAD_MUTEX_INITIALIZER;
void * trataResp( void*);

int main() {
	int fifo;
	char *str[MAXTHREADS];
	pthread_t th[MAXTHREADS];
	int nth = 0;

	fifo = createFifo(FIFO_REQ);

	createListclient(&clientes);

	srand(time(NULL));
	do{
		str[nth] = (char*) calloc(sizeof(char),1024);
		if(readFifo(FIFO_REQ,0,str[nth]) == NULL)
			break;

		if(strcmp(str[nth],"shutdown")==0)
			break;

		pthread_create(&(th[nth]), NULL, trataResp,str[nth]);
		nth++;

		if(nth == MAXTHREADS){
			for(nth=0 ; nth < MAXTHREADS ; nth++){
				pthread_join(th[nth],NULL); //pensaar em receber a parte de ret
				free(str[nth]);
			}
			nth=0;
		}

	}while(1);




	pthread_exit(NULL);

	remove("requests");
}

void * trataResp( void* str){

	char * req = (char*) str;
	int ret, id;
	char resp[128];

	pthread_mutex_lock(&mlista);
	ret = addCliente(req,"1234",&clientes);
	pthread_mutex_unlock(&mlista);

	sscanf(req,"%d",&id);
	sprintf(resp,"%d OK\n",id);

	ret = rand()%3+2;
	sleep(ret);
	printf("sleep=%d; ",ret);

	usleep(500);
	ret =writeFifo(FIFO_ANS,resp);
	//if(!ret)
		printf("ret=%d a tentar a por a resposta: %s",ret,resp);

	return NULL;

}



