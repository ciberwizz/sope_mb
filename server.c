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
