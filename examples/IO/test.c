#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>

int main()
{
    printf("%d\n",sizeof(fd_set));
    return 0;
}
