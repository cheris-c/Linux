/*************************************************************************
  > File Name: procwrite.c
  > Description: 
  > Author: Actually
  > Created Time: 2017年08月24日 星期四 21时52分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"
#define BUF_SIZE  1024

/*************************************************************************************
 * #include <sys/stat.h>
 * #include <sys/types.h>
 * int mknod(const char *path, mode_t mode, dev_t dev);
 * int mkfifo(const char *path, mode_t mode);
 *      path 参数为创建有名管道的全路径名；mode为创建的有名管道的模式，指明其存取权限；dev
 * 为设备值，该值取决于文件创建的种类，他只在创建设备文件时才会用到。这两个函数调用成功时
 * 都返回0，失败返回-1。
 *      使用有名管道时必须先用open函数将其打开。因为有名管道是一个可以存在于硬盘上的文件，
 * 而管道时存在于内存中的特殊文件。
 *      调用open()打开有名管道的进程可能会被阻塞。但如果用读写方式(O_RDWR)打开，则一定不
 * 会导致阻塞；如果以只读方式打开(O_RDONLY)打开，则调用open()函数的进程会被阻塞直到有写方
 * 打开管道；同样以只写方式(O_WRONLY)打开也会阻塞，直到有读方打开管道。
 *
 * #include <unistd.h>
 * int unlink(const char *path);
 *      unlink系统调用从文件系统中删除一个文件，如果文件的链接数为0且没有进程打开这个文件，
 *则文件被删除且占用的磁盘空间被释放。如果文件的链接数虽然为0，但是有进程打开这个文件，则
 *文件暂时不能删除，直到所有打开该文件的进程都结束时文件才被删除。
 *      参数pathname若指向一个符号链接，则该链接被删除。若参数pathname指向一个socket(套接
 * 字文件)、FIFO(命名管道)或设备文件时，该名字被删除，但已经打开这些文件的进程仍然可以使用这
 * 些特殊文件。
 * *************************************************************************************/

int main()
{
    int fd;
    char buf[BUF_SIZE] = "Hello procread, I come from process named procwrite!\n";

    umask(0);
    if (mkfifo(FIFO_NAME, S_IFIFO | 0666) == -1)
    {
	perror("mkfifo error!");
	exit(1);
    }
    
    if (fd = open(FIFO_NAME, O_WRONLY) == -1)
    {
	perror("fopen error!");
	exit(1);
    }

    write(fd, buf, strlen(buf)+1);
    unlink(FIFO_NAME);   
    close(fd);

    return 0;
}
