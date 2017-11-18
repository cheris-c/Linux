#!/bin/bash

echo if-then结构的嵌套使用
echo 判断3和5的关系

if [ 3 -lt 5 ]
then
    echo 3 小于 5
elif [ 3 -eq 5]
then
    echo 3 等于 5
else
    echo 3 大于 5
fi
