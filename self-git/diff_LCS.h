#include "git.h"

bool find_diff_LCS(int param_num, const char param[][301]);

bool diff_LCS()
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
                    find_diff_LCS(2, cmp);
                    printf("\n\n");
                }

                fclose(f1);
                fclose(f2);
            }
        }

    printf("git diff finish!\n");
    return true;
}

bool find_diff_LCS(int param_num, const char param[][301])
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

    //字符串数组保存两个文件
    char f1[DIFF_MAX_ROW_NUM][301], f2[DIFF_MAX_ROW_NUM][301];
    memset(f1, 0, sizeof(f1));
    memset(f2, 0, sizeof(f2));
    int i = 0;
    while (fgets(f1[i], 301, A) != 0)
    {
        if (f1[i][strlen(f1[i]) - 1] == '\n' || f1[i][strlen(f1[i]) - 1] == '\r') //清除结尾回车、换行键
            f1[i][strlen(f1[i]) - 1] = '\0';
        i++;
    }

    int j = 0;
    while (fgets(f2[j], 301, B) != 0)
    {
        if (f2[j][strlen(f2[j]) - 1] == '\n' || f2[j][strlen(f2[j]) - 1] == '\r') //清除结尾回车、换行键
            f2[j][strlen(f2[j]) - 1] = '\0';
        j++;
    }

    //初始化dp表格
    int lcs_table[201][201];          //dp表格
    int lcs_sequency_table[201][201]; //记录dp表格每个单元的来源位置
    memset(lcs_table, 0, sizeof(lcs_table));
    memset(lcs_sequency_table, 0, sizeof(lcs_sequency_table));

    //生成dq表格，并记录来源位置：1为左、2为上、3为左上
    int m, n;
    for (m = 1; m < i; m++)
    {
        for (n = 1; n < j; n++)
        {
            if (strcmp(f1[m], f2[n]) == 0)
            {
                lcs_table[m][n] = lcs_table[m - 1][n - 1] + 1;
                lcs_sequency_table[m][n] = 3;
            }
            else
            {
                lcs_table[m][n] = lcs_table[m][n - 1] > lcs_table[m - 1][n] ? lcs_table[m][n - 1] : lcs_table[m - 1][n];
                lcs_sequency_table[m][n] = lcs_table[m][n - 1] >= lcs_table[m - 1][n] ? 1 : 2;
            }
            //printf("%2d ", lcs_sequency_table[m][n]);
            //printf("%2d ", lcs_table[m][n]);
        }
        //printf("\n");
    }

    //生成diff输出序列
    char diff_output[2 * DIFF_MAX_ROW_NUM][301];
    int count = 0;
    for (m = i, n = j; m > 0 && n > 0;)
    {
        if (lcs_sequency_table[m][n] == 3)
        {
            strcpy(diff_output[count++], f1[m]);

            m--;
            n--;
        }
        else if (lcs_sequency_table[m][n] == 2)
        {
            char str[301];
            strcpy(str, "-");
            strcat(str, f1[m]);
            strcpy(diff_output[count++], str);
            m--;
        }
        else
        {
            char str[301];
            strcpy(str, "+");
            strcat(str, f2[n]);
            strcpy(diff_output[count++], str);
            n--;
        }
    }
    if (m == 0)
        for (n; n > 0; n--)
        {
            char str[301];
            strcpy(str, "+");
            strcat(str, f2[n]);
            strcpy(diff_output[count++], str);
            n--;
        }
    else if (n == 0)
        for (m; m > 0; m--)
        {
            char str[301];
            strcpy(str, "-");
            strcat(str, f1[m]);
            strcpy(diff_output[count++], str);
            m--;
        }

    //打印输出序列
    for (count--; count > 0; count--)
        printf("%s\n", diff_output[count]);
    printf("\n");

    fclose(A);
    fclose(B);

    return true;
}