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
