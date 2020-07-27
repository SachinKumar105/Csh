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
void execute(int cp, char **cmd_parts, int l, int pi[], int pp[], char buf[])
{
    if (strcmp(cmd_parts[0], "pwd") == 0)
        pwd();
    else if (strcmp(cmd_parts[0], "echo") == 0)
        echo(cp, cmd_parts);
    else if (strcmp(cmd_parts[0], "cd") == 0)
        cd(cp, cmd_parts, buf);
    else if (strcmp(cmd_parts[0], "ls") == 0)
        ls(cp, cmd_parts, buf);
    else if (strcmp(cmd_parts[0], "pinfo") == 0)
        pinfo(cp, cmd_parts);
    else if (strcmp(cmd_parts[0], "history") == 0)
        history(cp, cmd_parts);
    else
        syscmd(cp, cmd_parts, l, pi, pp);
}