#!/bin/bash

echo if-then结构的嵌套使用
echo 判断3和5的关系

if [ 3 -le 5 ]
then
    if [ 3 -eq 5 ]
    then
        echo 3 等于 5
    fi

    if [ 3 -gt 5 ]
    then 
        echo 3 大于 5
    fi
    
    echo 3 小于 5
fi
