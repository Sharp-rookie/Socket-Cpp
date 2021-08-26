#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("本程序的进程编号是：%d\n", getpid());
    sleep(30); // 是为了方便查看进程在shell下用ps -ef|grep book251查看本进程的编号。
}