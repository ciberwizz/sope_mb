#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/select.h>

/*
 *   TODO A definir
 *
 * - TESTAR
 *
 *
 */


/*   TODO LIST Miguel
 *
 * - modificar funcoes para usar request em vez de char[]
 * - modificar as funcoes para usar o array de clientes
 *
 */


/*
 *    TODO LIST Nelson
 *
 *
 *
 *
 */

#define MAXCLIENTES 100000
#define MAX_NUM_CLIENTES 100000
#define FIFO_ANS "ans"
#define FIFO_REQ "requests"

typedef struct Cliente Cliente;
typedef struct ListaCliente ListaCliente;
typedef Cliente ** arrCliente;
typedef struct Request Request;
typedef struct Response Response;

enum Tipo {CONSULTAR, LEVANTAR, DEPOSITAR, TRANSFERENCIA, ADICIONAR, REMOVER, LISTAR, INVALID = -1};
enum User {ADMIN,CLIENTE,SERVER};
struct Request {
	 char pedidoOriginal[128];
	 unsigned int numConta;
	 char pin[5];
	 pid_t pid_cli;
	 enum Tipo tipo;
	 unsigned int numConta2;
	 char pin2[5];
	 char nome[21];
	 double valor;
	 enum User user;
};
struct Response {
	char respOriginal[128];
	char status[128];
	char msg[128];

};

static unsigned int ultimoNumconta = 0;

struct Cliente{
	char nome[20];
	char pin[5];
	unsigned int numconta;
	//aqui
	//int saldo;//o saldo tem de ser double
	double saldo;
	//aqui

};

struct ListaCliente{
	Cliente cliente;
	pid_t pid;
	ListaCliente *next;
	ListaCliente *prev;
};

// retorna o cliente criado ou  null se cliente nao existe
bool login(unsigned int numconta,char pin[4],Cliente * cliente);

//retorna o numero da conta com que o cliente fica ou zero em erro
unsigned int addCliente(char nome[20],char pin[4],arrCliente clienteArray);

//remove um cliente e retorna o numero da conta se ocorreu com sucesso, zero se ocorreu erro
unsigned int removeCliente(unsigned int numconta,arrCliente clienteArray);

//transofrma os dados do cliente numa string
char * clienteToString(Cliente* cliente);

//recebe a linha obtida no accounts.txt e transforma num cliente, sera usada em leraccounts
Cliente * stringToCliente(char* str);

//TODO DEIXA DE SER USADO
//retorna a lista onde um determinado cliente se encontra, else retorna null
ListaCliente * searchCliente(unsigned int numconta,ListaCliente* lista);


arrCliente listarClientes(arrCliente arrayCliente,char* str,int * i);

//criar arrayCliente com o admin com numconta = 0
int createArrayclient(arrCliente array);

bool levantarDinheiro(unsigned int numconta,char pinconta[4],double valor,arrCliente clientesArray);

bool depositarDinheiro(unsigned int numconta,char pinconta[4],double valor,arrCliente clientesArray);

bool transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor,arrCliente clientesArray);

double consultarSaldo(unsigned int numconta,char pinconta[4],arrCliente clientesArray);

bool escreveAcounts(arrCliente clientesArray);

bool lerAcounts(arrCliente clientesArray);
//cria o ficheiro com a primeira linha como data hora programa operacao
bool iniciaLog();
//abre o ficheiro e escreve em modo append ficheiro, e chamado detro de cada funcao como levantardinheiro, etc ...
bool actualizaLog(Request * request,Response * response);

int createFifo(char*);
char* readFifo(char*, int, char*);
// args{ path do fifo, string to write} return  success >0
int writeFifo(char*, char*);
void sigpipe_handler(int signo);


//recebe lista de cliente e array de pointer para cliente
//retorna a quantidade de elementos que fica no array
int listToArray(ListaCliente*, Cliente **);
//so para ser usado no sort e no bsearch
int clienteComparator ( const void * , const void * );
//recebe o array e o num de elementos. usa o qsort
void sortArrayCliente( Cliente **,int);
//recebe array,num de elementos e numconta a procurar
//retorna o apontador para o cliente ou null
Cliente* bsearchClient(Cliente **,int , unsigned int);

//envia o request para o FIFO requests. retorna >0 bem sucedido
int sendRequest(Request *);

//parse do pedido, chama funcao apropriada
Request * parseRequest(char *);

Response * processRequest(Request *, arrCliente );



#endif // UTIL_H_INCLUDED
