#include<stdio.h>
#include"helper.h"
void a1(void)
{
	#ifdef   LANDIS_DEBUG
		printf("debug:this is within a1 function.\n");
	#else
		printf("release:this is within a1 function.\n");
	#endif
}
void b1(void)
{
	#ifdef   LANDIS_DEBUG
		printf("debug:this is within b1 function.\n");
	#else
		printf("release:this is within b1 function.\n");
	#endif
}
