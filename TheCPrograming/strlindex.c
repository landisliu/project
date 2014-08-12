#include<stdio.h>
#include<string.h>
char * strlindex(char * s,char *t)
{
	int i =strlen(s);
	int j = strlen(t);
	if(i<j)
	return NULL;
	i--;
	for(;i>=0;i--)
	{
		j = strlen(t);
		j--;
		for(;j>=0&&i>=0;j--,i--)
		{
			if(s[i]!=t[j])
			break;
		}
		if(j<0)
		return s+i+1;
	}
	if(i<0)
	return NULL;
}

char * strfindex(char *s ,char * t)
{
	int i,j,k;
	int sl = strlen(s);
	int tl = strlen(t);
	if(sl<tl)
		return NULL;
	for(i=0;i<sl;i++)
	{
		k=i;
		for(j=0;j<tl&&i<sl;j++,i++)
		{
			if(s[i]!=t[j])
			break;
		}
		if(j==tl)
			return s+k;
	}
	
	return NULL;
}

int  strcount(char *s ,char *t)
{
	int count =0;
	char * index;
	while((index=strfindex(s,t))!=NULL)
	{
		count++;
		s=index+1;
	}
	return count;	
}

int main()
{
	char * s ="aabbccddasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfaabasdfbacdd";
	char *t = "asdf";
	char * lindex = strlindex(s,t);
	char * findex = strfindex(s,t);
	printf("lindex %ld\n",lindex-s);
	printf("findex %ld\n",findex-s);
	printf("count %d\n",strcount(s,t));
	return 0;
}
