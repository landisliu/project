all:main grep strindex test reversepoland
CC=gcc
INSTALLDIR=~/mylib
FILENAME=filetransfer1.c
main:main.o userlib.o
	$(CC) main.o userlib.o -o main
userlib.o:userlib.c userlib.h
	$(CC) -g -c userlib.c
main.o:$(FILENAME) userlib.h
	$(CC) -g -c $(FILENAME) -o main.o
grep:grep.o
	$(CC) grep.o -o grep
grep.o:grep.c
	$(CC) -c grep.c -o grep.o
strindex:strindex.o
strindex.o:strindex.c
reversepoland:reversepoland.o
reversepoland.o:reversepoland.c
clean:
	-rm -rf main.o userlib.o grep.o grep strindex.o strindex test.o test
install:main
	@if [ -d $(INSTALLDIR) ]; \
	then \
		cp main $(INSTALLDIR); \
		chmod a+x $(INSTALLDIR)/main; \
		chmod og-w $(INSTALLDIR)/main; \
		echo "Installed in $(INSTALLDIR)"; \
	else \
		echo "Sorry , $(INSTALLDIR) does not exist"; \
	fi
