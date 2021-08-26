#include "git.h"

bool add(int short_option_now)
{ /*无参数时，把工作目录文件全部传到.git/stage下
  含参数 * 时，只把工作目录下相对暂存区有更改的文件传到.git/stage下*/
    //打印指令
    printf("git add %c\n", short_option_now);

    //工作目录和暂存区
    char dir[300], stage[300];
    memset(dir, 0, sizeof(dir));
    memset(stage, 0, sizeof(stage));
    getcwd(dir, 300);
    getcwd(stage, 300);
    strcat(stage, "/.git/stage");
    printf("工作目录：%s\n暂存目录：%s\n\n", dir, stage);

    //打开工作目录
    DIR *work_dir;
    if ((work_dir = opendir(dir)) == 0)
        return false;

    //copy工作目录内容到暂存目录
    struct dirent *stdinfo;
    char work_file[300], stage_file[300]; //工作、暂存目录下文件地址
    memset(work_file, 0, sizeof(work_file));
    memset(stage_file, 0, sizeof(stage_file));
    while (1)
    {
        if (((stdinfo = readdir(work_dir))) == 0)
            break;
        strcpy(work_file, dir);
        strcat(work_file, "/");
        strcpy(stage_file, stage);
        strcat(stage_file, "/");
        if (stdinfo->d_name[0] != '.')
        {
            strcat(work_file, stdinfo->d_name);
            strcat(stage_file, stdinfo->d_name);
        }
        else
            continue;

        if (file_copy(work_file, stage_file) == false) //移动文件
            return false;

        printf("%-65s --->    %-65s\n", work_file, stage_file);
    }

    printf("\ngit add finish\n");

    closedir(work_dir);
    return true;
}