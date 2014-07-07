#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void swap(int[],int,int);
void quicksort(int array[],int start,int end)
{
	int mid =start+(end -start)/2;
	int f_start = start;
	int f_end = end;

	while(start<end)
	{
		while(end>mid&&array[end]>=array[mid])end--;
		if(end>mid)
		{
			swap(array,end,mid);
			mid = end;
		}
		while(start<mid&&array[start]<=array[mid])start++;
		if(start<mid)
		{
			swap(array,start,mid);
			mid=start;
		}
	}
	if(f_start<mid-1)
	quicksort(array,f_start,mid-1);
	if(mid+1<f_end)
	quicksort(array,mid+1,f_end);	
}
void swap(int array[],int index1,int index2)
{
	int temp = array[index1];
	array[index1]=array[index2] ;
	array[index2]= temp;
}
int main(int argc,char ** argv)
{
	int num = atoi(argv[1]);
	int i;
	int array[num];
	for(i=0;i<num;i++)
	{
		array[i] = rand();
	}
	quicksort(array,0,num-1);
	//for(i=0;i<num;i++)
	//printf("%d\n",array[i]);
	exit(EXIT_SUCCESS);
}
