#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#ifndef __MYPOOL_H__
#define __MYPOOL_H__
#define MSQ_SIZE 32
#define MSG_BODY 512

typedef struct mymesg
{
	long mtype;
	char mtext[MSG_BODY];
}mymsg,*pmymsg;

typedef struct mypool
{
	int msqid;
	int process_count;
	void (*myq_init)(struct mypool *pmp);
	void (*parent_func)(struct mypool *pmp);
	void (*child_func)(struct mypool *pmp);
	void (*mypool_init)(struct mypool *pmp);
	void (*myq_destroy)(struct mypool *pmp);
	void (*myq_display)(struct mypool *pmp);
}mypool,*pmypool;

void child_func(pmypool mp);
void parent_func(pmypool mp);
void dropmsq(pmypool mp);
char * readabletime(time_t);
void displayinfo(pmypool mp);
void sig_parent(int signo);
void sig_parent_int(int signo);
void myppoll_init(pmypool mp);
void mymsq_init(pmypool mp);
#endif
