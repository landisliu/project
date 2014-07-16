all:main
CC=gcc
INSTALLDIR=~/mylib
FILENAME=filetransfer1.c
main:main.o userlib.o
	$(CC) main.o userlib.o -o main
userlib.o:userlib.c userlib.h
	$(CC) -g -c userlib.c
main.o:$(FILENAME) userlib.h
	$(CC) -g -c $(FILENAME) -o main.o
clean:
	-rm main.o userlib.o
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
