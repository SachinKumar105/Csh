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
void display(char d[], char buf[])
{
    struct utsname utsbuf;
    if (uname(&utsbuf) != -1)
    {
        memset(d, 0, strlen(d));
        strcat(d, "< ");
        strcat(d, getenv("USER"));
        strcat(d, "@");
        strcat(d, utsbuf.nodename);
        strcat(d, ":");
    }
    char a[200], b[200] = "";
    getcwd(a, 200);
    int in = strlen(buf), fn = strlen(a);
    if (fn >= in)
    {
        if (strstr(a, buf) != NULL)
        {
            strcat(b, "~");
            strcat(b, &a[in]);
        }
        else
            strcat(b, a);
    }
    else
        strcat(b, a);
    strcat(d, b);
    strcat(d, " > ");
}