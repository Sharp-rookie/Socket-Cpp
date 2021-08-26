#include "git.h"

bool commit(const char short_option, const char long_option[301], int param_num, const char param[][301])
{
    /*把暂存区文件 + message信息文本文件作为新版本传到.git/local的一个新版本文件夹下*/
    if (param_num == 0)
    {
        printf("commit need for message!\n");
        return false;
    }
    else if (param_num > 1)
    {
        printf("number of parameters wrong!\n");
        return false;
    }

    //打印指令
    if (short_option != 0 || long_option[0] != 0) //若有执行m选项
    {

        printf("git commit ");
        if (short_option != 0)
            printf("-%c ", short_option);
        if (long_option[0] != 0)
            printf("--%s ", long_option);
        printf("%s ", param[0]);

        printf("message: %s\n", param[0]);
    }
    else
    {
        printf("commit need for message!\n");
        return false;
    }

    //版本数(暂时用时间代替)
    time_t time_now;
    time(&time_now);
    struct tm *tmn;
    tmn = localtime(&time_now);
    char name[301];
    memset(name, 0, sizeof(name));
    sprintf(name, "%d.%d.%d %d:%d:%d", tmn->tm_year + 1900, tmn->tm_mon + 1, tmn->tm_mday, tmn->tm_hour,
            tmn->tm_min, tmn->tm_sec);

    //打开暂存区和本地仓库
    DIR *stage_dir;
    char stage[300], local[300];
    memset(local, 0, sizeof(local));
    memset(stage, 0, sizeof(stage));
    getcwd(stage, 300);
    getcwd(local, 300);
    strcat(stage, "/.git/stage");
    strcat(local, "/.git/local/");
    strcat(local, name);
    printf("暂存目录：%s\n本地仓库：%s\n\n", stage, local);

    if ((stage_dir = opendir(stage)) == 0)
        return false;

    if (mkdir(local, 0755) == -1)
        return false;

    //move暂存区内容到本地仓库
    struct dirent *stdinfo;
    std::string stage_file, local_file; //工作、暂存目录下文件地址

    char file_delete[100][301]; //记录暂存区的文件名，循环后copy后删除之
    int count = 0;

    while (((stdinfo = readdir(stage_dir))) != 0)
    {
        //获取文件路径
        stage_file = stage;
        stage_file += "/";
        local_file = local;
        local_file += "/";

        if (stdinfo->d_name[0] != '.')
        {
            local_file += stdinfo->d_name;
            stage_file += stdinfo->d_name;
            strcpy(file_delete[count++], stage_file.c_str());
        }
        else
            continue;

        //mv
        if (file_copy(stage_file.c_str(), local_file.c_str()) == false) //移动文件
            return false;
        printf("%-65s--->    %-65s\n", stage_file.c_str(), local_file.c_str());
    }

    for (count = count ? count - 1 : 0; count > -1; count--) //防止暂存区本身就是空的情况
        remove(file_delete[count]);                          //清空暂存区

    //保存message信息
    strcat(local, "/message.txt");
    FILE *m;
    m = fopen(local, "w");
    fprintf(m, "%s", param[0]);
    fclose(m);

    printf("\ngit commit finish\n");

    closedir(stage_dir);

    return true;
}
