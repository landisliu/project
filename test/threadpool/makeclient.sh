#!/bin/sh
cmd=""
for i in $(seq 4000)
do
	cmd=${cmd}"./client &"
done
eval $cmd
