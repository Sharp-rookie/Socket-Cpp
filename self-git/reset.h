#include "git.h"

bool reset(char long_option[301])
{ /*--workdir 用暂存区内容覆盖工作目录内容
    --cathe 用本地仓库内容覆盖暂存区内容*/

    //打印指令
    printf("git --%s\n", long_option);

    //获取目录
    std::string dir, target_dir;
    char buf[301];
    getcwd(buf, sizeof(buf));
    dir = buf;
    target_dir = buf;

    if (strcmp(long_option, "cathe") == 0)
    {
        target_dir += "/.git/stage";
        dir += "/.git/local";
    }
    else if (strcmp(long_option, "workdir") == 0)
    {
        dir += "/.git/stage";
    }
    else
    {
        printf("option wrong!\n");
        return false;
    }

    //dir内容覆盖target_dir
    struct dirent *stdinfo;
    DIR *work_dir;
    std::string file;

    //先删除dir中的文件
    work_dir = opendir(target_dir.c_str());
    while (((stdinfo = readdir(work_dir))) != 0)
    {
        //获取文件路径
        file = target_dir;
        file += "/";
        if (stdinfo->d_name[0] != '.' && strcmp(stdinfo->d_name, "git") != 0)
        {
            file += stdinfo->d_name;
            printf("%s\n", file.c_str());
            remove(file.c_str());
        }
        else
            continue;
    }
    closedir(work_dir);

    //再移动dir到target_dir
    std::string file_old, file_new;
    work_dir = opendir(dir.c_str());
    while (((stdinfo = readdir(work_dir))) != 0)
    {
        //获取文件路径
        file_old = dir;
        file_old += "/";
        file_new = target_dir;
        file_new += "/";
        if (stdinfo->d_name[0] != '.' && strcmp(stdinfo->d_name, "git") != 0)
        {
            file_old += stdinfo->d_name;
            file_new += stdinfo->d_name;
        }
        else
            continue;

        //copy之
        if (file_copy(file_old.c_str(), file_new.c_str()) == false)
            return false;
    }
    closedir(work_dir);

    printf("git reset finish!\n");
    return true;
}