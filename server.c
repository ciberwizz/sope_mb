#include "util.h"


int main() {

    /*
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
    Request * request;
    Response * response;
    */
    Cliente * arrayclient[MAX_NUM_CLIENTES];
    arrCliente temp;
    arrCliente temp2;
    char str[128];
    int i;
    //printf("cria array\n");
    createArrayclient(arrayclient);
    //printf("ja criou array\n");



    //printf("vai comecar a adicionar\n");
    addCliente("nelson","1234",arrayclient);
    addCliente("Miguel","5678",arrayclient);
    addCliente("Da","1656",arrayclient);
    addCliente("Costa","2465",arrayclient);
    addCliente("Martins","8714",arrayclient);
    addCliente("Pereira","9832",arrayclient);
    addCliente("Miguel","4164",arrayclient);
    addCliente("Marcos","9165",arrayclient);
    addCliente("Juliana","6519",arrayclient);
    addCliente("Joao","9720",arrayclient);
    addCliente("Joana","1642",arrayclient);
    addCliente(":)","1236",arrayclient);
    addCliente("NO","1769",arrayclient);
    addCliente("YES","6414",arrayclient);
    addCliente("ABCD","1223",arrayclient);
    addCliente("dhf","2222",arrayclient);
    addCliente("aghf","2222",arrayclient);

    //printf("ja adicionou\n");


    i = 0;
    printf("listar clientes\n");
    memset(str,0,128);
    temp = listarClientes(arrayclient,str,&i);


    while(temp != NULL)
    {
            printf("String :%s\n",str);


        memset(str,0,128);
        temp = listarClientes(temp,str,&i);



    }

    //removecliente

    removeCliente(3,arrayclient);

    i = 0;
    printf("listar clientes\n");
    memset(str,0,128);
    temp2 = listarClientes(arrayclient,str,&i);


    while(temp2 != NULL)
    {
            printf("String :%s\n",str);


        memset(str,0,128);
        temp2 = listarClientes(temp,str,&i);



    }

    /*
    inicio = &lista;
    ini = &lista;
    depositar = &lista;
    levantar = &lista;
    transferir = &lista;
    verSaldo = &lista;
    listaRemover = &lista;
    listaEscrever = &lista;
    listaler = &lista;
    */



    /*
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
    */

    //testar logs

    /*
    request = (Request *) malloc(sizeof(Request));
    response = (Response *) malloc(sizeof(Response));

    strcpy(request->nome,"nelson");
    request->numConta = 1;
    request->numConta2 = 2;
    strcpy(request->pedidoOriginal,"Depositar dinheiro");
    request->pid_cli = 12;
    strcpy(request->pin,"1234");
    strcpy(request->pin2,"5678");
    request->valor = 100;
    request->user = CLIENTE;
    request->tipo = DEPOSITAR;
    */


    //strcpy(response->status,"OK");
    //strcpy(response->respOriginal,"levantar dinheiro");
    //strcpy(response->msg,"levantar");

    /*
    response = NULL;
    //iniciaLog();
    actualizaLog(request,response);
    */




    return 0;
}
