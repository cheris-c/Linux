#!/bin/bash

#until结构的使用

num=1
echo until循环开始
until [ $num -ge 6 ]
do 
    echo "the current num is $num"
    let num++
done
echo until循环结束
