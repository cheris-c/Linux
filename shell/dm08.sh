#!/bin/bash

echo 使用test命令进行逻辑判断
echo 判断3是否小于5

if [ 3 -le 5 ]
then
    echo 3 小于 5
fi
echo

echo 判断5是否小于3
if test 5 -le 3
then
    echo 5 小于 3
fi
