#include "git.h"

bool status()
{ /*列出工作目录下的被修改过的文件*/

    //打印指令
    printf("git status\n\n");

    int count = 0;

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
    char common[100][301];
    int count3 = 0;
    memset(common, 0, sizeof(common));

    //先列出新增文件
    for (int i = 0; i < count1; i++)
    {
        int flag = 0;
        for (int j = 0; j < count2; j++)
        {
            if (strcmp(work_file[i], stage_file[j]) == 0 && strcmp(work_file[i], "git") != 0)
            {
                strcpy(common[count3++], work_file[i]);
                flag = 1;
            }
        }
        if (flag == 0 && strcmp(work_file[i], "git") != 0)
        {
            printf("%s is to be added\n", work_file[i]);
            count++;
        }
    }

    //比较共有文件内容是否相同
    std::string file1, file2;
    char ch1, ch2;
    for (int i = 0; i < count3; i++)
    {
        file1 = work_dir;
        file1 += "/";
        file1 += common[i];
        file2 = stage_dir;
        file2 += "/";
        file2 += common[i];

        FILE *f1 = fopen(file1.c_str(), "r");
        FILE *f2 = fopen(file2.c_str(), "r");

        while ((fgetc(f1) == fgetc(f2)) && (fgetc(f1) != EOF) && (fgetc(f2) != EOF))
            continue;
        if (fgetc(f1) != EOF || fgetc(f2) != EOF)
        {
            count++;
            printf("%s is motified\n", common[i]);
        }

        fclose(f1);
        fclose(f2);
    }

    if (count == 0)
        printf("nothing to be added\n");

    printf("\ngit status finish!\n");
    return true;
}