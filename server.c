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
    ListaCliente * listaRemover;
    ListaCliente * listaEscrever;
    ListaCliente * listaler;
    createListclient(&lista);
    char str[128];
    bool depositou;
    bool levantou;
    bool transferiu;
    bool resultEscrever;
    bool resultLer;
    Cliente * clienteA;
    Cliente * clienteB;
    double saldoCliente;
    unsigned int resultRemover;
    Cliente * clienteTestar;



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
    addCliente(":)","1236",&lista);
    addCliente("NO","1769",&lista);
    addCliente("YES","6414",&lista);
    addCliente("ABCD","1223",&lista);
    addCliente("dhf","2222",&lista);
    addCliente("aghf","2222",&lista);


    inicio = &lista;
    ini = &lista;
    depositar = &lista;
    levantar = &lista;
    transferir = &lista;
    verSaldo = &lista;
    listaRemover = &lista;
    listaEscrever = &lista;
    listaler = &lista;



    //testar escrever accounts


    printf("Escrever accounts\n");
    resultEscrever = escreveAcounts(listaEscrever);
    if(resultEscrever == false)
        printf("Erro, nao escreveu accounts\n");
    printf("Escreveu no accounts\n");


    //testar ler accounts

    printf("ler accounts\n");
    resultLer = lerAcounts(listaler);

    printf("primeiro nome: %s\n",listaler->cliente.nome);

    if(resultLer == true)
    {
        printf("Leu correctamente\n");
    }else
    {
        printf("Nao leu correctamente\n");
    }

    printf("listar clientes depois ler\n");
    while(listaler != NULL)
    {
        listaler = listarClientes(listaler,str);
        printf("String :%s\n",str);

    }



    return 0;
}
