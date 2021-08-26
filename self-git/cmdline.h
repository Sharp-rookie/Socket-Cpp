#include "git.h"

class cmdl
{
public:
    char action_name[MAX_ACTION_NUM][301];                           //用于存储动作名称，目前最多30个
    char action_help[MAX_ACTION_NUM][301];                           //用于存储动作的说明
    char action_short_options[MAX_ACTION_NUM][MAX_SHORT_OPT_NUM];    //用于存储每个动作的短选项，目前最多5个
    char action_long_options[MAX_ACTION_NUM][MAX_LONG_OPT_NUM][301]; //用于存储每个动作的长选项，目前最多5个
    int action_option_num[MAX_ACTION_NUM][2];                        //用于存储每个动作的长/短选项的数量,[0]存短选项、[1]存长选项
    int action_num;                                                  //已存储动作的数量

    std::string action_now;                    //从命令行获取的本轮动作
    char short_option_now;                     //从命令行获取的动作短选项
    char long_option_now[301];                 //从命令行获取的动作长选项
    char action_help_now[301];                 //当前动作的说明
    char action_param_now[MAX_PARAM_NUM][301]; //当前动作的选项的参数，目前最多5个
    int action_param_num;                      //当前动作的选项的参数数量

    cmdl();
    ~cmdl();

    bool add_action(const char *action, const char short_opt, const char *long_opt, const int param_num, const char *help);
    bool parse(const int argc, char *argv[]);
};

cmdl::cmdl()
{
    memset(action_name, 0, sizeof(action_name));
    memset(action_help, 0, sizeof(action_help));
    memset(action_short_options, 0, sizeof(action_short_options));
    memset(action_long_options, 0, sizeof(action_long_options));
    memset(action_option_num, 0, sizeof(action_option_num));
    action_num = 0;

    action_now = "";
    short_option_now = 0;
    memset(long_option_now, 0, sizeof(long_option_now));
    memset(action_param_now, 0, sizeof(action_param_now));
    action_param_num = 0;
}

cmdl::~cmdl()
{
    action_num = 0;
}

bool cmdl::add_action(const char *action, const char short_opt, const char *long_opt, const int param_num, const char *help)
{
    int option_num; //当前动作已存储选项的个数

    //action已存在
    for (int i = 0; i < action_num; i++)
    {
        if (strcmp(action_name[i], action) == 0)
        {
            //if (strcmp("", help) != 0)
            strcpy(action_help[i], help); //动作的说明

            if (short_opt != ' ')
            {
                action_short_options[i][option_num] = short_opt; //短选项
                action_option_num[i][0]++;
            }

            if (strcmp(long_opt, "") != 0)
            {
                strcpy(action_long_options[i][option_num++], long_opt); //长选项
                action_option_num[i][1]++;
            }

            action_num++;
            return true;
        }
    }

    //action不存在
    option_num = 0; //新动作，选项短数量清零
    strcpy(action_name[action_num], action);
    strcpy(action_help[action_num], help); //动作的说明

    if (short_opt != ' ')
    {
        action_short_options[action_num][option_num] = short_opt; //短选项
        action_option_num[action_num][0]++;
    }

    if (strcmp(long_opt, "") != 0)
    {
        strcpy(action_long_options[action_num][option_num++], long_opt); //长选项
        action_option_num[action_num][1]++;
    }

    action_num++;

    return true;
}

bool cmdl::parse(const int argc, char *argv[])
{ /*若无短选项，则对应参数填‘ ’;若无长选项，则对应参数填“”*/
    if (argc <= 1)
    {
        printf("请输入动作和选项！\n");
        return false;
    }

    printf("命令行解析：\n");

    int action_exist = 0; //判断动作是否存在
    int option_exist = 0; //判断选项是否存在
    int param_num = 0;    //参数数量
    int flag = 0;
    for (int i = 2; i < argc && argc > 2; i++)
    {
        if ('-' != argv[i][0]) //认为除了动作以外，其他不以’-‘开头的都是参数
            flag = 1;
        if (flag == 1)
            param_num++;
    }
    action_param_num = param_num;

    //判断输入指令是否合法
    int i;
    for (i = 0; i < action_num; i++)
        //判断指令中的动作是否存在
        if (strcmp(argv[1], action_name[i]) == 0)
        {
            action_now = argv[1];                    //记录当前动作
            strcpy(action_help_now, action_help[i]); //记录当前动作的说明

            //解析指令中的短选项、长选项、参数
            for (int l = 2; l < argc && argc > 2; l++) //l为命令行输入字符串组的下标指针
            {
                //判断是否为长/短选项
                for (int j = 0; j < action_option_num[i][0] + action_option_num[i][1]; j++)
                {
                    if ('-' == argv[l][0] && '-' != argv[l][1]) //用‘-’数量判断是长/短选项
                    {
                        if (argv[l][1] == action_short_options[i][j])
                        {
                            short_option_now = argv[l][1]; //记录当前短选项
                            option_exist = 1;
                        }
                    }
                    if ('-' == argv[l][0] && '-' == argv[l][1]) //用‘-’数量判断是长/短选项
                    {
                        if (strcmp(argv[l] + 2, action_long_options[i][j]) == 0)
                        {
                            strcpy(long_option_now, argv[l] + 2); //记录当前长选项
                            option_exist = 1;
                        }
                    }
                }
                //判断是否为参数
                if ('-' != argv[l][0] && '-' != argv[l][1]) //用‘-’数量判断是长/短选项
                {
                    static int count = 0;                       //只初始化一次
                    strcpy(action_param_now[count++], argv[l]); //记录当前所有参数
                }
            }
            action_exist = 1;
            break;
        }
    if (action_option_num[i][0] == 0 && action_option_num[i][1] == 0) //action没有选项的情况
        option_exist = 1;

    //打印解析后的命令行信息
    if (action_exist == 0)
        printf("动作 %s 不存在，请重新输入！\n", argv[1]);
    else if (option_exist == 0 && argc > 2)
        printf("动作 %s 存在，但是选项不存在，请重新输入！\n", argv[1]);
    else
    {
        printf("%c", long_option_now[0]);
        if (short_option_now != 0 && long_option_now[0] != 0)
            printf("action: %s\nhelp: %s\nshort option: %c\nlong option: %s\n", action_now.c_str(), action_help_now, short_option_now, long_option_now);
        else if (short_option_now != 0 && long_option_now[0] == 0)
            printf("action: %s\nhelp: %s\nshort option: %c\nno long option\n", action_now.c_str(), action_help_now, short_option_now);
        else if (short_option_now == 0 && long_option_now[0] != 0)
            printf("action: %s\nhelp: %s\nno short option\nlong option: %s\n", action_now.c_str(), action_help_now, long_option_now);
        else
            printf("action: %s\nhelp: %s\nno short option\nno long option\n", action_now.c_str(), action_help_now);

        if (param_num > 0)
        {
            printf("%d parameter(s):", param_num);
            for (int k = 0; k < param_num; k++)
                printf("\t%s", action_param_now[k]);
            printf("\n");
        }
        else
            printf("no parameter\n");

        printf("命令行解析结束\n\n\n");

        return true;
    }

    return false;
}