all: tpool client server
tpool:testpool.o threadpool.o
	$(CC) -o tpool testpool.o threadpool.o -lpthread
testpool.o:threadpool.h testpool.c
threadpool.o:threadpool.h threadpool.c
client:client.c
	$(CC) client.c -o client -lpthread
server:server.c threadpool.h
server:server.o threadpool.o
	$(CC) -o server server.o threadpool.o -lpthread
clean:
	rm -rf *.o tpool client server
