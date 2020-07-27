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
void history(int n, char **cmd_parts)
{
    int k;
    if (n == 1)
        k = 10;
    else
        k = atoi(cmd_parts[1]);
    if (k > 20)
        k = 20;
    char *p = getenv("USER"), *host = getenv("HOSTNAME");
    HISTORY_STATE *myhist = history_get_history_state();
    HIST_ENTRY **mylist = history_list();
    for (int i = myhist->length - 1; i >= 0 && i >= myhist->length - k; i--)
    {
        printf(" %8s  %s\n", mylist[i]->line, mylist[i]->timestamp);
    }
    putchar('\n');
}