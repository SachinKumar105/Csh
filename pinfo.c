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
void pinfo(int n, char **cmd_parts,int parpid)
{
    int g, line_count = 0;
    char *f, h[10], ad[100] = "", aa[100], ff[100], *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    if (n == 1)
    {
        g = parpid;
        sprintf(h, "%d", g);
        f = h;
    }
    else if (n == 2)
        f = cmd_parts[1];
    strcat(ad, "/proc/");
    strcat(ad, f);
    strcpy(aa, ad);
    strcat(ad, "/status");
    FILE *fp = fopen(ad, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }
    printf("pid -- %s\n", f);
    int i = 0;
    while (fgets(ff, sizeof(ff), fp))
    {
        if (i == 2)
        {
            int nn = 0;
            char *ab, *token;
            ab = ff;
            char *ac[5];
            while ((token = strtok_r(ab, "\t", &ab)))
            {
                ac[nn] = token;
                nn++;
            }
            printf("Process Status -- %s", ac[1]);
        }
        if (i == 17)
        {
            int nn = 0;
            char *ab, *token;
            ab = ff;
            char *ac[5];
            while ((token = strtok_r(ab, "\t", &ab)))
            {
                ac[nn] = token;
                nn++;
            }
            printf("memory -- %s", ac[1]);
        }
        i++;
    }
    fclose(fp);
    strcat(aa, "/exe");

    char buf[1024];
    ssize_t len;
    if ((len = readlink(aa, buf, sizeof(buf) - 1)) != -1)
        buf[len] = '\0';
    printf("Executable path -- %s\n", buf);
}