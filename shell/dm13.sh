#!/bin/bash

echo select命令的使用
select choose in 鸡 鸭 鱼 肉 其他
do
    break
done
echo 你喜欢的是$choose

