#include "util.h"

bool login(unsigned int numconta,char pin[4],Cliente * cliente){

    bool result = false;

    if(cliente->numconta == numconta && strcmp(cliente->pin,pin) == 0)
    {
        result = true;
    }

    return result;

}

unsigned int addCliente(char nome[20],char pin[4],arrCliente clienteArray){

    ultimoNumconta = ultimoNumconta + 1;
    int i = 0;

    Cliente *novoCliente = (Cliente *) calloc(1,sizeof(Cliente));

    strcpy(novoCliente->nome,nome);
    novoCliente->numconta = ultimoNumconta;
    strcpy (novoCliente->pin,pin);
    novoCliente->saldo = 0;


    while(clienteArray[i] != NULL && i < MAX_NUM_CLIENTES)
        i++;

    if(i < MAX_NUM_CLIENTES)
        clienteArray[i] = novoCliente;
    else
    {
        free(novoCliente);
        return 0;
    }


    return ultimoNumconta;



}



unsigned int removeCliente(unsigned int numconta,arrCliente clienteArray){

    int i = 0;
    int k = 0;
    int acum = 0;
    Cliente * cli;
    Cliente * subt;

    if(numconta == 0)
    {
        return 0;
    }

    for(k = 0; k < MAX_NUM_CLIENTES;k++)
        if(clienteArray[k] == NULL)
            break;


    cli = bsearchClient(clienteArray, k, numconta);

    free(cli);

    subt = clienteArray[k-1];
    clienteArray[k-1] = NULL;

    for(i = k-2; i >= 0;i--)
    	if(clienteArray[i] == cli)
    		clienteArray[i] = subt;
    k--;

    sortArrayCliente(clienteArray,k);

    return numconta;
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

char * clienteToString(Cliente* cliente){

    char nconta[8];
    char* str = (char *) malloc( sizeof(char)*100  );
    if(str == NULL) {
        puts("STR = NULL");
        return NULL;
    }

    if(cliente == NULL)
    {
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


    sscanf (str,"%u %s %s %lf",&numconta,nome,pin,&saldo);


    strcpy(clienteA->nome,nome);
    clienteA->numconta = numconta;
    strcpy(clienteA->pin,pin);
    clienteA->saldo = saldo;






    return clienteA;
}


arrCliente listarClientes(arrCliente arrayCliente,char* str,int * i)
{

    int k =0;

    if(arrayCliente == NULL)
		return NULL;

    if(*arrayCliente == NULL)
        return NULL;

    if(str == NULL)
        return NULL;

    if(i == NULL)
        i = &k;

    else
       *i += 1;

    if(arrayCliente != NULL && *i < MAX_NUM_CLIENTES)
    {
        strcpy(str,clienteToString(arrayCliente[0]));
        return &(arrayCliente[1]);

    }else
        return NULL;
}



int createArrayclient(arrCliente array){

    Cliente * clienteA = (Cliente *) calloc(1,sizeof(Cliente));
    ultimoNumconta = 0;
    int i = 0;

    clienteA->numconta = ultimoNumconta;
    clienteA->saldo = 0;
    strcpy(clienteA->nome,"admin");
    strcpy(clienteA->pin,"1234");

    array[i] = clienteA;

    while(i++ < MAX_NUM_CLIENTES)
    {
        array[i] = NULL;
    }

    return ultimoNumconta;


}

bool levantarDinheiro(unsigned int numconta,char pinconta[4],double valor,arrCliente clientesArray){
    bool result = false;
    bool resultLogin = false;
    int k;
    Cliente * clienteA;

    for(k = 0; k < MAX_NUM_CLIENTES;k++)
        if(clientesArray[k] == NULL)
            break;


    clienteA =  bsearchClient(clientesArray,k, numconta);


    if(clienteA == NULL)
        return false;
    else
    {
        resultLogin = login(numconta,pinconta,clienteA);
        if(resultLogin == true)
        {
            if(clienteA->saldo >= valor)
            {
                clienteA->saldo = clienteA->saldo - valor;
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

bool depositarDinheiro(unsigned int numconta,char pinconta[4],double valor,arrCliente clientesArray){
    bool result = false;
    bool resultLogin = false;
    int k;
    Cliente * clienteA;

    for(k = 0; k < MAX_NUM_CLIENTES;k++)
        if(clientesArray[k] == NULL)
            break;

    clienteA =  bsearchClient(clientesArray,k, numconta);

    if(clienteA == NULL)
        return false;
    else
    {
        resultLogin = login(numconta,pinconta,clienteA);
        if(resultLogin == true)
        {
            clienteA->saldo = clienteA->saldo + valor;
            result = true;
        }else
        {
            result = false;
        }
    }


    return result;


}

bool transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor,arrCliente clientesArray){
    int k;
    bool resultLogin = false;
    bool result = false;
    Cliente * clienteA;
    Cliente * clienteB;

    for(k = 0; k < MAX_NUM_CLIENTES;k++)
        if(clientesArray[k] == NULL)
            break;


    clienteA = bsearchClient(clientesArray,k,numconta);
    clienteB = bsearchClient(clientesArray,k,numconta2);


    if(clienteA != NULL && clienteB != NULL)
    {
        resultLogin = login(numconta,pinconta,clienteA);
        if(resultLogin == true)
        {
            if(clienteA->saldo >= valor)
            {
                clienteA->saldo = clienteA->saldo - valor;
                clienteB->saldo = clienteB->saldo + valor;
                result = true;
            }else
            {
                result = false;
            }

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


double consultarSaldo(unsigned int numconta,char pinconta[4],arrCliente clientesArray){
    int k;
    double result;
    Cliente * clienteA;
    bool resultLogin;

    for(k = 0; k < MAX_NUM_CLIENTES;k++)
        if(clientesArray[k] == NULL)
            break;

    clienteA = bsearchClient(clientesArray,k,numconta);

    if(clienteA != NULL)
    {
        resultLogin = login(numconta,pinconta,clienteA);
        if(resultLogin == true)
        {
            result = clienteA->saldo;
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

bool escreveAcounts(arrCliente clientesArray){
    int k;
    int i = 0;
    bool result = false;
    FILE *file;
    char str[128];
    arrCliente temp;

	if ( (file = fopen ( "accounts.txt", "r" ) ) != NULL )
	{

        remove("accounts.txt");
        file = fopen("accounts.txt", "w");

	}
	else {

		file = fopen("accounts.txt", "w");
	}


    fprintf(file,"%07u\n",ultimoNumconta);

    k = 0;
    temp = clientesArray;

    while(temp != NULL)
    {
        temp = listarClientes(temp,str,&k);
        if(temp != NULL)
            fprintf(file,"%s\n",str);

    }




    result = true;
	fclose(file);
	return result;




}

bool lerAcounts(arrCliente clientesArray){
    int i = 0;
    int k;
    char mystring [100];
    bool result = true;
    Cliente *  clienteA = (Cliente * ) malloc(sizeof(Cliente));
    FILE *file;

	if ( (file = fopen ( "accounts.txt", "r" ) ) != NULL )
	{
	    fgets (mystring , 100 , file);
	    sscanf(mystring,"%u",&ultimoNumconta);

        while(!feof(file))
        {
            fgets (mystring , 100 , file);

            clienteA = stringToCliente(mystring);

            clientesArray[i] = clienteA;

            ++i;

        }

        for(k = i; k < MAX_NUM_CLIENTES;k++)
            clientesArray[i] = NULL;

        fclose(file);
	}
	else {

		result = false;

	}


    return result;



}

bool iniciaLog(){

    bool result = false;
    FILE *file;

	if ( (file = fopen ( "logfile.txt", "r" ) ) != NULL )
	{
         fclose(file);
         return false;
	}
	else {

		file = fopen("logfile.txt", "a+");

	}


	fprintf(file,"   DATA          HORA      PROGRAMA      OPERACAO\n");
	result = true;
	fclose(file);

	return result;




}


bool actualizaLog(Request * request,Response * response){
    bool result = false;
    char programa[128];
    char operacao[128];
    char mensagem[128];
    pid_t pid;
    FILE *file;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);



    iniciaLog();

    file = fopen("logfile.txt", "a+");

    if(response == NULL)
    {
        if(request->user == ADMIN)
        {
            strcpy(programa,"ADMIN");
        }else

        if(request->user == CLIENTE)
        {
            strcpy(programa,"CLIENTE");
        }else

        if(request->user == SERVER)
        {
            strcpy(programa,"SERVER");
        }

        if(request->tipo == CONSULTAR)
        {
            strcpy(operacao,"CONSULTAR");
        }else

        if(request->tipo == LEVANTAR)
        {
            strcpy(operacao,"LEVANTAR");
        }else

        if(request->tipo == DEPOSITAR)
        {
            strcpy(operacao,"DEPOSITAR");
        }else

        if(request->tipo == TRANSFERENCIA)
        {
            strcpy(operacao,"TRANSFERENCIA");
        }else

        if(request->tipo == ADICIONAR)
        {
            strcpy(operacao,"ADICIONAR");
        }else

        if(request->tipo == REMOVER)
        {
            strcpy(operacao,"REMOVER");
        }else

         if(request->tipo == LISTAR)
        {
            strcpy(operacao,"LISTAR");
        }else

         if(request->tipo == INVALID)
        {
            strcpy(operacao,"INVALID");
            result = false;
        }

        pid = request->pid_cli;
        fprintf(file,"   %02d-%02d-%02d     %02d:%02d:%02d   %s Cliente(pid=%d)  %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,programa,(int)pid,operacao);
        result = true;
    }else

    {
        if(strcmp(response->status,"ERRO") == 0)
        {
            strcpy(mensagem,"ERRO operacao");
            pid = request->pid_cli;
            strcpy(programa,"SERVER");
            strcpy(operacao,response->msg);
            fprintf(file,"   %02d-%02d-%02d     %02d:%02d:%02d   %s Cliente(pid=%d)  %s %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,programa,(int)pid,operacao,mensagem);
            result = false;
        }else
        {
            strcpy(mensagem,"OK");
            pid = request->pid_cli;
            strcpy(programa,"SERVER");
            strcpy(operacao,mensagem);
            fprintf(file,"   %02d-%02d-%02d     %02d:%02d:%02d   %s Cliente(pid=%d)  %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,programa,(int)pid,operacao);
            result = true;
        }

    }



    fclose(file);
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

	if( *(Cliente **) cli1 == NULL )
		return 1;

	if( *(Cliente **) cli2 == NULL )
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
	int i=0;

	strcpy(req->pedidoOriginal,line);

	//pid
	ch = strtok(line," ");

	sscanf(ch,"%d",&i);
	req->pid_cli = i;
	i= 0;

	//numConta
	ch = strtok(NULL," ");
	sscanf(ch,"%u",&req->numConta);

	//pin
	ch = strtok(NULL," ");
	sscanf(ch,"%s",req->pin);

	//tipo
	ch = strtok(NULL," ");
	sscanf(ch,"%s",tipo);


	if(strcmp(tipo,"CONSULTAR") == 0){
		req->tipo = CONSULTAR;
	} else

	if(strcmp(tipo,"LEVANTAR") == 0) {
		req->tipo = LEVANTAR;

		//valor
		ch = strtok(NULL," ");
		sscanf(ch,"%lf",&req->valor);
	} else

	if(strcmp(tipo,"DEPOSITAR") == 0) {
		req->tipo = DEPOSITAR;

		//valor
		ch = strtok(NULL," ");
		sscanf(ch,"%lf",&req->valor);
		printf("valor a depositar: %lf\n",req->valor);
	} else

	if(strcmp(tipo,"TRANSFERENCIA") == 0) {
		req->tipo = TRANSFERENCIA;

		//valor
		ch = strtok(NULL," ");
		sscanf(ch,"%lf",&req->valor);

		//para onde
		ch = strtok(NULL," ");
		sscanf(ch,"%u",&req->numConta2);

	} else
	if(strcmp(tipo,"ADICIONAR") == 0) {

		req->tipo = ADICIONAR;

		//nome
		ch = strtok(NULL," ");
		sscanf(ch,"%s",req->nome);

		//pin
		ch = strtok(NULL," ");
		sscanf(ch,"%s",req->pin2);

	} else
	if(strcmp(tipo,"REMOVER") == 0) {

		req->tipo = REMOVER;

		//numconta2
		ch = strtok(NULL," ");
		sscanf(ch,"%u",&req->numConta2);

	} else
	if(strcmp(tipo,"LISTAR") == 0) {
		req->tipo = LISTAR;
	} else{
		puts("ERRO NO PARSE");
		return NULL;
	}

	actualizaLog(req,NULL);
	return req;

}

Response * processRequest(Request * request, arrCliente lista){
	Response * response = (Response *) calloc(1, sizeof(Response) );

	switch(request->tipo ){

			case CONSULTAR:
				request->user = CLIENTE;
				request->valor = consultarSaldo(request->numConta,request->pin, lista );
				if( request->valor < 0) {
					sprintf(response->respOriginal, "ERROR Wrong Password/username.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Wrong Password/username.\n");
				} else {

					sprintf(response->respOriginal, "OK Saldo: %.2lf\n",request->valor);
					sprintf(response->status, "OK");
					sprintf(response->msg, "Saldo: %.2lf\n",request->valor);
				}


			 break;

			case LEVANTAR:
				request->user = CLIENTE;
				if( levantarDinheiro(request->numConta,request->pin,request->valor,lista) ){
					sprintf(response->respOriginal, "OK Operacao bem sucedida.\n");
					sprintf(response->status, "OK");
					sprintf(response->msg, "Operacao bem sucedida.\n");
				} else {
					sprintf(response->respOriginal, "ERROR Sem fundos Suficientes ou Wrong Password/username.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Sem fundos Suficientes ou Wrong Password/username.\n");
				}


			 break;

			case DEPOSITAR:
				request->user = CLIENTE;
				if(depositarDinheiro(request->numConta,request->pin,request->valor,lista)){
					sprintf(response->respOriginal, "OK Operacao bem sucedida.\n");
					sprintf(response->status, "OK");
					sprintf(response->msg, "Operacao bem sucedida.\n");
				} else {
					sprintf(response->respOriginal, "ERROR Wrong Password/username.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Wrong Password/username.\n");
				}

			 break;

			case TRANSFERENCIA:
				request->user = CLIENTE;
				if( transferirDinheiro(request->numConta,request->pin,request->numConta2, request->valor,lista) ){
					sprintf(response->respOriginal, "OK Operacao bem sucedida.\n");
					sprintf(response->status, "OK");
					sprintf(response->msg, "Operacao bem sucedida.\n");
				} else {
					sprintf(response->respOriginal, "ERROR Sem fundos Suficientes ou Wrong Password/username.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Sem fundos Suficientes ou Wrong Password/username.\n");
				}

			 break;

			 // so para admin
			case ADICIONAR:
				request->user = ADMIN;
				if(request->numConta == 0 && login(request->numConta,request->pin,lista[0]) ){

					request->numConta2 = addCliente(request->nome,request->pin2,lista);
					sprintf(response->respOriginal, "OK Atribuido com o numero de conta %u.\n",request->numConta2);
					sprintf(response->status, "OK");
					sprintf(response->msg, "Atribuido com o numero de conta %u.\n",request->numConta2);

				} else {
					sprintf(response->respOriginal, "ERROR Nao tem permicoes para esta operacao.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Nao tem permicoes para esta operacao.\n");
				}


			 break;
			 // so para admin
			case REMOVER:
				request->user = ADMIN;
				if(request->numConta == 0 && login(request->numConta,request->pin,lista[0])){
					request->numConta2 = removeCliente(request->numConta2 ,lista);
					sprintf(response->respOriginal, "OK Operacao bem sucedida.\n");
					sprintf(response->status, "OK");
					sprintf(response->msg, "Operacao bem sucedida.\n");

				} else {
					sprintf(response->respOriginal, "ERROR Nao tem permicoes para esta operacao.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Nao tem permicoes para esta operacao.\n");
				}


			 break;
			 // so para admin
			case LISTAR:
				request->user = ADMIN;
				if(request->numConta == 0 && login(request->numConta,request->pin,lista[0])){
					sprintf(response->respOriginal, "OK Lista em seguida.\n");
					sprintf(response->status, "OK");
					sprintf(response->msg, "Lista em seguida.\n");

				} else {
					sprintf(response->respOriginal, "ERROR Nao tem permicoes para esta operacao.\n");
					sprintf(response->status, "ERROR");
					sprintf(response->msg, "Nao tem permicoes para esta operacao.\n");
				}


			 break;
		}

	actualizaLog(request,response);

	return response;
}

