#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    //int iret = execl("/bin/lss", "/bin/ls", "-l", "/usr/include/stdio.h", NULL); // /bin/lss不存在，执行不能成功。
    int iret = execl("/bin/ls", "/bin/ls", "-l", "/usr/include/stdio.h", NULL); // 可以调用成功的代码。
    printf("iret=%d\n", iret);
    if (iret == -1)
        printf("%d:%s\n", errno, strerror(errno));
}