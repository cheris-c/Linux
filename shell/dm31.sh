#!/bin/bash
 
dir=`ls /log/rating/chf_cg_offline`
DIR_PATH="/log/rating/chf_cg_offline/"
file_list=""

for fi in $dir
do
    FILE_NAME="${DIR_PATH}${fi}"
    echo $FILE_NAME
    create_date=`stat -c %Y $FILE_NAME`
    b=`date +%s`
    if [ $[ $b - $a ] -lt 24*3600 ];then
       file_list = "$file_list $FILE_NAME"
    fi
done
 
echo file_list
echo "done"