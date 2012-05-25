#include "util.h"
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAXTHREADS 4



ListaCliente lista;

Cliente *cliente[MAXCLIENTES];

void debugIni();


pthread_mutex_t mlista = PTHREAD_MUTEX_INITIALIZER;
void * trataResp( void*);

int main() {
	int fifo;
	char str[1024];
	pthread_t th;
	pthread_attr_t th_attr;

	int nth = 0;


	pthread_attr_init(&th_attr);
	pthread_attr_setdetachstate(&th_attr,PTHREAD_CREATE_DETACHED);


	//cria fifo request
	fifo = createFifo(FIFO_REQ);

	//verifica se já existem clientes no ficheiro
	if( !lerAcounts(&lista) )
		createListclient(&lista);


	do{

		if(readFifo(FIFO_REQ,0,str) == NULL)
			break;

		if(strcmp(str,"shutdown")==0)
			break;

		pthread_create(&th, &th_attr, trataResp,str);
		nth++;

	}while(1);




pthread_exit(NULL);

remove("requests");
}

void * trataResp( void* str){
	int ret, id;
	ListaCliente *lcl;
	Cliente *cl;
	Response *response;

	Request * request = parseRequest(str);

	//TODO falta por os mutexes..
	response = processRequest(request,&lista);
	//TODO mandas as responses. SE LISTA é diferente!!!

	/*
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
	 */
	return NULL;

}




void debugIni() {
	createListclient(&lista);
	addCliente("nelson","1234",&lista);
	addCliente("Miguel","5678",&lista);
	addCliente("Da","1656",&lista);
	addCliente("Costa","2465",&lista);
	addCliente("Martins","8714",&lista);
	addCliente("Pereira","9832",&lista);
	addCliente("Miguel","4164",&lista);
	addCliente("Marcos","9165",&lista);
	addCliente("Juliana","6519",&lista);
	addCliente("Joao","9720",&lista);
	addCliente("Joana","1642",&lista);

	escreveAcounts(&lista);
}







//
