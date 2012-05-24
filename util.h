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


#define FIFO_ANS "ans"
#define FIFO_REQ "requests"

//TODO diferenciar cliente e lista de cliente
typedef struct Cliente Cliente;
typedef struct ListaCliente ListaCliente;//mudar tudo nos outros files de Cliente para ListaCliente


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
unsigned int addCliente(char nome[20],char pin[4],ListaCliente* lista/*,unsigned int ultimoNumconta*/);

//remove um cliente e retorna o numero da conta se ocorreu com sucesso, zero se ocorreu erro
unsigned int removeCliente(unsigned int numconta,ListaCliente* lista);

//transofrma os dados do cliente numa string
char * clienteToString(Cliente* cliente);


//retorna a lista onde um determinado cliente se encontra, else retorna null
ListaCliente * searchCliente(unsigned int numconta,ListaCliente* lista);

//listar todos os clientes e ir devolvendo strings obtidas pelos tostrings de cada cliente, a cada iteracao a listaCliente e actualizada
ListaCliente * listarClientes(ListaCliente * lista,char* str);

//criar lista e o admin com numconta = 0
int createListclient(ListaCliente *);

bool levantarDinheiro(unsigned int numconta,char pinconta[4],int valor,ListaCliente* lista);
bool depositarDinheiro(unsigned int numconta,char pinconta[4],int valor,ListaCliente* lista);
bool transferirDinheiro(unsigned int numconta,char pinconta[4],unsigned int numconta2,int valor,ListaCliente* lista);
double consultarSaldo(unsigned int numconta,char pinconta[4],ListaCliente* lista);
bool escreveAcounts(ListaCliente *  lista);
bool lerAcounts();

//TODO operacoes com fifos
int createFifo(char*);
char* readFifo(char*, int, char*);
int writeFifo(char*, char*);
void sigpipe_handler(int signo);

#endif // UTIL_H_INCLUDED
