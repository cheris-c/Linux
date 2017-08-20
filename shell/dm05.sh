#!/bin/bash

for i in "$*"
	do 
		echo "This parameter is : $i"
	done

x=1
for y in "$@"
	do 
		echo "This parameter is $x : $y"
		x=$(($x + 1))
	done
