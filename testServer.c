#include "util.h"
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAXTHREADS 4



ListaCliente lista;

Cliente *lcliente[MAX_NUM_CLIENTES];

void debugIni();


pthread_mutex_t mlista = PTHREAD_MUTEX_INITIALIZER;
void * trataResp( void*);

int main() {
	int fifo;
	char str[1024];
	char *thread;
	pthread_t th;
	pthread_attr_t th_attr;

	int nth = 0;


	pthread_attr_init(&th_attr);
	pthread_attr_setdetachstate(&th_attr,PTHREAD_CREATE_DETACHED);


	//cria fifo request
	fifo = createFifo(FIFO_REQ);

	//verifica se já existem clientes no ficheiro
	if( !lerAcounts(&lista) )
		createArrayclient(lcliente);


	do{
		memset(str,0,1024);


		if(readFifo(FIFO_REQ,0,str) == NULL)
			break;

		thread = (char *) calloc(1024,sizeof(char));
		strcat(thread,str);

		if(strcmp(str,"shutdown")==0)
			break;

		pthread_create(&th, &th_attr, trataResp,thread);
		nth++;

	}while(1);



	remove("requests");
	pthread_exit(NULL);


}

void * trataResp( void* str){
	int ret, i, n;
	arrCliente lcl;
	Cliente *cl;
	Response *response;
	char fifo[10], temp[1024];
	char * tmp;
	char * tmp2;
	Request * request = parseRequest(str);

	pthread_mutex_lock(&mlista);
	response = processRequest(request,lcliente);
	pthread_mutex_unlock(&mlista);

	sprintf(fifo, "ans%d",(int) request->pid_cli);

	writeFifo(fifo,response->respOriginal);

	lcl = lcliente;

	if(request->tipo == LISTAR && strcmp(response->status, "OK") == 0){
		n=0;
		usleep(100*1000); //10ms
		while(lcl != NULL){
			memset(response->respOriginal,0,128);
			memset(temp,0,1024);
			i=1;

			pthread_mutex_lock(&mlista);
			lcl = listarClientes(lcl,temp,&n);
			pthread_mutex_unlock(&mlista);

			tmp = strtok(temp," ");
			do {
				if(i++ != 3) {
					strcat(response->respOriginal," ");
					strcat(response->respOriginal,tmp);
				}
				tmp = strtok(NULL," ");
			}while(tmp != NULL);
			writeFifo(fifo,response->respOriginal);
			usleep(100*1000); //10ms
		}
		writeFifo(fifo,"end\0");
	}

	free(str);
	free(response);
	free(request);
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
