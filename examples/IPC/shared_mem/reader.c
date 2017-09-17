/*************************************************************************
  > File Name: reader.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年09月07日 星期四 15时26分28秒
 ************************************************************************/

#include <stdio.h>
#include "share_mem.h"

int main()
{
    int semid, shmid;
    char *shmaddr;

    if ((shmid = createshm(".", 'm', SHM_SIZE)) == -1)
    {
        exit(1);
    }

    if ((shmaddr = (char *)shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("attch shared memory error!\n");
        exit(1);
    }

    if (semid = opensem(".", 's') == -1)
    {
        exit(1);
    }

    while (1)
    {
        printf("writer : ");
        wait_sem(semid, 0);
        sem_p(semid, 0);

        printf("%s\n", shmaddr);
        sem_v(semid, 0);
        sleep(5);
    }

    return 0;
}
