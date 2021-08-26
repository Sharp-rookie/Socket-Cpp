#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void EXIT(int sig)
{
    printf("收到了信号%d，程序退出。\n", sig);

    //这里加入释放资源的代码

    exit(0);
}

int main()
{
    for (int ii = 0; ii < 100; ii++) //屏蔽掉全部信号
        signal(ii, SIG_IGN);
    signal(SIGINT, EXIT);  //CTRL C
    signal(SIGTERM, EXIT); //kill + id
    while (1)
    {
        sleep(10);
    }
}