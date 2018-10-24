#########################################################################
# File Name: case01.sh
# Description:  监控脚本实例 
# Author: Actually
# Created Time: 2017年11月21日 星期二 16时57分11秒
#########################################################################
#!/bin/bash

echo 获取剩余交换空间
swap_free=`free -m | grep Swap | awk '{print $4}'`
if ((swap_free < 15))
then
    echo 交换空间剩余不足
fi
echo 交换空间还剩余$swap_free
echo

echo 获取剩余普通内存空间
mem_free=`free -m | grep Mem | awk '{print $4}'`
if ((mem_free < 15))
then
    echo 内存空间剩余不足
fi
echo 内存空间还剩$mem_free
echo

echo 获取硬盘剩余空间
disk_free=`df -h | grep /dev/mapper/centos-root | awk '{print $5}' | cut -f 1 -d "%"`
if ((disk_free < 15))
then
    echo 硬盘/dev/mapper/centos-root剩余空间不足
fi
echo "磁盘/dev/mapper/centos-root的剩余空间为$(( 100-$disk_free ))%"
