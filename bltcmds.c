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
void pwd() 
{
    char p[1000];
    getcwd(p, 1000);
    printf("%s\n", p);
}
void echo(int n, char **cmd_parts)
{
    for (int i = 1; i < n; i++)
    {   if(cmd_parts[i][0]!='$')
            printf("%s ", cmd_parts[i]);
        else
        {   char *evar;
            evar = getenv(cmd_parts[i]+1);
            printf("%s ",evar);
        }
        
    }
    printf("\n");
}
void cd(int n, char **cmd_parts, char buf[])
{   int er=0;
    if (n == 1)
        chdir(buf);
    if (n > 2)
        printf("cd: string not in pwd: %s", cmd_parts[1]);
    else if (n == 2)
        if (cmd_parts[1][0] == '~')
        {
            char lol[200] = "";
            strcat(lol, buf);
            strcat(lol, &cmd_parts[1][1]);
            er = chdir(lol);
            if(er)
            perror("");
        }
        else
            if(chdir(cmd_parts[1]))
                perror(cmd_parts[1]);
}