#include "util.h"

int main() {
	int i;
	char buff[1000];
	char pid[100];
	printf("whatpid? ");
	//scanf("%d",i);
	i=1234;
	sprintf(pid,"ans%d",i);

	printf("createfifo=%d\n",createFifo(pid));
	signal(SIGPIPE, sigpipe_handler);

	sleep(3);
	for(i = 0 ; i < 10000 ; i++) {
		sprintf(buff, "%04d mississippi",i);
		puts(buff);
		writeFifo(pid,buff);
		usleep(1500);
	}
	puts("a sair");
	//remove(pid);
	pause();
	return 0;


}
