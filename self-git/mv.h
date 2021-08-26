#include "git.h"

bool mv(int param_num, const char param[][301])
{
    if (param_num != 2)
    {
        printf("参数数量错误，请重新输入！\n");
        return false;
    }

    //打印指令
    printf("git mv %s %s\n\n", param[0], param[1]);

    //执行mv操作
    char work_file[2][300], stage_file[2][300];
    memset(work_file, 0, sizeof(work_file));
    memset(stage_file, 0, sizeof(stage_file));
    //工作目录
    getcwd(work_file[0], sizeof work_file[0]);
    getcwd(work_file[1], sizeof work_file[1]);
    strcat(work_file[0], "/");
    strcat(work_file[1], "/");
    strcat(work_file[0], param[0]);
    strcat(work_file[1], param[1]);
    if (access(work_file[0], 0))
    {
        printf("error: %s does not exist in the work_dir!\n", work_file[0]);
        return false;
    }
    else
    {
        file_copy(work_file[0], work_file[1]);
        remove(work_file[0]);
    }
    //暂存目录
    getcwd(stage_file[0], sizeof stage_file[0]);
    getcwd(stage_file[1], sizeof stage_file[1]);
    strcat(stage_file[0], "/.git/stage/");
    strcat(stage_file[1], "/.git/stage/");
    strcat(stage_file[0], param[0]);
    strcat(stage_file[1], param[1]);
    if (access(stage_file[0], 0))
    {
        printf("warning: %s does not exist in the stage_dir!\n", stage_file[0]);
        return true;
    }
    else
    {
        file_copy(stage_file[0], stage_file[1]);
        remove(stage_file[0]);
    }

    printf("%-30s--->%30s\n\ngit mv finished\n", param[0], param[1]);

    return true;
}