#!/bin/bash

echo 使用return设置函数返回值
func ()
{
    for ((i=1; i<=6; i++))
    {
        if [ $i -eq 5 ]
        then
            return $i
        fi
    }
}

func
echo "函数func的返回值为：$?"
echo 使用return命令返回函数返回值时，要尽快取值，否则会被后续执行的命令的返回值覆盖,return返回的命令只能在0~255之间
