#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define MAX_ACTION_NUM 30   //最大动作数量
#define MAX_SHORT_OPT_NUM 5 //每个动作最大短选项数量
#define MAX_LONG_OPT_NUM 5  //每个动作最大长选项数量
#define MAX_PARAM_NUM 5     //每个选项最大参数数量

#define DIFF_MAX_ROW_NUM 200 //diff读取的文件的最大行数s

bool file_copy(const char *old_file, const char *new_file); //文件copy函数的声明