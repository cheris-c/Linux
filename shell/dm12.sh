#!/bin/bash

echo -n 输入一个分数：
read num
case $num in
    1)echo 输入的数值为1;;
    2)echo 输入的数值为2;;
    3)echo 输入的数值为3;;
    4)echo 输入的数值为4;;
    *)echo 输入的数值大于4;;
esac
echo case语句运行结束

#esac作为case结构的结尾，在每一条执行的后面需要添加两个分号作为分支执行结束的标志。
