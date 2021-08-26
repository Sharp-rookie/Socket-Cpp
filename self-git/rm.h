#include "git.h"

bool rm(int param_num, const char param[][301])
{ /*同时删除工作目录和暂存区的指定文件*/
    if (param_num < 1)
    {
        printf("参数数量错误，请重新输入！\n");
        return false;
    }

    //打印指令
    printf("git rm ");
    for (int i = 0; i < param_num; i++)
        printf("%s ", param[i]);
    printf("\n\n");

    std::string workdir_file;
    std::string stage_file;
    char buf[301];
    memset(buf, 0, sizeof(buf));
    getcwd(buf, 301);

    //执行删除操作
    for (int i = 0; i < param_num; i++)
    {
        workdir_file = buf;
        stage_file = buf;
        stage_file += "/.git/stage/";
        workdir_file += "/";
        workdir_file += param[i];
        stage_file += param[i];
        //删除工作目录下文件
        if (access(workdir_file.c_str(), 0))
        {
            printf("error: %s does not exist in the work_dir!\n", workdir_file.c_str());
            return false;
        }
        else
        {
            printf("Work Dir: delete %s succeed!\n", workdir_file.c_str());
            remove(workdir_file.c_str());
        }

        //删除暂存区文件
        if (access(stage_file.c_str(), 0))
            printf("warning: %s does not exist in the stage_dir!\n", stage_file.c_str());
        else
        {
            printf("Stage Dir: delete %s succeed!\n", stage_file.c_str());
            remove(stage_file.c_str());
        }
    }

    printf("git rm finish!\n");
    return true;
}