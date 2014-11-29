#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "threadpool.h"

void *func(void *arg)
{
	//pthread_t  pt = pthread_self();
	//usleep(10000);
	printf("args: %d \n",(int)arg);
	return NULL;
}
  																					
int main(int argc, char **argv)
{
	if(argc!=3)
		return -1;
	
	int num = atoi(argv[2]);
	int thread_num = atoi(argv[1]);
	if (tpool_create(thread_num) != 0) {
		printf("tpool_create failed\n");
		exit(1);
	}
	int i;
	time_t t1,t2;
	time(&t1);
	for (i = 0; i < num; ++i) {
		tpool_add_work(func, (void*)i);
	}
	tpool_destroy();
	time(&t2);
	printf("%lf seconds elapsed.\n",difftime(t2,t1));
	while(1)
	{}
	return 0;
}
