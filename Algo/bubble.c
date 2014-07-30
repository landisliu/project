#include"helper.h"
int main()
{
	clock_t t1,t2;
	int array[ARRAYSIZE];
	int j,k;
	init(array);

	t1 =clock();
	int comTimes =0;
	int exchangeTimes=0;
	for(j=ARRAYSIZE-1;j>0;j--)
		for(k=0;k<j;k++)
		{
			if(array[k]<array[k+1])
			{
				int temp = array[k];
				array[k] = array[k+1];
				array[k+1] = temp;
				exchangeTimes++;
			}
			comTimes++;
		}
	t2 = clock();

	statistics("bubble",t1,t2,comTimes,exchangeTimes);
	return 0;
}
