#!/bin/bash

echo "数组作函数参数"

num1=(1, 2, 3, 4, 5)
num2=(a, b, c, d, e)

func()
{
    local array1=($1)
    echo "传递的数组1中的数值分别为:${array1[*]}"

    local array2=($2)
    echo "传递的数组2中的数值分别为:${array2[*]}"
}

func "${num1[*]}"
echo 

echo "向函数传递多个数组作为参数"
func "${num1[*]}" "${num2[*]}"
