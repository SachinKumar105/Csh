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
int setenvvar(int cp, char **cmd_parts)
{   if(cp==3)
        setenv(cmd_parts[1],cmd_parts[2],1);
    else if (cp==2)
        setenv(cmd_parts[1],"",1);
    else
        printf("Not enough arguements or more than enough args  %d\n",cp);
}
int unsetenvvar(int cp, char **cmd_parts)
{   if(cp==2){
        if(unsetenv(cmd_parts[1])!=0)
            printf("Variable not undeclared\n");
    }
    else
        printf("Not enough arguements or more than enough args  %d\n",cp);
}