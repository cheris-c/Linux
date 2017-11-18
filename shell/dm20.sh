# break的复杂使用
#!/bin/bash

echo "break命令中断for循环"
for ((i=1; i<=5; i++))
do
    for ((j=1; j<=7; j++))
    do
        echo "i = $i"
        echo "j = $j"
       
        if [ $j -eq 5 ]
        then
            echo 退出内层循环后继续外层循环
            break;
        fi;
        
        if [ $i -eq 3 ]
        then
            echo 退出两层循环
            break 2;
        fi
    done
done

echo 结束整个循环



