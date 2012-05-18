#include "util.h"

Cliente *  login(unsigned int numconta,char pin[4],ListaCliente* lista){

    bool encontrou = false;
    Cliente* clienteA;
    while(lista != NULL)
    {
        //percorre a lista de clientes a procura de um client com numconta e pin iguais aos introduzidos

        //se encontrar coloca enontrou = true actualiza o valor de clienteA e salta fora do ciclo com o break

        if(lista->cliente.numconta == numconta && strcmp(lista->cliente.pin,pin) == 0)
        {
            printf("login realizado com sucesso\n");
            encontrou =  true;
            clienteA = &(lista->cliente);
            break;
        }
        //lista = (*lista).next; ==> lista = lista->next
        lista = lista->next;
    }

    //quando salta fora do ciclo verifica a variavel 'encontrou' para verificar se pode retornar o cliente ou nao
    if(encontrou == true)
    {
        return clienteA;
    }else
        return NULL;


}


unsigned int addCliente(char nome[20],char pin[4],ListaCliente* lista,unsigned int ultimoNumconta){

    Cliente *novoCliente;
    ListaCliente* listaNova = (ListaCliente*) malloc(sizeof(ListaCliente));
    novoCliente = &(listaNova->cliente);//e como se fosse um atalho, qualquer alteracao a novoCliente afecta o cliente de listaNova

    if(ultimoNumconta >= 10000000)
        return 0;

    while(lista != NULL)
    {
        if(lista->next == NULL)
            break;

        lista = lista->next;
    }


    strcpy (novoCliente->nome,nome);
    //novoCliente->nome = nome;
    novoCliente->numconta = ultimoNumconta+1;
    strcpy (novoCliente->pin,pin);
    //novoCliente->pin = pin;
    novoCliente->saldo = 0;

    //listaNova->cliente = novoCliente;
    listaNova->next = NULL;
    listaNova->pid = 0;
    listaNova->prev = lista;

    lista->next = listaNova;



    return novoCliente->numconta;


}

unsigned int removeCliente(unsigned int numconta,ListaCliente* lista){

    while(lista->cliente.numconta != numconta)
    {

        lista = lista->next;

        if(lista == NULL)
        {
            break;
        }
    }

    if(lista == NULL)
    {
        return 0;
    }else {

        lista->prev->next = lista->next;
        lista->next->prev = lista->prev;
        free(lista);

        return numconta;
    }
}


ListaCliente * searchCliente(unsigned int numconta,ListaCliente* lista){

    //ListaCliente* listaclient;

    while(lista->cliente.numconta != numconta)
    {


        lista = lista->next;

        if(lista == NULL)
        {

                break;
        }

    }

    if(lista == NULL)
    {
        return NULL;
    }else {

        return lista;
    }



}

//transforma os dados do cliente numa string
char * clienteToString(Cliente* cliente){

    char nconta[8];
    char* str = (char *) malloc( sizeof(char)*100  );
    if(str == NULL) {
        puts("STR = NULL");
        return NULL;
    }


    printf("antes: %07u\n",cliente->numconta);
    sprintf (nconta,"%07u", cliente->numconta);
    printf("depois: %s\n",nconta);

    //sprintf(str,"%s %s     %s     %d",nconta,"nel","1234",12345);
    sprintf(str,"%s %s     %s     %d",nconta,cliente->nome,cliente->pin,cliente->saldo);

    cliente->numconta =12345;
    return str;




}


void sigpipe_handler(int signo){
	printf("SIGPIPE COUGHT\n");
}


int createFifo(char* ff){
	int ret;
	// S_IRWXU | S_IRWXO = dar todas as permissoes ao ficheiro
	ret = mkfifo(ff, S_IRWXU | S_IRWXO);
//	signal(SIGPIPE, sigpipe_handler);

	if(ret < 0){
		remove(ff);
		return createFifo(ff);
	}


	return ret;
}

char* readFifo(char* path, int timeout, char* buff){
	int fifo = open(path, O_RDWR );
	int ret, start,end=0;

	start = time(NULL);

	//erro
	if( fifo == -1)
		return NULL;

	do{
		ret = read(fifo, buff, 16);
		if(ret==-1)
			usleep(1 * 1000);
		end = time(NULL);
	}while(ret == -1 && (end - start) != timeout );
	printf("ret=%d\n", ret);


	close(fifo);

	if(ret < 0) {
		//if( errno != EINTR)
			printf("ERRRROOOO %s",strerror(errno));

		return NULL;
	}

	//printf("%u stop alarm\n",alarm(0));
	//wait();

	return buff;
}

int writeFifo(char* path, char* buff){

	int fifo = open(path, O_RDWR | O_APPEND );

	int len = strlen(buff);

	int wr;
	printf("fifo erro: %s\n",strerror(errno));
	printf("fifo = %d; path = %s\n",fifo, path);

	while( (wr=write(fifo, buff, len)) == -1){
		printf("erro: %s\n",strerror(errno));
		usleep(250 * 1000);
	}

	close(fifo);
	return wr;
}


