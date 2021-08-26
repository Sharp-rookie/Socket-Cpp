#include "cmdline.h"
#include "diff.h"
#include "diff_LCS.h"
#include "add.h"
#include "commit.h"
#include "rm.h"
#include "mv.h"
#include "init.h"
#include "reset.h"
#include "status.h"

int main(int argc, char *argv[])
{
    cmdl cmd;
    cmd.add_action("diff", ' ', "", 2, "Show changes between work dir and stage");
    cmd.add_action("add", ' ', "", 2, "submit the files from work dir to stage dir");
    cmd.add_action("commit", 'm', "message", 1, "commit the files from stage dir to local dir with the parameter as message");
    cmd.add_action("rm", ' ', "", 1, "remove the file in the work_dir and stage");
    cmd.add_action("mv", ' ', "", 2, "move or rename a file");
    cmd.add_action("init", ' ', "", 0, "initial a local repository");
    cmd.add_action("_reset", 'c', "cathe", 0, "");
    cmd.add_action("_reset", 'w', "workdir", 0, "");
    cmd.add_action("status", ' ', "", 0, "");
    cmd.parse(argc, argv);

    if (strcmp(cmd.action_now.c_str(), "diff") == 0)
        diff_LCS();
    //diff();

    if (strcmp(cmd.action_now.c_str(), "add") == 0)
        add(cmd.short_option_now);

    if (strcmp(cmd.action_now.c_str(), "commit") == 0)
        commit(cmd.short_option_now, cmd.long_option_now, cmd.action_param_num, cmd.action_param_now);

    if (strcmp(cmd.action_now.c_str(), "rm") == 0)
        rm(cmd.action_param_num, cmd.action_param_now);

    if (strcmp(cmd.action_now.c_str(), "mv") == 0)
        mv(cmd.action_param_num, cmd.action_param_now);

    if (strcmp(cmd.action_now.c_str(), "init") == 0)
        init(cmd.action_param_num, cmd.action_param_now);

    if (strcmp(cmd.action_now.c_str(), "_reset") == 0)
        reset(cmd.long_option_now);

    if (strcmp(cmd.action_now.c_str(), "status") == 0)
        status();
}

bool file_copy(const char *old_file, const char *new_file) //文件copy函数的定义
{
    char buf[300];
    memset(buf, 0, sizeof(buf));

    FILE *W, *S;

    if ((W = fopen(old_file, "r")) == 0 || (S = fopen(new_file, "w")) == 0)
        return false;

    while (fgets(buf, 300, W))
        fprintf(S, "%s", buf);

    fclose(W);
    fclose(S);

    return true;
}