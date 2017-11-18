#!/bin/bash

echo "不使用双引号"
for str in fish meat Italian Pizza
do 
    echo "今天晚上的菜是: $str"
done

echo 

echo "使用双引号"
for str in fish meat "Italian Pizza"
do 
    echo "今天晚上的菜是：$str"
done
