#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"userlib.h"
#include<time.h>
#include<syslog.h>
int main(int argc,char * argv[])
{
	openlog("here",LOG_PID,LOG_USER);
	syslog(LOG_INFO|LOG_LOCAL2,"OK");
	closelog();
	
	system("date");	
	return 0;
}

