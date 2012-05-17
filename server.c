#include "util.h"


// estas funcoes deviam apenas ser usadas pelo server, passar para server.c
// estas funcoes teem de retornar algo pois pode nao ser possivel concretizar a operacao
// se do servidor, nao e necessario pin..
void levantarDinheiro(unsigned int numconta,char pinconta[4],int valor);
void depositarDinheiro(unsigned int numconta,char pinconta[4],int valor);
void transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor);
void escreveAcounts(Cliente a);

//TODO logfiles

//TODO threads


int main() {

    //teste do toString
    /*
    char * a;
    Cliente cliente;
    strcpy(cliente.nome,"nelson");
    cliente.numconta = 5577756;
    printf("cliente numconta: %u\n",cliente.numconta);
    strcpy(cliente.pin,"1234");
    cliente.saldo = 123432345;
    a = clienteToString(&cliente);
    printf(a);
    free(a);
    printf("\nlast cliente numconta: %u\n",cliente.numconta);
    a = clienteToString(&cliente);
    printf("last cliente numconta: %u\n",cliente.numconta);
    printf(a);
    free(a);
    a = clienteToString(&cliente);
    printf("last cliente numconta: %u\n",cliente.numconta);
    printf(a);
    free(a);
    */

    // teste do login
    /*Cliente a;
    strcpy(a.nome,"nelson");
    a.numconta = 1;
    strcpy(a.pin,"1234");
    a.saldo = 123432345;

    Cliente b;
    strcpy(b.nome,"Manuel");
    a.numconta = 2;
    strcpy(b.pin,"1111");
    b.saldo = 1111111111;

    Cliente c;
    strcpy(c.nome,"Carla");
    a.numconta = 3;
    strcpy(c.pin,"2222");
    c.saldo = 2222222222;

    ListaCliente* listaA;
    listaA->cliente = a;
    listaA->pid = 0;

    ListaCliente* listaB;
    listaB->cliente = b;
    listaB->pid = 0;

    ListaCliente* listaC;
    listaC->cliente = c;
    listaC->pid = 0;

    listaA->prev = NULL;
    listaA->next = listaB;
    listaB->prev = listaA;
    listaB->next = listaC;
    listaC->prev = listaB;
    listaC->next = NULL;

    login(3,"2222",listaA);
    */


    //teste ao addCliente

    unsigned int ultimoNumconta = 0;

    ListaCliente lista;
    lista.cliente.nome admin //usar string copy
    lista.cliente.numconta 0
    lista.nexxt e prev = NULL

    unsigned int result;

    result = addCliente("nelson","1234",&lista,ultimoNumconta);

    if(result == 0)
        printf("Nao adicionou cliente\n");

    printf("Cliente adicionado com num conta: %u\n", result);

    return 0;
}

/*

void levantarDinheiro(unsigned int numconta,char pinconta[4], int valor){

    Clinte *utilizador;
    utilizador = ini;
    while(utilizador != NULL)
    {

        if(Cliente.numconta == numconta && Cliente.pin == pinconta)
        {
            Cliente.saldo = Cliente.saldo - valor;
            break;
        }

        utilizador = utilizador.next;
    }
}



void depositarDinheiro(unsigned int numconta,char pinconta[4],int valor){

    Clinte *utilizador;
    utilizador = ini;
    while(utilizador != NULL)
    {

        if(Cliente.numconta == numconta && Cliente.pin == pinconta)
        {
            Cliente.saldo = Cliente.saldo + valor;
            break;
        }

        utilizador = utilizador.next;
    }
}



void transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor){
    Clinte *utilizador;
    utilizador = ini;

     while(utilizador != NULL)
    {

        if(Cliente.numconta == numconta && Cliente.pin == pinconta)
        {
            Cliente.saldo = Cliente.saldo + valor;
            break;
        }

        utilizador = utilizador.next;
    }

    utilizador = ini;

    while(utilizador != NULL)
    {

        if(Cliente.numconta == numconta)
        {
            Cliente.saldo = Cliente.saldo + valor;
            break;
        }

        utilizador = utilizador.next;
    }




}


void escreveAcounts(Cliente a){
	FILE *file;

	if ( (file = fopen ( "accounts.txt", "r" ) ) != NULL )
	{

	}
	else {

		file = fopen("accounts.txt", "a+");//se nao existir cria e abre para escrita modo append

	}

	//acho que se tem de usar fprintf e nao fputs
	fprintf(file, "%d    %s    %s    %d",a.numconta,a.nome,a.pin,a.saldo);
	fprintf(file," ");



}

*/
