#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//TODO diferenciar cliente e lista de cliente
typedef struct Cliente Cliente;

struct Cliente{
	pid_t pid;
	char nome[20];
	char pin[4];
	Cliente *next;
	Cliente *prev;
	unsigned int numconta;
	int saldo;

};



//TODO operacoes com fifos
int createFifo(char*);
int removeFifo(char*);
int readFifo(char*);
int writeFifo(char*);


#endif // UTIL_H_INCLUDED
