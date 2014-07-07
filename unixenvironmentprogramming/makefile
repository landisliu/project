all:main
CC=gcc
F_Name=10_5.c
main:main.o helper.o
main.o:$(F_Name)
	$(CC) -c $(F_Name) -o main.o
helper.o:helper.c

clean:
	rm -f helper.o main.o
