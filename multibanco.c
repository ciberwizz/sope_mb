#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <signal.h>
#include "cliente.h"


void escreveAcounts(Cliente a);
Cliente lerAcounts();



void escreveAcounts(Cliente a){
	FILE *file;

	if ( (file = fopen ( "accounts.txt", "r" ) ) != NULL )
	{
		fclose ( file );
	}
	else {

		file = fopen("accounts.txt", "a+");//se nao existir cria e abre para escrita modo append
		fclose(file);
	}

	//acho que se tem de usar fprintf e nao fputs
	fprintf(file, "%d    %s    %s    %d",a.numconta,a.nome,a.pin,a.saldo);
	fprintf(file," ");



}
