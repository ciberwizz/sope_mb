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
    /*
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
    */
    //printf("ja adicionou\n");



    //escrever no accouts.txt


    //escreveAcounts(arrayclient);




    //ler do accouts.txt
    if(lerAcounts(arrayclient)){
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

    } puts("nao exist");


    return 0;
}
