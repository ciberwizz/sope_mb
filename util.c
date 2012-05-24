#include "util.h"

bool login(unsigned int numconta,char pin[4],Cliente * cliente){

    bool result = false;

    if(cliente->numconta == numconta && strcmp(cliente->pin,pin) == 0)
    {
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
    novoCliente->numconta = ultimoNumconta;

    strcpy (novoCliente->pin,pin);
    novoCliente->saldo = 0;

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





    if(numconta == 0)
    {
        printf("Erro, esta a tentar remover o admin\n");
        return 0;
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

ListaCliente * searchCliente(unsigned int numconta,ListaCliente* lista){

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


    sprintf (nconta,"%07u", cliente->numconta);

    sprintf(str,"%s %.20s     %s     %.2lf",nconta,cliente->nome,cliente->pin,cliente->saldo);

    return str;




}


Cliente * stringToCliente(char* str){
    Cliente * clienteA = (Cliente *) malloc(sizeof(Cliente));
    char nome[20];
    unsigned int numconta;
    char pin[5];
    double saldo;


    sscanf (str,"%u %s %s %lf",&numconta,nome,pin,&saldo);//nome e pin ja sao o endereco do primeiro elemento por isso e sem '&'

    //adicionar os valores ontidos ao cliente e retornar

    strcpy(clienteA->nome,nome);
    clienteA->numconta = numconta;
    strcpy(clienteA->pin,pin);
    clienteA->saldo = saldo;






    return clienteA;
}


//listar todos os clientes e ir devolvendo strings obtidas pelos tostrings de cada cliente, a cada iteracao a listaCliente e actualizada
ListaCliente * listarClientes(ListaCliente * lista,char* str){

    if(lista == NULL)
    {
        return NULL;
    }else

    {
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



bool levantarDinheiro(unsigned int numconta,char pinconta[4], int valor,ListaCliente* lista){
    bool result = false;
    bool resultLogin = false;
    ListaCliente* lista1;
    lista1 = searchCliente(numconta,lista);


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
                result = true;
            }else
            {
                result = false;
            }

        }else
        {
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

    if(lista1 == NULL)
    {
        result = false;
    }else
    {
        resultLogin = login(numconta,pinconta,&(lista1->cliente));
        if(resultLogin == true)
        {
            lista1->cliente.saldo = lista1->cliente.saldo + valor;
            result = true;
        }else
        {
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
            lista2->cliente.saldo = lista2->cliente.saldo + valor;
            result = true;
        }else
        {
            result = false;
        }
    }else
    {
        result = false;
    }
    return result;


}


double consultarSaldo(unsigned int numconta,char pinconta[4],ListaCliente* lista){
    double result;
    ListaCliente * lista1;
    bool resultLogin;

    lista1 = searchCliente(numconta,lista);

    if(lista1!= NULL)
    {
        resultLogin = login(numconta,pinconta,&(lista1->cliente));
        if(resultLogin == true)
        {
            result = lista1->cliente.saldo;
        }else
        {
            return -1.0;
        }
    }else
    {
        return -1.0;
    }

    return result;
}


bool escreveAcounts(ListaCliente *  lista){
    ListaCliente * listaclient;
    bool result = false;
    FILE *file;
    char str[128];

	if ( (file = fopen ( "accounts.txt", "r" ) ) != NULL )
	{

        remove("accounts.txt");
        file = fopen("accounts.txt", "w");

	}
	else {

		file = fopen("accounts.txt", "w");
	}


    //escrever na primeira linha o numconta do ultimo jogador registado
    fprintf(file,"%07u\n",ultimoNumconta);

	while(lista != NULL)
	{


	    if(lista->next == NULL)
	    {
	        listaclient = listarClientes(lista,str);
            fprintf(file,"%s",str);

	        break;
	    }

        listaclient = listarClientes(lista,str);
        fprintf(file,"%s\n",str);
        lista = lista->next;
	}

    result = true;
	fclose(file);
	return result;



}

//ignora a primeira linha pois contem o numconta do ultimo jogador registado
bool lerAcounts(ListaCliente * listaler){
    char mystring [100];
    bool result = true;
    Cliente *  clienteA = (Cliente * ) malloc(sizeof(Cliente));
    FILE *file;

	if ( (file = fopen ( "accounts.txt", "r" ) ) != NULL )
	{
	    fgets (mystring , 100 , file);//para passar a primeira linha a frente
	    sscanf(mystring,"%u",&ultimoNumconta);

        while(!feof(file))
        {
            fgets (mystring , 100 , file);
            //tratar a mystring e passar os dados stringToCliente que devolve um apontador para cliente
            clienteA = stringToCliente(mystring);

            //adicionar este cliente a lista
            strcpy(listaler->cliente.nome,clienteA->nome);
            listaler->cliente.numconta = clienteA->numconta;
            strcpy(listaler->cliente.pin,clienteA->pin);
            listaler->cliente.saldo = clienteA->saldo;

            listaler->pid = 0;

            listaler->next = (ListaCliente * ) malloc(sizeof(ListaCliente));
            listaler->next->prev = listaler;
            listaler = listaler->next;

        }
            //neste momento estou numa lista que nao tenha nada
            listaler = listaler->prev;//voltar a ultima lista que tem alguma coisa nela guardada
            free(listaler->next);//libertar a memoria usada pelo malloc
            listaler->next = NULL;//dizer que a lista a seguir a ultima lista com um cliente e vazia
	}
	else {

		result = false;

	}

    fclose(file);
    return result;

}

//cria o ficheiro com a primeira linha como data hora programa operacao
bool iniciaLog(){

    bool result = false;
    FILE *file;

	if ( (file = fopen ( "logfile.txt", "r" ) ) != NULL )
	{

	}
	else {

		file = fopen("logfile.txt", "a+");//se nao existir cria e abre para escrita com modo append

	}


	fprintf(file,"   DATA     HORA   PROGRAMA   OPERACAO\n");
	result = true;

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

	Cliente * tcl1;
	Cliente * tcl2;

	if( tcl1 == NULL )
		return 1;
	else
		if( tcl2 == NULL )
			return -1;

	tcl1 = *(Cliente **) cli1;
	tcl2 = *(Cliente **) cli2;

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

int sendRequest(Request *req ){
	char line[1024];

	req->pid_cli = getpid();

	switch(req->tipo ){

		case CONSULTAR:
		 sprintf(line,"%ld %09u %s CONSULTAR\n",(long) req->pid_cli, req->numConta, req->pin);
		 break;

		case LEVANTAR:
		 sprintf(line,"%ld %09u %s LEVANTAR %.2lf\n",(long) req->pid_cli, req->numConta, req->pin, req->valor);
		 break;

		case DEPOSITAR:
		 sprintf(line,"%ld %09u %s DEPOSITAR %.2lf\n",(long) req->pid_cli, req->numConta, req->pin, req->valor);
		 break;

		case TRANSFERENCIA:
		 sprintf(line,"%ld %09u %s TRANSFERENCIA %.2lf %09u\n",(long) req->pid_cli, req->numConta, req->pin, req->valor, req->numConta2);
		 break;

		case ADICIONAR:
		 sprintf(line,"%ld %09u %s ADICIONAR %s %s\n",(long) req->pid_cli, req->numConta, req->pin, req->nome, req->pin2);
		 break;

		case REMOVER:
		 sprintf(line,"%ld %09u %s REMOVER %09u\n",(long) req->pid_cli, req->numConta, req->pin, req->numConta2);
		 break;

		case LISTAR:
		 sprintf(line,"%ld %09u %s LISTAR\n",(long) req->pid_cli, req->numConta, req->pin);
		 break;
	}

	printf("sendRequest: %s\n",line);
	return writeFifo(FIFO_REQ,line);

}

Request * parseRequest(char *line){
	Request *req = (Request *) calloc(1,sizeof(Request));
	char * ch;
	char tipo[128];

	strcpy(req->pedidoOriginal,line);

	//pid
	ch = strtok(line," ");
	sscanf(line,"%ld",&req->pid_cli);

	//numConta
	ch = strtok(ch," ");
	sscanf(ch,"%u",&req->numConta);

	//pin
	ch = strtok(ch," ");
	sscanf(ch,"%s",req->pin);


	//tipo
	ch = strtok(ch," ");
	sscanf(ch,"%s",tipo);

	if(strcmp(tipo,"CONSULTAR") == 0){
		req->tipo = CONSULTAR;
	} else

	if(strcmp(tipo,"LEVANTAR") == 0) {
		req->tipo = LEVANTAR;

		//valor
		ch = strtok(ch," ");
		sscanf(ch,"%lf",&req->valor);
	} else

	if(strcmp(tipo,"DEPOSITAR") == 0) {
		req->tipo = DEPOSITAR;

		//valor
		ch = strtok(ch," ");
		sscanf(ch,"%lf",&req->valor);
	} else

	if(strcmp(tipo,"TRANSFERENCIA") == 0) {
		req->tipo = TRANSFERENCIA;

		//valor
		ch = strtok(ch," ");
		sscanf(ch,"%lf",&req->valor);

		//para onde
		ch = strtok(ch," ");
		sscanf(ch,"%u",&req->numConta2);

	} else
	if(strcmp(tipo,"ADICIONAR") == 0) {

		req->tipo = ADICIONAR;

		//nome
		ch = strtok(ch," ");
		sscanf(ch,"%s",req->nome);

		//pin
		ch = strtok(ch," ");
		sscanf(ch,"%s",req->pin);

	} else
	if(strcmp(tipo,"REMOVER") == 0) {

		req->tipo = REMOVER;

		//numconta2
		ch = strtok(ch," ");
		sscanf(ch,"%u",&req->numConta2);

	} else
	if(strcmp(tipo,"LISTAR") == 0) {
		req->tipo = LISTAR;
	} else

		return NULL;


	return req;

}



