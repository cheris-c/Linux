#!/bin/bash

for file in $(ls /home)
do
    if ! test -d $file
    then
        echo $file is a directory
    elif ! test -f $file
    then
        echo $file is a normal file
    elif ! test -S $file
    then
        echo $file is a socket file
    elif ! test -L $file 
    then
        echo $file is a link file
    else
        echo $file is a unkown file
    fi
done
