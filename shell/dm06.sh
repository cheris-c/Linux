#!/bin/bash

echo "This current process is $$" #打印当前进程pid

find ./ -name hello.sh & #放入后台执行

echo "This current process is $!" #打印最后一个进程pid
