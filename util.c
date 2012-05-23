#include "util.h"

bool login(unsigned int numconta,char pin[4],Cliente * cliente){

    bool result = false;
    printf("login numconta*: %u\n",cliente->numconta);
    printf("login pin*: %s\n",cliente->pin);
    printf("login numconta: %u\n",numconta);
    printf("login pin: %s\n",pin);

    if(cliente->numconta == numconta && strcmp(cliente->pin,pin) == 0)
    {
        printf("cliente %s\n fez login",cliente->nome);
        result = true;
    }

    return result;

}


unsigned int addCliente(char nome[20],char pin[4],ListaCliente* lista){
    //aqui
    ultimoNumconta = ultimoNumconta + 1;
    //end aqui
    Cliente *novoCliente;
    ListaCliente* listaNova = (ListaCliente*) malloc(sizeof(ListaCliente));
    novoCliente = &(listaNova->cliente);//e como se fosse um atalho, qualquer alteracao a novoCliente afecta o cliente de listaNova


    while(lista != NULL)
    {
        if(lista->next == NULL)
        {
            break;
        }

        if(lista->next !=NULL)
        {
            lista = lista->next;
        }

    }

    strcpy (novoCliente->nome,nome);
    //novoCliente->nome = nome;

    //aqui
    //novoCliente->numconta = ultimoNumconta+1;
    novoCliente->numconta = ultimoNumconta;
    //end aqui

    strcpy (novoCliente->pin,pin);
    //novoCliente->pin = pin;
    novoCliente->saldo = 0;

    //listaNova->cliente = novoCliente;
    listaNova->next = NULL;
    listaNova->pid = 0;
    listaNova->prev = lista;


    lista->next = listaNova;

    //printf("novoCliente->numconta: %u\n", novoCliente->numconta);

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


    if(lista->cliente.numconta != numconta)
    {
        return 0;
    }else {

        lista->prev->next = lista->next;
        if(lista->next != NULL)
            lista->next->prev = lista->prev;

        free(lista);

        return numconta;
    }
}

/*


lclient = searchCliente(30,&lista);

searchcliente(1,lclient);




*/
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


    //printf("antes: %07u\n",cliente->numconta);
    sprintf (nconta,"%07u", cliente->numconta);
    //printf("depois: %s\n",nconta);

    //sprintf(str,"%s %s     %s     %d",nconta,"nel","1234",12345);
    sprintf(str,"%s %s     %s     %d",nconta,cliente->nome,cliente->pin,cliente->saldo);

    //aqui
    //cliente->numconta =12345;
    //end aqui
    return str;




}

//listar todos os clientes e ir devolvendo strings obtidas pelos tostrings de cada cliente, a cada iteracao a listaCliente e actualizada
ListaCliente * listarClientes(ListaCliente * lista,char* str){

    //abrir o fifo
    //int resultOpen;
    //O_WRONLY

    //resultOpen = open (const char *filename, int mode [, int permissions]);

    //usar a tostring
    //ListaCliente* listaResult;

    if(lista == NULL)
    {
        return NULL;
    }else

    {
        //listaResult = lista;
        //printf("hello\n");
        strcpy(str,clienteToString(&(lista->cliente)));
        lista = lista->next;
        return lista;
    }




}

//criar lista e o admin com numconta = 0
int createListclient(ListaCliente * lista){

    ultimoNumconta = 0;

    lista->cliente.numconta = ultimoNumconta;
    lista->cliente.saldo = 0;
    strcpy(lista->cliente.nome,"admin");
    strcpy(lista->cliente.pin,"1234");

    lista->prev = NULL;
    lista->next = NULL;

    return ultimoNumconta;
}




//verificar se existe saldo suficiente
//verificar o login
//retirar o valor e fazer return true
bool levantarDinheiro(unsigned int numconta,char pinconta[4], int valor,ListaCliente* lista){
    bool result = false;
    bool resultLogin = false;
    ListaCliente* lista1;
    lista1 = searchCliente(numconta,lista);

    printf("lista1 cliente numconta: %u\n",lista1->cliente.numconta);
    printf("lista1 cliente pin: %s\n",lista1->cliente.pin);

    if(lista1 == NULL)
    {
        printf("Erro ao levantar, cliente nao existe\n");
        result = false;
    }else
    {
        resultLogin = login(numconta,pinconta,&(lista1->cliente));
        if(resultLogin == true)
        {
            if(lista1->cliente.saldo >= valor)
            {
                lista1->cliente.saldo = lista1->cliente.saldo - valor;
                printf("ocorreu levantamento\n");
                result = true;
            }else
            {
                printf("Nao tem saldo suficiente para o levantamento\n");
                result = false;
            }

        }else
        {
            printf("Erro levantamento, numconta/pin errados\n");
            result = false;
        }

    }

    return result;

}

