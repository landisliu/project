#include"helper.h"
#include<dirent.h>
int main(int argc,char * argv[])
{
	DIR * dp;
	struct dirent * dirp;
	if(argc!=2)
		err_quit("parameter invalid.");
	if((dp=opendir(argv[1]))==NULL)
		err_quit("path invalid.");
	while((dirp=readdir(dp))!=NULL)
		printf("%s\n",dirp->d_name);
	exit(0);
}
