#include "mypool.h"

mypool pool;

int main(int argc,char * argv[])
{
	if(signal(SIGINT,sig_parent_int)==SIG_ERR)
	{
		printf("register sigint failed.\n");
		exit(1);
	}
	pool.myq_init = mymsq_init;
	pool.myq_destroy = dropmsq;
	pool.parent_func=parent_func;
	pool.child_func=child_func;
	pool.mypool_init = myppoll_init;
	pool.myq_display = displayinfo;
	
	pool.process_count =1;
	pool.myq_init(&pool);
	pool.mypool_init(&pool);
	exit(0);
}

void sig_parent_int(int signo)
{
	dropmsq(&pool);
}
