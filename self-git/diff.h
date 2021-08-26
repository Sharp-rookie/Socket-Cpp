#include "git.h"

bool find_diff(int param_num, const char param[][301]);

bool diff()
{
    printf("git diff\n\n");

    //获取目录
    std::string work_dir, stage_dir;
    char buf[301];
    getcwd(buf, sizeof(buf));
    work_dir = buf;
    stage_dir = buf;
    stage_dir += "/.git/stage";

    //读入两个目录下的文件
    struct dirent *work_stdinfo, *stage_stdinfo;
    DIR *read_dir;
    std::string file;
    char work_file[100][301], stage_file[100][301];
    memset(work_file, 0, sizeof work_file);
    memset(stage_file, 0, sizeof stage_file);
    int count1 = 0, count2 = 0;

    //读入工作目录下的文件名
    read_dir = opendir(work_dir.c_str());
    while (((work_stdinfo = readdir(read_dir))) != 0)
    {
        if (work_stdinfo->d_name[0] != '.')
            strcpy(work_file[count1++], work_stdinfo->d_name);
        else
            continue;
    }
    closedir(read_dir);

    //读入暂存区下的文件名
    read_dir = opendir(stage_dir.c_str());
    while (((stage_stdinfo = readdir(read_dir))) != 0)
    {

        if (stage_stdinfo->d_name[0] != '.')
            strcpy(stage_file[count2++], stage_stdinfo->d_name);
        else
            continue;
    }
    closedir(read_dir);

    //比较异同
    for (int i = 0; i < count1; i++)
        for (int j = 0; j < count2; j++)
        {
            if (strcmp(work_file[i], stage_file[j]) == 0 && strcmp(work_file[i], "git") != 0)
            {
                char cmp[2][301];
                memset(cmp, 0, sizeof(cmp));
                strcpy(cmp[0], work_dir.c_str());
                strcat(cmp[0], "/");
                strcat(cmp[0], work_file[i]);
                strcpy(cmp[1], stage_dir.c_str());
                strcat(cmp[1], "/");
                strcat(cmp[1], stage_file[j]);

                //比较文件是否相同
                FILE *f1 = fopen(cmp[0], "r");
                FILE *f2 = fopen(cmp[1], "r");

                while ((fgetc(f1) == fgetc(f2)) && (fgetc(f1) != EOF) && (fgetc(f2) != EOF))
                    continue;
                if (fgetc(f1) != EOF || fgetc(f2) != EOF)
                {
                    printf("%s: \n\n", work_file[i]);
                    find_diff(2, cmp);
                    printf("\n\n");
                }

                fclose(f1);
                fclose(f2);
            }
        }

    printf("git diff finish!\n");
    return true;
}

bool find_diff(int param_num, const char param[][301])
{
    if (param_num != 2)
        return false;

    //打开文件
    FILE *A, *B;
    if ((A = fopen(param[0], "r")) == 0 || (B = fopen(param[1], "r")) == 0)
    {
        printf("文件打开失败！\n");
        return false;
    }

    //逐行比较文件
    char buf1[301], buf2[301];
    while (fgets(buf1, 301, A) != 0 && fgets(buf2, 301, B) != 0)
    {
        while (buf1[strlen(buf1) - 1] == '\n' || buf1[strlen(buf1) - 1] == '\r') //清除结尾回车、换行键
            buf1[strlen(buf1) - 1] = '\0';

        while (buf2[strlen(buf2) - 1] == '\n' || buf2[strlen(buf2) - 1] == '\r') //清除结尾回车、换行键
            buf2[strlen(buf2) - 1] = '\0';

        if (strcmp(buf1, buf2) == 0)
        {
            printf("%s\n", buf1);
            continue;
        }
        else
        {
            printf("-%s\n+%s\n", buf1, buf2);
        }
    }

    //若 param[0] 比 param[1] 行数多
    while (fgets(buf1, 301, A) != 0)
    {
        while (buf1[strlen(buf1) - 1] == '\n' || buf1[strlen(buf1) - 1] == '\r') //清除结尾回车、换行键
            buf1[strlen(buf1) - 1] = '\0';
        printf("-%s\n", buf1);
    }

    //若 param[0] 比 param[1] 行数少
    while (fgets(buf2, 301, B) != 0)
    {
        while (buf2[strlen(buf2) - 1] == '\n' || buf2[strlen(buf2) - 1] == '\r') //清除结尾回车、换行键
            buf2[strlen(buf2) - 1] = '\0';
        printf("+%s\n", buf2);
    }

    fclose(A);
    fclose(B);

    return true;
}