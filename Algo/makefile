CC=gcc
all:searchtree quick test
searchtree:searchtree.o
	$(CC) searchtree.o -o searchtree
searchtree.o:searchtree.c helper.h
	$(CC) -c searchtree.c -o searchtree.o

quick:quick.o
	$(CC) quick.o -o quick
quick.o:quick.c helper.h
	$(CC) -c quick.c -o quick.o

test:test.o
test.o:test.c
clean:
	rm -rf searchtree quick searchtree.o quick.o test.o test

