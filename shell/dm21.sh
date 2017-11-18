#!/bin/bash

echo 在函数中使用参数

func()
{
    echo "传入的参数个数为：$#"
    echo "函数名为：$0"
    echo "第一个参数为：$1"
    echo "第二个参数为：$2"
}

echo 调用函数，并传递2个参数
func 1 2
func "hello" "world"

echo 函数的默认返回值取决于最后一个命令的执行结果，因此一般不使用默认返回值
echo "func函数的返回值为：$?"
