#include <libmemcached/memcached.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
	const char *config_string= "192.168.1.115:11211 192.168.1.116:11211";
	char keybuf[1024];
	char valbuf[1024];
	int c;
	while(fgets(keybuf,1024,stdin)!=NULL)
	{
		memcached_return_t rc;
		memcached_st *memc= memcached(config_string, strlen(config_string));
		strcpy(valbuf,keybuf);

		rc= memcached_set(memc, keybuf, strlen(keybuf), valbuf, strlen(valbuf), (time_t)0, (uint32_t)0);

		if (rc != MEMCACHED_SUCCESS)
		{
			printf("set to cache failed. %s\n",keybuf);
		}
		memcached_free(memc);
	}
	return 1;
}
