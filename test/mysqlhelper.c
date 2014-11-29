#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<mysqld_error.h>
#include<string.h>
#define BUFSIZE 1024
//#define DEBUG_MYSQL
 
MYSQL ms;
MYSQL_RES *res_ptr;
char buffer[BUFSIZE];

static int colnum=0;

char * getmyconerr();
void myconerrexit();
void mycon_showerr();
unsigned long mycon_affect_rows();
int mycon_lastinsertid();
unsigned long mycon_insert(const char* query);
int mycon_update(const char* query);
int mycon_delete(const char* query);
int mycon_initoptions();
int mycon_init();
int mycon_close();
int mycon_getrows(const char * query,MYSQL_ROW *rows,int *count);

/*int main(int argc,char * argv[])
{
	mycon_init();
	int i,j;
	
	for(i=0;i<10;i++)
	{
		bzero(buffer,BUFSIZE);
		snprintf(buffer,BUFSIZE,"insert into person(name,height,salary,birthday) values('liuzhiwei%d',1.70,10000,'1987/02/18');",i);
		mycon_insert(buffer);
	}
	
	printf("last insert id:%d\n",mycon_lastinsertid());
	
	int count = BUFSIZE;
	MYSQL_ROW rows[count];
	if(!mycon_getrows("select * from person;",rows,&count))
	{
		for(i=0;i<count;i++)
		{
			printf("id:%s,name:%s,height:%s,salary:%s,birthday:%s\n",rows[i][0],rows[i][1],rows[i][2],rows[i][3],rows[i][4]);
		}
		printf("totally %d rows\n",count);
		//释放空间
		for(i=0;i<count;i++)
		{
			for(j=0;j<colnum;j++)
			{
				free(rows[i][j]);
			}
			free(rows[i]);
		}
	}
	mycon_update("update person set height=50 where name like '%liuzhiwei%';");
	mycon_delete("delete from person where name like '%liuzhiwei%';");

	mycon_close();
	exit(EXIT_SUCCESS);
}
*/

char * getmyconerr()
{
	bzero(buffer,BUFSIZE);
	snprintf(buffer,BUFSIZE,"mysql error:%d,detail msg:%s\n",mysql_errno(&ms),mysql_error(&ms));
	return buffer;
}
void myconerrexit()
{
	char * errmsg = getmyconerr();
	fprintf(stderr,"%s",errmsg);
	exit(EXIT_FAILURE);
}

void mycon_showerr()
{
	fprintf(stderr,"%s",getmyconerr());
}


unsigned long mycon_affect_rows()
{
	return (unsigned long)mysql_affected_rows(&ms);
}

int mycon_getrows(const char * query,MYSQL_ROW *rows,int *count)
{
	int ret = mysql_query(&ms,query);
	MYSQL_ROW sqlrow;
	if(!ret)
	{
		res_ptr = mysql_use_result(&ms);
		if(res_ptr)
		{
			colnum = mysql_field_count(&ms);
			int i=0;
			int j=0;
			while((sqlrow=mysql_fetch_row(res_ptr))&&i<*count)
			{
				*(rows+i)=malloc(colnum*sizeof(void*));
				for(j=0;j<colnum;j++)
				{
					if(sqlrow[j])
					{
						char *pcol = malloc(strlen(sqlrow[j])+1);
						*(*(rows+i)+j) = pcol;
						strcpy(pcol,sqlrow[j]);
					}					
				}
				i++;
			}
			*count=i;
			mysql_free_result(res_ptr);	
		}
		return 0;		
	}
	else
	{
		mycon_showerr();	
	}
	return -1;
}

int mycon_lastinsertid()
{
	int ret = mysql_query(&ms,"select last_insert_id();");
	int lastid=-1;
	MYSQL_ROW sqlrow;
	if(!ret)
	{
		res_ptr = mysql_use_result(&ms);
		if(res_ptr && (sqlrow=mysql_fetch_row(res_ptr)))
		{
			lastid = atoi(sqlrow[0]);
			mysql_free_result(res_ptr);	
		}		
	}
	else
	{
		mycon_showerr();
		return lastid;	
	}
	return lastid;
}

unsigned long mycon_insert(const char* query)
{
	if(!mysql_query(&ms,query))
	{
		unsigned long ret = mycon_affect_rows();
		#ifdef DEBUG_MYSQL
		fprintf(stdout,"insert %lu rows\n",ret);
		#endif
		return ret;
	}
	else
	{
		fprintf(stderr,"insert failed:%s\n",query);
		mycon_showerr();
	}
}

int mycon_update(const char* query)
{
	if(!mysql_query(&ms,query))
	{
		#ifdef DEBUG_MYSQL
		fprintf(stdout,"update %lu rows\n",mycon_affect_rows());
		#endif	
	}
	else
	{
		fprintf(stdout,"no rows affected.\n");
		mycon_showerr();
	}
}

int mycon_delete(const char* query)
{
	if(!mysql_query(&ms,query))
	{
		#ifdef DEBUG_MYSQL
			fprintf(stdout,"delete %lu rows\n",mycon_affect_rows());
		#endif	
	}
	else
	{
		fprintf(stdout,"no rows deleted.\n");
		mycon_showerr();
	}
}
int mycon_initoptions()
{
	unsigned int timeout = 7;
	return mysql_options(&ms,MYSQL_OPT_CONNECT_TIMEOUT,(const char *)&timeout);	
}
int mycon_init()
{
	char * host="localhost";
	char * username="root";
	char * password ="zhiwei.liu";
	char * db_name ="worm";
	unsigned int port = 0;
	const char *usn=NULL;
	/*CLIENT_FOUND_ROWS 显示所有相关的行，而不止是受影响的行*/
	unsigned int flags=CLIENT_FOUND_ROWS;

	if(mysql_init(&ms)==NULL||mycon_initoptions()!=0||mysql_real_connect(&ms,host,username,password,db_name,port,usn,flags)==NULL)
	{
		myconerrexit();
	}
	return 0;
}

int mycon_close()
{
	mysql_close(&ms);
}
