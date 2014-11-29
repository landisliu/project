#include "mypool.h"
//采用二次fork来避免产生僵尸进程

void myppoll_init(pmypool mp)
{
	//注册信号量 防止产生僵尸进程
	if(signal(SIGCHLD,sig_parent)==SIG_ERR)
	{
		printf("register sigcld failed.\n");
		exit(1);
	}

	pid_t pid;
	int i;
	for(i=0;i<mp->process_count;i++)
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
				child_func(mp);	
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
	mp->parent_func(mp);
}

void sig_parent(int signo)
{
	wait(NULL);
}

void mymsq_init(pmypool mp)
{
	mp->msqid = msgget(IPC_PRIVATE,0666);

	if(mp->msqid<0)
	{
		printf("create msg queue failed.\n");
		exit(1);
	}
}

void parent_func(pmypool mp)
{
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
				if(msgsnd(mp->msqid,msgs+i,MSG_BODY,0)==0)
				{
					mp->myq_display(mp);
				}
				else
				{
					if(errno==EINTR)
						continue;
					perror("send to msq failed.");
					return;
				}
			}
		}
}

void child_func(pmypool mp)
{
		if(signal(SIGINT,SIG_DFL)==SIG_ERR)
		{
			printf("remove signal for child process failed.\n");
			exit(1);
		}
		mymsg tmp;
		while(msgrcv(mp->msqid,&tmp,MSG_BODY,0,0)==MSG_BODY)
		{
			usleep(1000);
			mp->myq_display(mp);
		}
		exit(0);
}

void dropmsq(pmypool mp)
{
	int ret = msgctl(mp->msqid,IPC_RMID,NULL);
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

void displayinfo(pmypool mp)
{
	struct msqid_ds msq;
	
	int ret = msgctl(mp->msqid,IPC_STAT,&msq);
	//printf("uid:%d,gid:%d,cuid:%d,cgid:%d,mode:%o\n",msq.msg_perm.uid,msq.msg_perm.gid,msq.msg_perm.cuid,msq.msg_perm.cgid,msq.msg_perm.mode);
		printf("number of message on the queue:%d,pid:%d\n",msq.msg_qnum,getpid());
		//printf("max # of bytes on the queue:%d\n",msq.msg_qbytes);
		//printf("last msg snd pid :%d\n",msq.msg_lspid);
		//printf("last msg recv pid:%d\n",msq.msg_lrpid);
		//printf("last msg snd time:%s\n",readabletime(msq.msg_stime));
		//printf("last msg recv time:%s\n",readabletime(msq.msg_rtime));
		//printf("last msg change time:%s\n",readabletime(msq.msg_ctime));
}
