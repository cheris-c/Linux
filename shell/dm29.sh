#!/bin/bash

echo "使用systime()获取秒数"
echo | gawk '{print systime()}'
echo

echo "使用mktime()获取秒数"
echo | gawk '{print mktime("2014 03 28 14 12 12")}'
echo

echo 使用strftime输出当前时间
echo | gawk '{print strftime("%D", systime())}'
echo | gawk '{print strftime("%e", systime())}'
echo | gawk '{print strftime("%w", systime())}'
echo strftime函数有很多格式符，需要可以自己查一下
