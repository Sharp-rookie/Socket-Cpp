#include "git.h"

bool generate_subdir(const char dir[301]);  //在文件夹dir下生成子文件夹 stage/、local/
bool generate_subfile(const char dir[301]); //在文件夹dir下生成日志 log.txt

bool init(int param_num, const char param[][301])
{ /*init参数缺省值为当前目录，最多支持一个参数，且必须是绝对路径
    在该路径下创建一个空仓库，或重置一个已存在的仓库*/
    if (param_num == 1)
    {
        char repository[301];
        memset(repository, 0, sizeof(repository));
        strcpy(repository, param[0]);

        if (access(repository, 0) == 0) //若仓库已存在，则重置仓库
            rmdir(repository);

        mkdir(repository, 0755);
        strcat(repository, "/.git");
        mkdir(repository, 0755);
        generate_subdir(repository);
        generate_subfile(repository);
    }
    else if (param_num > 1)
    {
        printf("Number of parameters wrong!\n");
        return false;
    }
    else
    {
        char repository[301];
        memset(repository, 0, sizeof repository);
        getcwd(repository, sizeof repository); //缺省目录为当前目录

        if (access(repository, 0) == 0) //若仓库已存在，则重置仓库
            rmdir(repository);

        mkdir(repository, 0755);
        strcat(repository, "/.git");
        printf("%s\n", repository);
        mkdir(repository, 0755);
        generate_subdir(repository);
        generate_subfile(repository);
    }

    printf(" repository init finish!\n");
    return true;
}

bool generate_subdir(const char dir[301])
{
    char subdir[301];
    memset(subdir, 0, sizeof(subdir));
    strcpy(subdir, dir);
    strcat(subdir, "/stage");
    mkdir(subdir, 0755);

    memset(subdir, 0, sizeof(subdir));
    strcpy(subdir, dir);
    strcat(subdir, "/local");
    mkdir(subdir, 0755);

    return true;
}

bool generate_subfile(const char dir[301])
{
    char subfile[301];
    memset(subfile, 0, sizeof(subfile));
    strcpy(subfile, dir);
    strcat(subfile, "/log.txt");
    fopen(subfile, "w");

    return true;
}