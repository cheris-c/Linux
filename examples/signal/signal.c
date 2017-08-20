#include <stdio.h>
#include <signal.h>


void handler_sigint(int signo)
{
    printf("recv SIGINT\n");
}

int main()
{
    int i = 5;
    signal(SIGINT, handler_sigint);
    while (i--)
    {
        printf("hello\n");
        sleep(2);
    }

    return 0;
}
