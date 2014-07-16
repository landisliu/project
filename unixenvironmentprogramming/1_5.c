#include"helper.h"
int main(int argc,char * argv[])
{
	int c;
	while((c=getc(stdin))!=EOF)
		if(putc(c,stdout)==EOF)
			err_quit("output failed.");
	if(ferror(stdin))
		err_quit("input failed.");
	exit(0);
}
