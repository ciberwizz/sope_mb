#include "util.h"

Cliente *  login(unsigned int numconta,char pin[4],ListaCliente* lista){

    bool encontrou = false;
    Cliente* clienteA;
    while(lista != NULL)
    {
        //percorre a lista de clientes a procura de um client com numconta e pin iguais aos introduzidos

        //se encontrar coloca enontrou = true actualiza o valor de clienteA e salta fora do ciclo com o break

        if(lista == NULL)
        {
            printf("conta nao existe\n");
            encontrou = false;
            break;
        }

        if(lista->cliente.numconta == numconta && strcmp(lista->cliente.pin,pin) == 0)
        {
            printf("login realizado com sucesso\n");
            encontrou =  true;
            clienteA = &(lista->cliente);
            //aqui
            clienteA->logado = true;
            //end aqui
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
    {
        printf("login nao efecutado\n");
        return NULL;
    }



}


unsigned int addCliente(char nome[20],char pin[4],ListaCliente* lista/*,unsigned int ultimoNumconta*/){
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

    //aqui
    novoCliente->logado = false;
    //end aqui

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
bool levantarDinheiro(unsigned int numconta/*,char pinconta[4]*/, int valor,ListaCliente* lista){
    bool result = false;
    //ListaCliente* lista;

    while(lista != NULL)
    {
        if(lista == NULL)
        {
            printf("chegou ao fim da lista e nao encontrou o cliente\n");
            result =  false;
            break;
        }

        if(lista->cliente.numconta == numconta)
        {
            if(lista->cliente.logado == true)
            {
                if(lista->cliente.saldo >= valor)
                {
                    lista->cliente.saldo = lista->cliente.saldo - valor;
                    result = true;
                    printf("dinheiro levantado\n");
                    break;
                }else
                {
                 printf("Nao tem saldo suficiente\n");
                 break;
                }

            }else
            {
                printf("Nao esta logado\n");
                break;
            }

        }
        else
        {
            lista = lista->next;
        }
    }

    return result;
}

bool depositarDinheiro(unsigned int numconta/*,char pinconta[4]*/,int valor,ListaCliente * lista){
    bool result = false;
    //ListaCliente* lista;

    printf("hello1\n");
    while(lista != NULL)
    {
        printf("hello2\n");
        printf("numconta: %u\n",lista->cliente.numconta);
        printf("logado: %s",(lista->cliente.logado)?"true":"false");
        if(lista == NULL)
        {
            printf("hello3\n");
            printf("chegou ao fim da lista e nao encontrou o cliente\n");
            result =  false;
            break;
        }

        if(lista->cliente.numconta == numconta)
        {
            printf("econtrou a conta\n");
            if(lista->cliente.logado == true)
            {
                printf("esta logado\n");
                lista->cliente.saldo = lista->cliente.saldo + valor;
                result = true;
                printf("dinheiro depositado\n");
                break;
            }else
            {
                    printf("Nao esta logado\n");
                    result = false;
                    break;
            }

        }
        else
        {
            printf("Proximo\n");
            lista = lista->next;
        }
    }

    return result;

}


bool transferirDinheiro(unsigned int numconta/*,char pinconta[4]*/,unsigned int numconta2,int valor,ListaCliente * lista){
    //ListaCliente* lista;
    ListaCliente* ini;

    ListaCliente* lista1;
    ListaCliente* lista2;

    Cliente* cliente1;
    Cliente* cliente2;
    bool result1 = false;
    bool result2 = false;
    bool final = false;

    ini = lista;

    lista1 = searchCliente(numconta,lista);
    lista = ini;//para ficar a apontar outra vez para o inicio
    lista2 = searchCliente(numconta2,lista);
    lista = ini;//para ficar a apontar outra vez para o inicio

    if(lista1 != NULL && lista2 != NULL)
    {
        while(lista != NULL)
        {
            if(lista == NULL)
            {
                printf("chegou ao fim lista1\n");
                break;
            }else
            if(lista->cliente.numconta == numconta)
            {
                if(lista->cliente.logado == true)
                {
                    if(lista->cliente.saldo >= valor)
                    {
                        lista->cliente.saldo = lista->cliente.saldo - valor;
                        printf("foi retirado dinheiro ao cliente1\n");
                        result1 = true;
                        break;
                    }else
                    {
                        printf("cliente1 nao tem saldo suficiente\n");
                        break;
                    }

                }else
                {
                        printf("cliente1 nao esta logado");
                        break;
                }

            }else
            lista = lista->next;
        }

        lista = ini;

        while(lista != NULL)
        {
            if(lista == NULL)
            {
                printf("chegou ao fim lista2\n");
                break;
            }else
            if(lista->cliente.numconta == numconta2)
            {
                if(result1 == true)
                {
                    lista->cliente.saldo = lista->cliente.saldo + valor;
                    printf("foi depositado dinheiro no cliente2\n");
                    result2 = true;
                    break;
                }else
                {
                    printf("o cliente1 nao esta logado e/ou nao tem saldo suficiente\n");
                    result2 = false;
                    break;
                }

            }else
            lista = lista->next;
        }




    }

     if(result1 == true && result2 == true)
        {
            final = true;
        }

        return final;






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

//	do{
		ret = read(fifo, buff, 1024);
/*		if(ret==-1)
			usleep(1 * 1000);
		end = time(NULL);
	}while(ret == -1 && (end - start) != timeout );
printf("ret=%d\n", ret);*/


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

	int fifo = open(path, O_WRONLY | O_APPEND );

	int len = strlen(buff);

	int wr;

	while( (wr=write(fifo, buff, len)) == -1){
		printf("erro: %s\n",strerror(errno));
		usleep(250 * 1000);
	}

	close(fifo);
	return wr;
}


