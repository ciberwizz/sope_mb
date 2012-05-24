#include "util.h"


// estas funcoes deviam apenas ser usadas pelo server, passar para server.c
// estas funcoes teem de retornar algo pois pode nao ser possivel concretizar a operacao
// se do servidor, nao e necessario pin..

/*
void levantarDinheiro(unsigned int numconta,char pinconta[4],int valor);
void depositarDinheiro(unsigned int numconta,char pinconta[4],int valor);
void transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor);
void escreveAcounts(Cliente a);
*/


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

    /*
    unsigned int ultimoNumconta = 0;

    ListaCliente lista;
    //strcpy(lista.cliente.nome,admin);
    //lista.cliente.numconta = 0
    lista.next = NULL;
    lista.prev = NULL;

    unsigned int result;
    unsigned int result2;

    result = addCliente("nelson","1234",&lista,ultimoNumconta);

    if(result == 0)
        printf("Nao adicionou cliente\n");

    printf("Cliente adicionado com num conta: %u\n", result);

    printf("listanext nome: %s\n pin: %s\n",lista.next->cliente.nome,lista.next->cliente.pin);
    printf("numconta: %u\n",lista.next->cliente.numconta);
    */

    //teste ao remover o cliente

    /*
    result2 = removeCliente(1,&lista);

    if(result2 == 0)
        printf("Cliente nao foi removido\n");

    printf("cliente removido\n");
    */

    //teste searchcliente

    /*
    ListaCliente* listaresult;
    listaresult =  searchCliente(2,&lista);
    if(listaresult ==NULL)
    {
        printf("lista nao encontrada\n");
    }else
        if(listaresult == lista.next)
            printf("lista econtrada\n");

    */

    //testar login

    /*
    Cliente * clienteresult;
    clienteresult = login(1,"1234",&lista);
    //printf("pinResult: %s, cmp = %d\n",clienteresult->pin,strcmp(clienteresult->pin,"1234"));
    if(clienteresult == NULL)
    {

          printf("Cliente nao existe\n");
    }else

    if(!strcmp(clienteresult->pin,"1234"))
      printf("Com login");
    */

    //testar listarClientes depositar dinheiro
    ListaCliente lista;
    ListaCliente *inicio;
    ListaCliente * ini;
    ListaCliente * levantar;
    ListaCliente * transferir;
    ListaCliente * depositar;
    ListaCliente * verSaldo;
    createListclient(&lista);
    char str[128];
    bool depositou;
    bool levantou;
    bool transferiu;
    Cliente * clienteA;
    Cliente * clienteB;
    double saldoCliente;
    //unsigned int ultimoNumconta = 0;//vai ser para utilizar um static int e actaulizar de cada vez que se adiociona um cliente


    addCliente("nelson","1234",&lista/*,ultimoNumconta*/);
    addCliente("Miguel","5678",&lista/*,ultimoNumconta*/);
    addCliente("Da","1656",&lista/*,ultimoNumconta*/);
    addCliente("Costa","2465",&lista/*,ultimoNumconta*/);
    addCliente("Martins","8714",&lista/*,ultimoNumconta*/);
    addCliente("Pereira","9832",&lista/*,ultimoNumconta*/);
    addCliente("Miguel","4164",&lista/*,ultimoNumconta*/);
    addCliente("Marcos","9165",&lista/*,ultimoNumconta*/);
    addCliente("Juliana","6519",&lista/*,ultimoNumconta*/);
    addCliente("Joao","9720",&lista/*,ultimoNumconta*/);
    addCliente("Joana","1642",&lista/*,ultimoNumconta*/);


    inicio = &lista;
    ini = &lista;
    depositar = &lista;
    levantar = &lista;
    transferir = &lista;
    verSaldo = &lista;


    printf("listar clientes antes\n");
    while(ini != NULL)
    {
        ini = listarClientes(ini,str);
        printf("String :%s\n",str);

    }

    //depositar
     depositou = depositarDinheiro(11,"1642",100,depositar);
     if(depositou == true)
     {
         printf("depositou\n");
     }else
     {
         printf("nao depositou\n");
     }

    printf("listar clientes depois depositar\n");
    while(depositar != NULL)
    {
        depositar = listarClientes(depositar,str);
        printf("String :%s\n",str);

    }

    //levantar
     /*
     levantou = levantarDinheiro(11,"1642",50,levantar);
     if(levantou == true)
     {
         printf("levantou\n");
     }else
     {
         printf("nao levantou\n");
     }

    printf("listar clientes depois levantar\n");
    while(levantar != NULL)
    {
        levantar = listarClientes(levantar,str);
        printf("String :%s\n",str);

    }*/

    //tranferir

    /*
    transferiu = transferirDinheiro(11,"1642",2,50,transferir);
     if(transferiu == true)
     {
         printf("transferiu\n");
     }else
     {
         printf("nao transferiu\n");
     }

    printf("listar clientes depois transferir\n");
    while(transferir != NULL)
    {
        transferir = listarClientes(transferir,str);
        printf("String :%s\n",str);

    }
    */

    //saldo

    saldoCliente = consultarSaldo(11,"1645",verSaldo);

    printf("saldo cliente: %f\n",saldoCliente);


    return 0;
}



/*
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