bool depositarDinheiro(unsigned int numconta,char pinconta[4],int valor,ListaCliente * lista){
    bool result = false;
    bool resultLogin = false;
    ListaCliente* lista1;
    lista1 = searchCliente(numconta,lista);

    printf("lista1 cliente numconta: %u\n",lista1->cliente.numconta);
    printf("lista1 cliente pin: %s\n",lista1->cliente.pin);

    if(lista1 == NULL)
    {
        printf("Erro ao depositar, cliente nao existe\n");
        result = false;
    }else
    {
        resultLogin = login(numconta,pinconta,&(lista1->cliente));
        if(resultLogin == true)
        {
            lista1->cliente.saldo = lista1->cliente.saldo + valor;
            printf("ocorreu deposito\n");
            result = true;
        }else
        {
            printf("Erro deposito, numconta/pin errados\n");
            result = false;
        }

    }

    return result;

}


bool transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor,ListaCliente * lista){
    bool resultLogin = false;
    bool result = false;
    ListaCliente * lista1;
    ListaCliente * lista2;

    lista1 = searchCliente(numconta,lista);
    lista2 = searchCliente(numconta2,lista);

    if(lista1 != NULL && lista2 != NULL)
    {
        resultLogin = login(numconta,pinconta,&(lista1->cliente));
        if(resultLogin == true)
        {
            lista1->cliente.saldo = lista1->cliente.saldo - valor;
            printf("Transferencia tirou dinheiro\n");
            lista2->cliente.saldo = lista2->cliente.saldo + valor;
            printf("Transferencia colocou dinheiro\n");
            result = true;
        }else
        {
            printf("Transferencia nao tirou dinheiro, numconta/pin errados\n");
            result = false;
        }
    }else
    {
        printf("Transferencia erro, um dos clientes nao existe\n");
        result = false;
    }
    return result;


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
	//tem a ver com o TIMEOUT
	fd_set set;
	struct timeval tmout;


	//erro
	if( fifo == -1)
		return NULL;

	if(timeout){

		FD_ZERO(&set);
		FD_SET(fifo, &set);

		tmout.tv_sec = timeout;
		tmout.tv_usec = 0;

		ret = select(fifo + 1, &set, NULL, NULL, &tmout);
		if(ret <= 0) {
			if(ret==-1)
				perror("SELECT");
			else if( ret == 0)
				puts("TIMOUT");

			close(fifo);
			return NULL;
		}
	}


	ret = read(fifo, buff, 1024);




	close(fifo);


	printf("readFIFO ret = %d\n",ret);


	if(ret < 0) {
			printf("ERRRROOOO %s",strerror(errno));

		return NULL;
	}

	return buff;
}

int writeFifo(char* path, char* buff){

	int fifo = open(path, O_WRONLY | O_APPEND );

	int len = strlen(buff);

	int wr, retry = 3;

	while( (wr=write(fifo, buff, len)) == -1){
		if(retry--){
			printf("erro: %s\n",strerror(errno));
			break;
		}
		usleep(250 * 1000);
	}

	close(fifo);
	return wr;
}

int listToArray(ListaCliente* lcliente, Cliente **cli){
	int ret, i = 0;

	while(lcliente != NULL && i < MAXCLIENTES){
		cli[i++] = &(lcliente->cliente);
		lcliente = lcliente->next;
		//printf("cli[%d]=%d\t",i-1,cli[i-1]->numconta);
	}

	ret = i;
	while(i < MAXCLIENTES)
		cli[i++] = NULL;

	return ret;
}
int clienteComparator ( const void * cli1, const void * cli2 ){
	/*
	 * *(Cliente *) elem1 == Cliente *
	 * *(*(Cliente *)) elem1 == Cliente
	 */

	Cliente * tcl1 =*(Cliente **) cli1;
	Cliente * tcl2 =*(Cliente **) cli2;

	unsigned int ncli1 = tcl1->numconta;
	unsigned int ncli2 = tcl2->numconta;


	return (int) (ncli1 - ncli2);

}

void sortArrayCliente( Cliente **cli, int ncl){

	qsort(cli,ncl,sizeof(Cliente*),clienteComparator);

}

Cliente* bsearchClient(Cliente **cli,int ncl, unsigned int nconta) {

	Cliente *cl = calloc(1,sizeof(Cliente*));
	Cliente **res;
	cl->numconta = nconta;

	res = bsearch(&cl,cli,ncl,sizeof(Cliente**),clienteComparator);
	free(cl);

	if(res != NULL)
		return *res;
	else
		return NULL;

}
