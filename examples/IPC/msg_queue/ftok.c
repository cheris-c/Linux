/*************************************************************************
  > File Name: ftok.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月26日 星期六 17时20分58秒
 ************************************************************************/

#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

/*
 *      消息队列随着内核而存在，每个消息队列在系统范围内对应唯一的键值。要获得一个消息
 * 队列的描述符，只需提供该消息队列的键值即可，该键值通常由函数ftok返回。
 * #include <sys/types.h>
 * #include <sys/ipc.h>
 * key_t ftok(const char *pathname, int proj_id);
 *      ftok函数根据pathname和proj_id这两个参数生成一个唯一的键值。该函数执行成功
 *返回一个键值，失败返回-1.
*       参数pathname在系统一定要存在，并且进程有权访问，参数proj_id的取值范围为1~255
 */

int main()
{
    int i;
    for (i = 1; i <= 5; i++)
    {
        printf("key[%d] = %ul\n", i, ftok(".", i));
    }

    return 0;
}
