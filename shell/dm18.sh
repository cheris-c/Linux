#!/bin/bash

echo "多条件while循环"
num=4
while [ $num -gt 3 -a $num -lt 6 ]
do
    echo num = $num
    let num++
done
