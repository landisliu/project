#include"helper.h"
static void quick_sort(int *array,int start,int end,int *iterator)
{
	int tstart= start;
	int tend=end;
	int mid = start+(end-start)/2;
	*iterator = *iterator+1;	
	while(tend>tstart)
	{
		while(tend>mid&&array[tend]>=array[mid])
			tend--;
		if(tend>mid)
		{
			exchange(array,tend,mid);
			mid=tend;
		}
		while(tstart<mid&&array[tstart]<=array[mid])
			tstart++;
		if(tstart<mid)
		{
			exchange(array,tstart,mid);
			mid = tstart;
		}
	}
	if((mid-start)>1)
		quick_sort(array,start,mid-1,iterator);
	if((end-mid)>1)
		quick_sort(array,mid+1,end,iterator);
}
int main()
{
	clock_t t1,t2;
	int array[ARRAYSIZE];
	t1 =clock();
	init(array);
	int iterator =0; 
	quick_sort(array,0,ARRAYSIZE-1,&iterator);
	t2=clock();
	printf("%d\n",iterator);
	statistics("quick",t1,t2,0,0);
	return 0;
}
