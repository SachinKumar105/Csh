#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/utsname.h>
#include <signal.h>
#include<errno.h>
int parse_line(char *cmdl, char **cmds)
{
    char *token;
    int n = 0;
    while ((token = strtok_r(cmdl, ";", &cmdl)))
    {
        cmds[n] = token;
        n++;
    }
    return n;
}
int parse(char *cmcp, char **cmd_parts)
{
    char *token;
    int n = 0;
    while ((token = strtok_r(cmcp, " ", &cmcp)))
    {
        cmd_parts[n] = token;
        // printf("%s--",token);
        n++;
    }
    // printf("\n");
    return n;
}
int outredr(char *cmcp, char **cmd_parts)
{   char *token;
    int n = 0;
     while ((token = strtok_r(cmcp, ">", &cmcp)))
    {
        cmd_parts[n] = token;
        // printf("%s--",token);
        n++;
    }
    // printf("\n");
    return n;
}
int inredr(char *cmcp, char **cmd_parts)
{   char *token;
    int n = 0;
     while ((token = strtok_r(cmcp, "<", &cmcp)))
    {
        cmd_parts[n] = token;
        // printf("%s--",token);
        n++;
    }
    // printf("\n");
    return n;
}
int pipar(char *cmcp, char **cmd_parts)
{   char *token;
    int n = 0;
    while ((token = strtok_r(cmcp, "|", &cmcp)))
    {
        cmd_parts[n] = token;
        // printf("%s--",token);
        n++;
    }
    // printf("\n");
    return n;
}