#!/bin/bash

function getDay() {
	data1=1
	data2=2
	data3=3
	echo "$DATE" "$data1" "$data2" "$data3" >> /tmp/test.txt
}

rm /tmp/test.txt

echo "日期	第一列	第二列	第三列" >> /tmp/test.txt
for ((i = 7; i > 0; i--));do
	DATE="`date -d "$i days ago" '+%Y%m%d'`"
	getDay $DATE
done

#发送邮件
START_DATE="`date -d "7 days ago" '+%Y%m%d'`"
END_DATE="`date -d "yesterday" '+%Y%m%d'`"
mail -s "数据统计报表["$START_DATE"~"$END_DATE"]" enumhack@163.com < /tmp/test.txt
