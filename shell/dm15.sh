#!/bin/bash

num=1
echo "at begining, the num = $num"
for num in 1 2 3 4 5 6 7
do
    num=$[$num+1] #num=$(($num+1))
    echo "the change, the num = $num"
done
num=100;
echo "after for in, the num = $num"
