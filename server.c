#include "util.h"


int main() {

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
