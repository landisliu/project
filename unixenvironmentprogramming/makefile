all:server client
server:server6.o
	$(CC) server6.o -o server
client:client6.o
	$(CC) client6.o -o client
server6.o:server6.c 
client6.o:client6.c
clean:
	rm -rf abc server client *.o  /tmp/serverlog /tmp/clientlog abc*
run:
	./server>/tmp/serverlog
	./test.sh>/tmp/clientlog
