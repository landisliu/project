#include"userlib.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#define STACK_SIZE 100
static char daytab[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};

void word_length_ver(char *str)
{
	char *p =str;
	int word_length = 0;
	int array[1024];
	int *parray = array;
	int arraysize =0;
	int max_wl =0;
	while(*p!=0)
	{
		if(*p==' '||*p=='\t'||*p=='.'||*p==',')
		{
			if(word_length>0)
			{	
				if(max_wl<word_length)
					max_wl =word_length;
				*parray++ =word_length;
				word_length=0;
				arraysize++;
			}
		}
		else	
		{
			word_length++;
		}
		p++;
	}
	if(word_length>0)
	{
		if(max_wl<word_length)
			max_wl = word_length;
		*parray = word_length;
		arraysize++;	
	}
	int t_array[max_wl][arraysize];
	int i,j,k;
	for(i=0;i<arraysize;i++)
	{
		for(j=max_wl-1,k=array[i];k>0;j--,k--)
		{
			t_array[j][i]=1;
		}
	}
	
	for(i=0;i<max_wl;i++)
	{
		for(j=0;j<arraysize;j++)
		{
			if(1==t_array[i][j])
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}
void word_length_hor(char *str)
{
	char *p =str;
	while(*p!=0)
	{
		if(*p==' '||*p=='\t'||*p==','||*p=='.')
			printf("\n");
		else
			printf("*");
		p++;
	}
	printf("\n");
}
char * max_dup_char(char *src,char ch,int * count)
{
	int count_org,count_new;
	char *p_org,*p_new,*p_start;	
	int findch =0;
	int flag =0;
	count_org = count_new =0;
	p_org=p_new=src;
	
	while(*p_new!=0)
	{
		if(*p_new==ch)
		{
			if(0==findch)
			{
				p_start = p_new;
				count_new =0;
				findch=1;
			}
			count_new++;
		}
		else
		{
			if(1==findch)
			{
				findch =0;
				if(count_org<count_new)
				{
					count_org = count_new;
					p_org = p_start;
				}
				flag =1;
			}
		}
		p_new++;
	}
	if(1==findch)
	{
		if(count_org<count_new)
		{
			count_org = count_new;
			p_org = p_start;
		}
		flag =1;
	}
	if(flag =1)
	{
		*count = count_org;
		return p_org;
	}
	else
		return NULL;
}
int wordcount(FILE * fp)
{
	int maxcharcount = 1024;
	char line[1024];
	int nw = 0;
	int flagstart = 0;
	int flagblank = 0;
	int c;
	char word[1024];
	char *pw = word;
	while((c=getc(fp))!=EOF)
	{
			if(c==' '||c=='\t'||c=='\n'||c==','||c=='.')
				flagblank =1;
			else
			{
				flagstart =1;
				*pw++ = c;
				flagblank = 0;
			}
			
			if(flagblank==1&&flagstart==1)
			{
				flagstart =0;
				*pw ='\0';
				puts(word);
				nw++;
				pw = word;
				
			}
					
	}
	return nw;
}
void memorytest()
{
	int size=(int)1024*sizeof(int);
	int *p = (int *)malloc(size);
	//memset(p,0,size);
	int *q = p;
	int c;
	while((c=getchar())!=EOF)
	{
		*q++ = c;
	}	
	
	int * q2;
	for(q2=p;q2!=q;q2++)
	{
		putchar(*q2);
	}
	free(p);
}
void mystrncpy(char * dest,const char * source,size_t num)
{
	while(num-->0&&*source!='\0')
	{
		*dest++=*source++;
	}
	*dest ='\0';
}

char * minlength(char * str1,char* str2)
{
	if(strlen(str1)<strlen(str2))
	{
		return str1;
	}	
	else
	{
		return str2;
	}
}

char * maxlength(char * str1,char * str2)
{
	if(strlen(str1)>strlen(str2))
	{
		return str1;
	}
	else
	{
		return str2;
	}
}

void stringlib()
{
	char * str1 = "first str.";
	char * str2 = "second str.";
	int minlen = strlen(minlength(str1,str2));
	int maxlen = strlen(maxlength(str1,str2));

	char newstr[1024]="abc";
	strcat(newstr,str1);
	strcat(newstr,str2);
	printf("strcat,%s,%s:%s\n",str1,str2,newstr);
	printf("----------------------------------\n");
	strncat(newstr,str1,strlen(str1)-1);
	strncat(newstr,str2,strlen(str2)-1);
	printf("strncat,%s,%s:%s\n",str1,str2,newstr);
	printf("----------------------------------\n");
	int ret= strcmp(str1,str2);
	if(ret>0)
	{
		printf("%s is greater than %s\n",str1,str2);		
	}
	else if(ret<0)
		printf("%s is less than %s\n",str1,str2);
	else
		printf("%s is equal to %s\n",str1,str2);
	printf("---------------------------------\n");
	ret = strncmp(str1,str2,minlen);
	
	if(ret>0)
	{
		printf("%s is greater than %s\n",str1,str2);
	}
	else if(ret<0)
	{
		printf("%s is less than %s\n",str1,str2);
	}
	else
		printf("%s is equal to %s within %d\n",str1,str2,minlen);

	printf("------------------------------------\n");
	strcpy(newstr,str1);
	printf("copy %s to %s\n",str1,newstr);
	strncpy(newstr,str2,strlen(str2));
	newstr[strlen(str2)]='\0';
	printf("copy %s to %s with in %ld\n",str2,newstr,strlen(str2));
	printf("------------------------------------\n");

	int c= 's';
	
	char * pc  =strchr(str1,c);
	printf("first %c in %s is %ld\n",c,str1,pc-str1+1);
	
	pc = strrchr(str2,c);
	printf("last %c in %s is %ld\n",c,str2,pc-str2+1);
}
void firstdiffline(char * file1,char * file2)
{
	const int size=1024;
	char line[size];
	char line2[size];
	FILE * fp1 = fopen(file1,"r");
	FILE * fp2 = fopen(file2,"r");
	while(1)
	{
		if(fgets(line,size,fp1)!=NULL)
		{
			if(fgets(line2,size,fp2)!=NULL)
			{
				if(strcmp(line,line2)!=0)
				{
					fputs(line,stdout);
					fputs(line2,stdout);
					break;
				}
			}
			else
			{
				fputs(line,stdout);
				break;
			}	
		}
		else
		{
			if(fgets(line2,size,fp2)!=NULL)
			{
				fputs(line2,stdout);
				break;
			}
			else
			{
				fputs("no difference.",stdout);
				break;
			}
		}
	
	}

	fclose(fp1);
	fclose(fp2);
	exit(0);
}
void filecopy(FILE * target,FILE * source)
{
	int c;
	while((c=getc(source))!=EOF)
		putc(c,target);
}
void cat(int argc,char *argv[])
{
	FILE * fp;
	char * procname = argv[0];
	if(argc==1)
		filecopy(stdout,stdin);
	while(--argc>0)
	{
		if((fp = fopen(*++argv,"r"))==NULL)
		{
			fprintf(stderr,"%s:open file %s failed.\n",procname,*argv);
			continue;
		}
		else
		{
			filecopy(stdout,fp);
			close(fp);
		}
		if(ferror(stdout))
		{
			fprintf(stderr,"%s:write to stdout failed.\n",procname);
			exit(1);
		}
	}
}
void miniscanf(char * fmt,...)
{
	va_list ap;
	int c;
	int *ival;
	double *dval;
	char *p,*sval;
	va_start(ap,fmt);
	for(p=fmt;*p;p++)
	{
		if(*p!='%')
		{
			if(*p!=(c=getchar()))
			{
				printf("input invalid\n");
				exit(1);
			}
			continue;	
		}
		switch(*++p)
		{
			case 'd':
				ival=va_arg(ap,int*);
				scanf("%d",ival);
				break;
			case 'f':
				dval = va_arg(ap,double*);
				scanf("%lf",dval);
				break;
			case 's':
				sval = va_arg(ap,char *);
				while((c=getchar())!=EOF)
				{
					*sval++=c;
				}
				break;
			default:getchar();break;
		}
	}
	va_end(ap);
}
void miniprintf(char * fmt,...)
{
	va_list ap;
	char *p,*sval;
	int ival;
	double dval;
	va_start(ap,fmt);
	for(p=fmt;*p;p++)
	{
		if(*p!='%')
		{
			putchar(*p);
			continue;
		}
		switch(*++p)
		{
			case 'd':
				ival = va_arg(ap,int);
				printf("%d",ival);
				break;
			case 'f':
				dval = va_arg(ap,double);
				printf("%f",dval);
				break;
			case 's':
				for(sval=va_arg(ap,char *);*sval;sval++)
					putchar(*sval);
				break;
			default: putchar(*p);break;
		}
	}
	va_end(ap);
}
int day_of_year(int year,int month,int day)
{
	int i,leap;
	leap  = year%4==0&&year%100!=0||year%400==0;
	for(i=1;i<month;i++)
		day+=daytab[leap][i];
	return day;
}
void month_day(int year,int yearday,int *pmonth,int *pday)
{
	int i,leap;
	leap = year%4==0&&year%100!=0||year%400==0;
	for(i=1;yearday-daytab[leap][i]>0;i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday; 
}

static double stack[STACK_SIZE];
static int index_stack =0;
double pop(void)
{
	if(index_stack>0)
	{
		return stack[--index_stack];
	}
	else
	{
		printf("stack is empty, no more item to pop....");
		exit(1);
	}
}

void push(double item)
{
	if(index_stack<STACK_SIZE)
	{
		stack[index_stack++] = item;
	}
	else
	{
		printf("Stack is full,cann't insert more...");
		exit(1);
	}
}
double expr(int argc,char **argv)
{
	double op2;
	while(--argc>0&&++argv!=NULL)
	{
		switch((*argv)[0])
		{
			case '+':push(pop()+pop());break;
			case '-':op2 =pop();push(pop()-op2);break;
			case '*':push(pop()*pop());break;
			case '/':op2 = pop();if(op2){printf("divide by zero.");}else{push(pop()/op2);}break;
			default:
				push(atof(*argv));break;
		}
	}
	return pop();
}
void sizeoftype()
{
	printf("sizeof int %4ld\n",sizeof(int));
	printf("sizeof float %4ld\n",sizeof(float));
	printf("sizeof short %4ld\n",sizeof(short));
	printf("sizeof long %4ld\n",sizeof(long));
	printf("sizeof char %4ld\n",sizeof(char));
	printf("sizeof unsigned int %4ld\n",sizeof(unsigned int));
}
size_t arraysize(void *array,size_t length)
{
	return sizeof(array)/length;
}
