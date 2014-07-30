#include"helper.h"

int main()
{
	int array[ARRAYSIZE];
	int i,j,k;
	clock_t t1,t2;
	init(array);
	t1 =clock();
	int comTimes =0;
	int exchangeTimes=0;
	for(j=0;j<ARRAYSIZE-1;j++)
	{
		for(k=j+1;k<ARRAYSIZE;k++)
		{
			if(array[k]<array[j])
			{
				exchangeTimes++;
				int temp = array[k];
				array[k] = array[j];
				array[j] = temp;
			}
			comTimes++;
		}
	}
	t2 =clock();
	statistics("compare",t1,t2,comTimes,exchangeTimes);
	return 0;
}
