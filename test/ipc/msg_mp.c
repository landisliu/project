#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#define MSQ_SIZE 32
#define MSG_BODY 512
#define CHILD_PROC_SIZE 4

void child_func();
int parent_func();
void dropmsq();
char * readabletime(time_t);
void displayinfo();
void sig_parent(int signo);
void sig_parent_int(int signo);
void myppoll_init();

typedef struct mymesg
{
	long mtype;
	char mtext[MSG_BODY];
}mymsg,*pmymsg;

int msqid;

int main(int argc,char * argv[])
{
	msqid = mymsq_init();
	myppoll_init();
	parent_func();
	exit(0);
}

//采用二次fork来避免产生僵尸进程

void myppoll_init()
{
	//注册信号量 防止产生僵尸进程
	if(signal(SIGCHLD,sig_parent)==SIG_ERR)
	{
		printf("register sigcld failed.\n");
		exit(1);
	}

	pid_t pid;
	int i;
	for(i=0;i<CHILD_PROC_SIZE;i++)
	{
		if((pid=fork())>0)//parent
		{
		}
		else if(pid==0) //child
		{
			if((pid=fork())>0) //c_parent
			{
				exit(0);
			}
			else if(pid==0) //c_child
			{
				child_func();	
			}
			else
			{
				printf("fork failed.\n");
				exit(1);
			}
		}
		else
		{
			printf("fork failed.\n");
			exit(1);
		}	
	}
}

void sig_parent_int(int signo)
{
	dropmsq(msqid);
}

void sig_parent(int signo)
{
	wait(NULL);
}

int mymsq_init()
{
	int msqid = msgget(IPC_PRIVATE,0666);

	if(msqid<0)
	{
		printf("create msg queue failed.\n");
		exit(1);
	}
	return msqid;
}

int parent_func()
{
		if(signal(SIGINT,sig_parent_int)==SIG_ERR)
		{
			printf("register sigint failed.\n");
			exit(1);
		}
		mymsg msgs[MSQ_SIZE];
		int i;
		for(i=0;i<MSQ_SIZE;i++)
		{
			msgs[i].mtype =i+1;
			strcpy(msgs[i].mtext,"helloworld");
		}
		while(1)
		{
			usleep(10);
			for(i=0;i<MSQ_SIZE;i++)
			{
				if(msgsnd(msqid,msgs+i,MSG_BODY,0)==0)
				{
					displayinfo(msqid);
				}
				else
				{
					perror("send to msq failed.");
					return -1;
				}
			}
		}
	return 0;
}

void child_func()
{
		mymsg tmp;
		while(msgrcv(msqid,&tmp,MSG_BODY,0,0)==MSG_BODY)
		{
			usleep(1000);
			displayinfo(msqid);
		}
		exit(0);
}

void dropmsq()
{
	int ret = msgctl(msqid,IPC_RMID,NULL);
	if(ret)
	{
		printf("message queue delete failed %d.\n",getpid());
		exit(1);
	}
	else
	{
		printf("message queue delete success.\n");
	}
}

char * readabletime(time_t time)
{
	return asctime(localtime(&time));
}

void displayinfo()
{
	struct msqid_ds msq;
	
	int ret = msgctl(msqid,IPC_STAT,&msq);
	//printf("uid:%d,gid:%d,cuid:%d,cgid:%d,mode:%o\n",msq.msg_perm.uid,msq.msg_perm.gid,msq.msg_perm.cuid,msq.msg_perm.cgid,msq.msg_perm.mode);
		printf("number of message on the queue:%d,pid:%d\n",msq.msg_qnum,getpid());
		//printf("max # of bytes on the queue:%d\n",msq.msg_qbytes);
		//printf("last msg snd pid :%d\n",msq.msg_lspid);
		//printf("last msg recv pid:%d\n",msq.msg_lrpid);
		//printf("last msg snd time:%s\n",readabletime(msq.msg_stime));
		//printf("last msg recv time:%s\n",readabletime(msq.msg_rtime));
		//printf("last msg change time:%s\n",readabletime(msq.msg_ctime));
}
