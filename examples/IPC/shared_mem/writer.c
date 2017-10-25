/*************************************************************************
  > File Name: writer.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月07日 星期四 15时26分15秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "share_mem.h"

int main()
{
    int  semid, shmid;
    char *shmaddr;
    char write_str[SHM_SIZE];

    if ((shmid = createshm(".", 'm', SHM_SIZE)) == -1)
    {
        exit(1);
    }

    if ((shmaddr = (char *)shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("attch shared memory error!\n");
        exit(1);
    }

    if ((semid = createsem(".", 's', 1, 1)) == -1)
    {
        exit(1);
    }

    while (1)
    {
        wait_sem(semid, 0);
        sem_p(semid, 0);

        printf("writer : ");
        fgets(write_str, 1024, stdin);
        int len = strlen(write_str) -1;
        write_str[len] = '\0';
        strcpy(shmaddr, write_str);
        sleep(5);

        sem_v(semid, 0);
        sleep(5);
    }

    return 0;
}
