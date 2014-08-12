#include<stdio.h>
#include<string.h>
#include<time.h>
//#include<sys/time.h>
static clock_t ct1;
static clock_t ct2;
void start_time()
{
//	struct timeval t1;
//	if(gettimeofday(&t1,NULL)==0)
//	{
//		printf("start time:%ld,%ld\n",t1.tv_sec,t1.tv_usec);
		ct1 = clock();	
//	}
}
void end_time()
{
//	struct timeval t1;
//	if(gettimeofday(&t1,NULL)==0)
//	{
//		printf("end time:%ld,%ld\n",t1.tv_sec,t1.tv_usec);
		ct2 = clock();	
//	}

	ct2 = ct2-ct1;
	printf("clocks per seconds:%ld,time spent:%lf\n",CLOCKS_PER_SEC,((float)ct2)/CLOCKS_PER_SEC);
}

