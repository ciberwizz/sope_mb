#include "util.h"
#include <stdbool.h>
#include <pthread.h>

/*
 * done - verifica q fifo "requests" existe
 * done - cria fifo para receber a resposta do server
 * doen - escreve para la 1000 mississipi open and close
 * - thread espera resposta a cada missisipi
 */


#define PEDIDOS 10

bool pedidos[PEDIDOS];

void *trataResp( void*);
int main() {
	pthread_t reader;
	int ff_req,ff_ans;
	bool ok = false;
	int i;

	char str[1024];

	ff_req = open(FIFO_REQ,O_RDONLY);
	if(ff_req == -1){
		perror("FIFO requests not found");
		exit(EXIT_FAILURE);
	} else close(ff_req);


	//ini do array pedidos
	for(i = 0; i < PEDIDOS ; i++)
		pedidos[i] = false;

	signal(SIGALRM,SIG_IGN);

	createFifo(FIFO_ANS);

	pthread_create(&reader,NULL,trataResp,NULL);


	for(i = 0 ; i < PEDIDOS; i++){
		while(sprintf(str, "%04d mississipi\n",i)<0);
		writeFifo(FIFO_REQ,str);
		usleep(1*1000); // 1msec
	}

	printf("shutdown\n");
	strcpy(str,"shutdown");
	writeFifo(FIFO_REQ,str);
//sleep(1);
//	i = pthread_tryjoin_np(&reader,NULL);
//
//	printf("ERRRO ao fazer tryjoin %d = %s",i,strerror(i));

	pthread_join(reader,NULL);

	puts("joined");
	for(i = 0 ; i < PEDIDOS ; i++)
		if(!pedidos[i]){
			printf("FOOOODDAAAA-SE ta a falso! n=%d \n",i);
			ok = false; break;
		} else ok = true;

	if(ok)
		puts("RECEBEU TUDO CRL!!!");

	remove(FIFO_ANS);


}


void *trataResp( void* a){
	int npedidos = 0;
	char buff[1024];
	int rid;
	char rstat[128];

	while(npedidos < PEDIDOS ){

		if(readFifo(FIFO_ANS,3,buff)==NULL)
			puts("TA A NULL CRL!");
		else
			printf("read=%s\n", buff);

		sscanf(buff,"%d %s\n",&rid,rstat);

		if(rid == npedidos)
			printf("npedidos=%d; rid=%d; rstat=%s;",npedidos,rid,rstat);
		//if(strcmp(rstat,"OK") == 0){
			pedidos[rid] = true;
			npedidos++;
		/*}
		else puts("DAFUQ\n");	puts("NOT OK");*/

	}

	puts("thread ended!");

	return NULL;
}









/*	// OLD TEST USER
	int i;
	char buff[1000];
	char pid[100];
	printf("whatpid? ");
	//scanf("%d",i);
	i=1234;
	sprintf(pid,"ans%d",i);

	printf("createfifo=%d\n",createFifo(pid));
	signal(SIGPIPE, sigpipe_handler);

	sleep(3);
	for(i = 0 ; i < 10000 ; i++) {
		sprintf(buff, "%04d mississippi",i);
		puts(buff);
		writeFifo(pid,buff);
		usleep(1500);
	}
	puts("a sair");
	//remove(pid);
	pause();
	return 0;


}*/
