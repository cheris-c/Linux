#!/bin/bash

read -t 30 -p "Please input your name: " name   #提示用户输入，等待30s，把输入保存至变量name中
echo "Name is $name"

read -s -t 30 -p "Please enter your age : " age #age是隐私，所以用“-s”选项隐藏输入
echo "\n"
echo  "Age is $age"

read -n 1 -t 30 -p "Please select you gender[M/F] : " gender #使用"-n 1"选项只接收一个字符就会执行（都不用输入回车 ）都不用输入回车
echo "\n"
echo "Sex is $gender"

