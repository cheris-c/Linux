#!/bin/bash

echo 使用取整函数
gawk '{num=int($1); print num}' data.txt
echo 

echo 使用取平方根函数
gawk '{num=sqrt($1); print num}' data.txt
echo 

echo 使用取对数函数
gawk '{num=log($1); print num}' data.txt
