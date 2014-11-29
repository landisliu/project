#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <time.h>

typedef struct mymesg
{
	long mtype;
	char mtext[512];
}mymsg,*pmymsg;

void dropmsq(int);
char * readabletime(time_t);
void displayinfo(int);
int main(int argc,char * argv[])
{
	int msqid = msgget(IPC_PRIVATE,0666);
	if(msqid<0)
	{
		printf("create msg queue failed.\n");
		exit(1);
	}
	else
	{
		printf("%d\n",msqid);
	}

	struct msqid_ds msq;
	
	int ret = msgctl(msqid,IPC_STAT,&msq);


	if(ret)
	{
		dropmsq(msqid);
		exit(1);	
	}
	else
	{
		mymsg msgs[10];
		int i=0;

		for(i=0;i<10;i++)
		{
			msgs[i].mtype =i+1;
			strcpy(msgs[i].mtext,"helloworld");
		}

		for(i=0;i<10;i++)
		{
			if(msgsnd(msqid,msgs+i,sizeof(msgs[i].mtext),0)==0)
			{
				displayinfo(msqid);
				sleep(5);
			}
			else
			{
				perror("send to msq failed.");
				goto error;
			}
		}
		mymsg tmp;
		for(i=0;i<10;i++)
		{
			if(msgrcv(msqid,&tmp,sizeof(msgs[i].mtext),0,0)==sizeof(mymsg))
			{
				printf("msg type:%d,message:%s\n",tmp.mtype,tmp.mtext);
				displayinfo(msqid);
				sleep(5);
			}
			else
			{
				printf("receive error.\n");
				break;
			}
		}
		
		displayinfo(msqid);		
	}
error:
	dropmsq(msqid);
	exit(0);
}

void dropmsq(int msqid)
{
	int ret = msgctl(msqid,IPC_RMID,NULL);
	if(ret)
	{
		printf("message queue delete failed.\n");
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
void displayinfo(int msqid)
{
	struct msqid_ds msq;
	
	int ret = msgctl(msqid,IPC_STAT,&msq);
	printf("uid:%d,gid:%d,cuid:%d,cgid:%d,mode:%o\n",msq.msg_perm.uid,msq.msg_perm.gid,msq.msg_perm.cuid,msq.msg_perm.cgid,msq.msg_perm.mode);
		printf("number of message on the queue:%d\n",msq.msg_qnum);
		printf("max # of bytes on the queue:%d\n",msq.msg_qbytes);
		printf("last msg snd pid :%d\n",msq.msg_lspid);
		printf("last msg recv pid:%d\n",msq.msg_lrpid);
		printf("last msg snd time:%s\n",readabletime(msq.msg_stime));
		printf("last msg recv time:%s\n",readabletime(msq.msg_rtime));
		printf("last msg change time:%s\n",readabletime(msq.msg_ctime));
}
