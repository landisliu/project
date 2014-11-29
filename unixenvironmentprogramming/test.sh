#!/bin/sh
for i in $(seq 1000)
do
	./client ./test.c ./abc$i &
done
exit 0	
