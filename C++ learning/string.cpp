#include <stdio.h>
#include <string>
#include <string.h>
#include <typeinfo>

using namespace std;

int main()
{
    char str1[31];
    memset(str1, 0, sizeof(str1));
    strcpy(str1, "西施");

    string str2 = "沉鱼";
    str2 += str1;
    printf("str2 = %s\n", str2.c_str());

    printf("%ld\t%ld\n", str2.size(), str2.length());

    str2.clear();

    str2 = str1;
    printf("%s\n", str2.c_str());
}