#!/bin/bash

echo "使用C式for循环"
for ((i=1; i <= 5; i++))
do
    echo "i = $i"
done

echo ""
for ((i=1, j=5; i<=5, j>=1; i++, j--))
do
    echo "i = $i"
    echo "j = $j"
done
