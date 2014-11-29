#!/bin/sh
UserFile:=a b
file:=$(foreach,n,$(UserFile),$(n).o)
echo $(file)
