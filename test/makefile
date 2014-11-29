CC=gcc
worm: worm.o mysqlhelper.o
	$(CC) -g -o worm worm.o mysqlhelper.o  -lmysqlclient
mysqlhelper.o:mysqlhelper.c
	$(CC) -c -g mysqlhelper.c 	-I/usr/include/mysql/
worm.o:worm.c
	$(CC) -c -g worm.c  -I/usr/include/mysql/
makelib:
	$(CC) -fPIC -shared -o libhello.so a.c b.c
install:
	sudo cp libhello.so /usr/lib/
	names:= a b c d
	files:= $(foreach n,$(names),$(n).o)
	$(error $(files))
clean:
	rm -rf *.o *.so main worm mysqlhelper core
	sudo rm -rf /usr/lib/libhello.so
