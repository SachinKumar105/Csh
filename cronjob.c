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
#include <errno.h>
int cronjob(int cp,char **cmd_parts)
{   
    // char *t = malloc(sizeof(char) * 100);
    char **t = malloc((sizeof(char) * 1000) * 1000);
    for (int i = 2; i < (cp - 4); i++)
    {
        t[i - 2] = (char *)malloc(100);
        strcpy(t[i - 2], cmd_parts[i]);
    }
    // cronjob(cmd_parts, a);
    // strcpy(t[a - 6], "");
    t[cp - 6] = NULL;
    int end_time = atoi(cmd_parts[cp - 1]);
    int freq = atoi(cmd_parts[cp - 3]);
    int pid = fork();
    if (pid == 0)
    {

        for (int i = 0; i < end_time / freq; i++)
        {
            sleep(freq);
            // printf("once \n");
            int child = fork();
            if (child == 0)
            {
                if (execvp(t[0], t) < 0)
                {
                    fprintf(stderr, "command not found\n");
                }
                exit(1);    
            }
        }
    }
}