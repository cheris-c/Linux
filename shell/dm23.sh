#!/bin/bash

echo "变量在定义时默认是全局变量。"
echo "定义局部变量时需要使用命令local,定义全局变量的方式如下：local valnum。valnum 可以是单个变量，也可以是一个赋值语句"

num=10
string="hello world"

func()
{
    local num=100
    local string="local value"

    echo "在函数func中，调用获取的变量num值为:$num"
    echo "在函数func中，调用获取的变量string=$string"
    num=$[$num+100]
}

func
echo "在函数func外，变量num的值为：$num"
echo "在函数func外，变量string的值：$string"
