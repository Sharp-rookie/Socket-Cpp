#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
    int iret;

    // 调用不成功的代码。
    iret = system("/bin/lss -l /usr/include/stdio.h");
    printf("iret=%d\n", iret);
    if (iret == -1)
        printf("%d:%s\n", errno, strerror(errno));

    // 可以调用成功的代码。
    iret = system("/bin/ls -l /usr/include/stdio.h");
    printf("iret=%d\n", iret);
    if (iret == -1)
        printf("%d:%s\n", errno, strerror(errno));
}