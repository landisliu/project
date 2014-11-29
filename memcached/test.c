#include <libmemcached/memcached.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
	const char *config_string= "--SERVER=192.168.1.115 --SERVER=192.168.1.116";
	struct memcached_pool_st* pool= memcached_pool(config_string, strlen(config_string));
	char keybuf[1024];
	char valbuf[1024];
	int c;
	while(fgets(keybuf,1024,stdin)!=NULL)
	{
		memcached_return_t rc;
		memcached_st *memc= memcached_pool_pop(pool, false, &rc);

		strcpy(valbuf,keybuf);

		rc= memcached_set(memc, keybuf, strlen(keybuf), valbuf, strlen(valbuf), (time_t)0, (uint32_t)0);

		if (rc != MEMCACHED_SUCCESS)
		{
			printf("set to cache failed. %s\n",keybuf);
		}
		/*
		  Release the memc_ptr that was pulled from the pool
		*/
		memcached_pool_push(pool, memc);
	
	}
	/*
	  Destroy the pool.
	*/
	memcached_pool_destroy(pool);
	return 1;
}
