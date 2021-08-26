#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int example1()
{
    printf("本程序的进程编号是：%d\n", getpid());

    int ipid = fork();

    sleep(1); // sleep等待进程的生成。

    printf("pid=%d\n", ipid);

    if (ipid != 0)
        printf("父进程编号是：%d\n", getpid());
    else
        printf("子进程编号是：%d\n", getpid());

    sleep(30); // 是为了方便查看进程在shell下用ps -ef|grep book252查看本进程的编号。
}

void fatchfunc() // 父进程流程的主函数
{
    printf("我是老子，我喜欢孩子他娘。\n");
}

void childfunc() // 子进程流程的主函数
{
    printf("我是儿子，我喜欢西施。\n");
}

int example2()
{
    if (fork() > 0)
    {
        printf("这是父进程，将调用fatchfunc()。\n");
        fatchfunc();
    }
    else
    {
        printf("这是子进程，将调用childfunc()。\n");
        childfunc();
    }

    sleep(1);
    printf("父子进程执行完自己的函数后都来这里。\n");
    sleep(1);
}

int ii = 10;

int example3()
{
    int jj = 20;

    if (fork() > 0)
    {
        ii = 11;
        jj = 21;
        sleep(1);
        printf("父进程：ii=%d,jj=%d\n", ii, jj);
    }
    else
    {
        ii = 12;
        jj = 22;
        sleep(1);
        printf("子进程：ii=%d,jj=%d\n", ii, jj);
    }
}

int main()
{
    int jj = 20;

    if (fork() > 0)
    {
        ii = 11;
        jj = 21;
        sleep(1);
        printf("父进程：ii=%d,jj=%d\n", ii, jj);
    }
    else
    {
        ii = 12;
        jj = 22;
        sleep(1);
        printf("子进程：ii=%d,jj=%d\n", ii, jj);
    }
}