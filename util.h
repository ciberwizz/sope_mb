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

//TODO diferenciar cliente e lista de cliente
typedef struct Cliente Cliente;
typedef struct ListaCliente ListaCliente;//mudar tudo nos outros files de Cliente para ListaCliente




struct Cliente{
	char nome[20];
	char pin[5];
	unsigned int numconta;
	int saldo;

};

struct ListaCliente{
	Cliente cliente;
	pid_t pid;
	ListaCliente *next;
	ListaCliente *prev;

};


//TODO MODIFICAR PARA LISTA DE CLIENTES E CLIENTE
//TODO ADICIONAR REMOVER E LISTAR CLIENTES (RECEBEM LISTA DE CLIENTES)
//TODO LOGIN FUNCAO

// retorna o cliente criado ou  null se cliente nao existe
Cliente *  login(unsigned int numconta,char pin[4],ListaCliente* lista);

//retorna o numero da conta com que o cliente fica ou zero em erro
unsigned int addCliente(char nome[20],char pin[4],ListaCliente* lista,unsigned int ultimoNumconta);

//remove um cliente e retorna o numero da conta se ocorreu com sucesso, zero se ocorreu erro
unsigned int removeCliente(unsigned int numconta,ListaCliente* lista);

//transofrma os dados do cliente numa string
char * clienteToString(Cliente* cliente);


//retorna a lista onde um determinado cliente se encontra, else retorna null
ListaCliente * searchCliente(unsigned int numconta,ListaCliente* lista);

//TODO operacoes com fifos
int createFifo(char*);
char* readFifo(char*, int);
int writeFifo(char*, char*);


#endif // UTIL_H_INCLUDED
