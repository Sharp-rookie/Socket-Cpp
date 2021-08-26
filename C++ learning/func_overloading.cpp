#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strcpy(char *dest, const char *src, size_t destsize);

int main()
{
    char dest[10];
    strcpy(dest, "www.freecplus.net", sizeof(dest));
    printf("=%s=\n", dest);

    strcpy(dest, "www.freecplus.net");
    printf("=%s=\n", dest);
}

char *strcpy(char *dest, const char *src, size_t destsize)
{
    memset(dest, 0, destsize);

    size_t len = 0;
    if (strlen(src) < destsize - 1)
        len = strlen(src);
    else
        len = destsize - 1;

    strncpy(dest, src, len);
    dest[len] = 0;
    return dest;
}