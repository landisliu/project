all: myprocesspool
myprocesspool:mypool.o mypooltest.o
	$(CC) -o myprocesspool mypool.o mypooltest.o
mypool.o:mypool.c mypool.h
mypooltest.o:mypooltest.c mypool.h
clean:
	rm -rf *.o myprocesspool
rmmsg:
	ipcs -q|grep 'landis'|awk '{v="ipcrm -q " $2;system(v)}'

