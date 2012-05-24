#include "util.h"
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define MAXTHREADS 4



ListaCliente lista;

Cliente *cliente[MAXCLIENTES];


int main(){
	int i = 0,cli1 ,cli2;
	int nclientes;


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


    nclientes = listToArray(&lista,cliente);
    sortArrayCliente(cliente, nclientes);
    bsearchClient(cliente,nclientes,7);

    puts("");
    for( i = 0; cliente[i] != NULL ;i++)
    	printf("i=%d; nome = %s; numconta = %d\n",i, (cliente[i])->nome, (cliente[i])->numconta);
//
//    puts("\n\nnow to sortit!!\n\n\n");

    cli1 = 1;
    cli2 = 6;

   /* i = clienteComparator(cliente[cli1],cliente[cli2]);

    if(i > 0)
    	printf("cli1:%s:%d > cl2:%s:%d\n",cliente[cli1]->nome,cliente[cli1]->numconta, cliente[cli2]->nome, cliente[cli2]->numconta);
    else
	if(i < 0)
		printf("cli1:%s:%d < cl2:%s:%d\n",cliente[cli1]->nome,cliente[cli1]->numconta, cliente[cli2]->nome, cliente[cli2]->numconta);
	else
		printf("cli1:%s:%d == cl2:%s:%d\n",cliente[cli1]->nome,cliente[cli1]->numconta, cliente[cli2]->nome, cliente[cli2]->numconta);

*/
}







//
//pthread_mutex_t mlista = PTHREAD_MUTEX_INITIALIZER;
//void * trataResp( void*);
//
//int main() {
//	int fifo;
//	char *str[MAXTHREADS];
//	pthread_t th[MAXTHREADS];
//	int nth = 0;
//
//	fifo = createFifo(FIFO_REQ);
//
//	createListclient(&clientes);
//
//	srand(time(NULL));
//	do{
//		str[nth] = (char*) calloc(sizeof(char),1024);
//		if(readFifo(FIFO_REQ,0,str[nth]) == NULL)
//			break;
//
//		if(strcmp(str[nth],"shutdown")==0)
//			break;
//
//		pthread_create(&(th[nth]), NULL, trataResp,str[nth]);
//		nth++;
//
//		if(nth == MAXTHREADS){
//			for(nth=0 ; nth < MAXTHREADS ; nth++){
//				pthread_join(th[nth],NULL); //pensaar em receber a parte de ret
//				free(str[nth]);
//			}
//			nth=0;
//		}
//
//	}while(1);
//
//
//
//
//	pthread_exit(NULL);
//
//	remove("requests");
//}
//
//void * trataResp( void* str){
//
//	char * req = (char*) str;
//	int ret, id;
//	char resp[128];
//
//	pthread_mutex_lock(&mlista);
//	ret = addCliente(req,"1234",&clientes);
//	pthread_mutex_unlock(&mlista);
//
//	sscanf(req,"%d",&id);
//	sprintf(resp,"%d OK\n",id);
//
//	ret = rand()%3+2;
//	sleep(ret);
//	printf("sleep=%d; ",ret);
//
//	usleep(500);
//	ret =writeFifo(FIFO_ANS,resp);
//	//if(!ret)
//		printf("ret=%d a tentar a por a resposta: %s",ret,resp);
//
//	return NULL;
//
//}
//
//
//
