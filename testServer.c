#include "util.h"
#include <pthread.h>
#include <stdbool.h>

#define NMAX 100

struct {
	int num;
	bool prime;
}isprimes[NMAX];

int tocheck[4];

pthread_mutex_t primes = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pri = PTHREAD_COND_INITIALIZER;

pthread_mutex_t check = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t chk = PTHREAD_COND_INITIALIZER;

void *calcprime(void *a);
void *wichcheck(void *a);

//ineficient prime check
bool prime(int);
//private
bool iprime(int,int);

//TODO BUUUUUGGGGGSSSS
int main() {
	pthread_t wich, calc[4];
	int th[4], num_a_calc = 80;


	int i;

	if( pthread_create(&wich,NULL,wichcheck,&num_a_calc ) ){
		perror("UNABLE TO CREATE -WICH- THREAD\n");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < 4; i++){
		th[i] = i;
		if( pthread_create( &(calc[i]), NULL, calcprime, &(th[i])) ){
			perror("UNABLE TO CREATE -CALC- THREAD\n");
			exit(EXIT_FAILURE);
		}
	}

	pthread_join(wich,NULL);
	for(i = 0; i < 4; i++){
		pthread_join(calc[i],NULL);
	}



}


void *calcprime(void *a){
	int id = *(int *) a;
	int tochck;
	int prme;
	bool ret;

	printf("Hello I'm th%d\n",id);

	while(1){
		usleep(10*1000);
		puts("start");

	//ver qual o indice do primo que tem de de calcular
	//caso seja 0 e' pq o wichcheck ainda nao actualizou
	//tem q esperar.
	//dpois manda o sinal pois ja nao necessita


		do{
			//puts("waiting to get idex");
			pthread_mutex_lock(&check);
			tochck = tocheck[id];
			//puts("got index");
			pthread_mutex_unlock(&check);

			if(tochck == -1){
				printf("thread th%d is out!!",id);
				return NULL;
			} //else printf("id:%d -> tochck = %d\n",id,tochck);

			usleep(10*1000);
		}while(tochck == 0);

		//puts("ja tenho o tochck");

		pthread_mutex_lock(&check);
		tocheck[id] = 0;
		pthread_mutex_unlock(&check);

		//get o prime a calcular
		pthread_mutex_lock(&primes);
		prme = isprimes[tochck].num;
		pthread_mutex_unlock(&primes);

		printf("th%d to calc:%d\n",id,tochck);
		ret = prime(prme);
		printf("th%d calced\n",id);

		//espera disponibilidade da struct para
		//actualizar se e primo ou n
		pthread_mutex_lock(&primes);
		isprimes[tochck].prime = ret;

		pthread_mutex_unlock(&primes);
		//pthread_mutex_unlock(&check);
	}

}

void *wichcheck(void *a){
	int i, index;
	int quant = *(int *) a; // qtiadade de primos
	int tquant,tq;

	/*
	 * INICIALIZAR
	 */

	pthread_mutex_lock(&check);
	pthread_mutex_lock(&primes);


	for(i = 0; i < NMAX ; i++){
		isprimes[i].num = i+1;
		isprimes[i].prime = false;
	}
	pthread_mutex_unlock(&primes);

	tocheck[0] = 0;
	tocheck[1] = 0;
	tocheck[2] = 0;
	tocheck[3] = 0;
	pthread_mutex_unlock(&check);

	//pthread_cond_signal(&chk);
	/*
	 * FIM INI
	 */



	/*
	 * Ciclo de actulizacao
	 */

	index = NMAX;
	i = quant -1;
	tquant = 0;
	do{
		//printf("wich: to wait index=%d\n",index);
		pthread_mutex_lock(&check);

		tq = 4;

		while( (tq != 0) && (quant - tquant != 0) ){
			if( tocheck[tq-1] == 0 ){
				tocheck[tq-1] = --index;
//				printf("ACTUALIZAR:index=%d",index);
				tquant++;
			}
			tq--;
		}

		pthread_mutex_unlock(&check);
		usleep(100);


	}while( index > NMAX-quant );

	//puts("out of while");
	pthread_mutex_lock(&check);
	for( i = 4 -1; i >= 0 ; i--)
		if(tocheck[i] == 0){
			tocheck[i] = -1;
			puts("endflag");
		} else {
			pthread_mutex_unlock(&check);
			i = 4;
		}
	pthread_mutex_unlock(&check);


	puts("\n\nOUUUUUTTTT\n\n");

}

bool prime(int x){
	return iprime(x,2);
}

bool iprime(int x, int y){
	if( y >= x/2 ){
		printf("%d is prime\n",x);
		return true;
	}
	else
		if(x%y == 0){
			printf("%d is devisable by %d\n",x,y);
			return false;
		} else  return iprime(x,y+1);

}



