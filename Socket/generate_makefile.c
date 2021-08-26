#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("请指定目录名。\n");
        return -1;
    }

    char strfilename[2][100][31]; // 存放文件名列表。
    memset(strfilename, 0, sizeof(strfilename));

    DIR *dir; // 定义目录指针

    // 打开目录
    if ((dir = opendir(argv[1])) == 0)
        return -1;

    // 用于存放从目录中读取到的文件和目录信息
    struct dirent *stdinfo;

    int count1 = 0;
    int count2 = 0;
    while (1)
    {
        // 读取一条记录并显示到屏幕
        if ((stdinfo = readdir(dir)) == 0)
            break;

        if ((stdinfo->d_type == 8) && (strcmp(stdinfo->d_name + strlen(stdinfo->d_name) - 4, ".cpp") == 0))
        {
            printf("%s\n", stdinfo->d_name);
            strncpy(strfilename[0][count1++], stdinfo->d_name, strlen(stdinfo->d_name) - 4);
        }

        if ((stdinfo->d_type == 8) && (strcmp(stdinfo->d_name + strlen(stdinfo->d_name) - 2, ".c") == 0))
        {
            printf("%s\n", stdinfo->d_name);
            strncpy(strfilename[1][count2++], stdinfo->d_name, strlen(stdinfo->d_name) - 2);
        }
    }

    closedir(dir); // 关闭目录指针

    FILE *fp = 0;

    if ((fp = fopen("Makefile", "w")) == 0)
    {
        printf("fopen(Makefile) failed.\n");
        return -1;
    }

    int ii = 0;
    int jj = 0;

    // 生成all:部分。
    fprintf(fp, "all:");
    for (jj = 0; jj < 2; jj++)
        for (ii = 0; *(strfilename[jj][ii]) != 0; ii++)
            fprintf(fp, "%s ", strfilename[jj][ii]);
    fprintf(fp, "\n\n");

    // 生成每个程序的编译指令。
    for (ii = 0; *(strfilename[0][ii]) != 0; ii++)
    {
        fprintf(fp, "%s:%s.cpp\n", strfilename[0][ii], strfilename[0][ii]);
        fprintf(fp, "\tg++ -o %s %s.cpp\n\n", strfilename[0][ii], strfilename[0][ii]);
    }
    for (ii = 0; *(strfilename[1][ii]) != 0; ii++)
    {
        fprintf(fp, "%s:%s.c\n", strfilename[1][ii], strfilename[1][ii]);
        fprintf(fp, "\tgcc -o %s %s.c\n\n", strfilename[1][ii], strfilename[1][ii]);
    }

    // 生成clean:部分。
    fprintf(fp, "clean:\n\trm -rf ");
    for (jj = 0; jj < 2; jj++)
        for (ii = 0; *(strfilename[jj][ii]) != 0; ii++)
            fprintf(fp, "%s ", strfilename[jj][ii]);
    fprintf(fp, "\n");

    fclose(fp); // 关闭文件指针。
}