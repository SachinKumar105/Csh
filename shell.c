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
#include "header.h"
int sgint(signal)
{
    if (signal == SIGINT)
    {
        kill(fore, SIGINT);
    }
}
int sgtstp(signal);
int main(void)
{
    int sout = dup(1);
    int sin = dup(0);
    int cn;
    signal(SIGINT, sgint);
    signal(SIGTSTP, sgtstp);
    int pi[100], pp[100];
    char c[100], d[100], e[100];
    char t[100] = "", *f, p[10] = "";
    strcat(t, "/proc/");
    int g = getpid();
    sprintf(p, "%d", g);
    strcat(t, p);
    strcat(t, "/exe");
    char buf[1024];
    ssize_t len;
    if ((len = readlink(t, buf, sizeof(buf) - 1)) != -1)
        buf[len] = '\0';
    int l = len;
    while (buf[l] != '/')
    {
        l--;
    }
    buf[l] = '\0';
    using_history();
    l = 0;
    while (1)
    {
        display(d, buf);
        char *cmdl = malloc(sizeof(char) * 1000);
        char **cmds = malloc((sizeof(char) * 1000) * 1000);
        cmdl = readline(d);
        if (strlen(cmdl) != 0)
            add_history(cmdl);
        cn = parse_line(cmdl, cmds);
        for (int i = 0; i < cn; i++)
        {
            int fl = -1, flin = -1;
            char *cmcp = strdup(cmds[i]);
            // char **cmd_parts = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partsin = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partsinf = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partsp = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partspf = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partso = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partsof = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partsi = malloc((sizeof(char) * 1000) * 1000);
            char **cmd_partsif = malloc((sizeof(char) * 1000) * 1000);
            int flag=0;
            if(strstr(cmcp,">>")!=NULL)
                flag=1;
            int optr = outredr(cmcp, cmd_partso);
            // printf("optr = %d\n",optr);
            int ptr = pipar(cmd_partso[0], cmd_partsp);
            int inptr = inredr(cmd_partsp[0], cmd_partsin);
            // printf("xxxxxxxxxxxx %d xxxxxxxxxxxxxxxxx\n",ptr);
            if (inptr == 2)
            { //int fl = 100;
                int inrdf = parse(cmd_partsin[1], cmd_partsinf);
                char inradd[1024];
                getcwd(inradd, 1024);
                strcat(inradd, "/");
                strcat(inradd, cmd_partsinf[0]);
                flin = open(inradd, O_RDONLY, 0644);
                // if(flin==-1)
                //     fprintf(stderr,"file doesn't exist\n");
                perror(inradd);
                // printf("printed in given file  %s -------   %d \n",outradd,fl);
                dup2(flin, 0);
                // printf("printed in given file  -------  %d \n",fl);
            }
            if (optr == 2)
            { //int fl = 100;
                int outrdf = parse(cmd_partso[1], cmd_partsof);
                char outradd[1024];
                getcwd(outradd, 1024);
                strcat(outradd, "/");
                strcat(outradd, cmd_partsof[0]);
                if(flag!=1)
                    fl = open(outradd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                else
                    fl = open(outradd, O_WRONLY | O_APPEND | O_CREAT, 0644);
                // printf("printed in given file  %s ------- %d---  %d \n",outradd,optr,fl);
                // dup2(fl,1);
                // printf("printed in given file  -------  %d \n",fl);
            }
            for (int i = 0; i < ptr; i++)
            {
                int parr[2];
                char **cmd_parts = malloc((sizeof(char) * 1000) * 1000);
                // printf("--%d  ----   %d ----  %s--  \n",ptr,i,cmd_partsp[i]);
                int cp = parse(cmd_partsp[i], cmd_parts);
                if (i != ptr - 1)
                    pipe(parr);
                else
                {
                    parr[1] = fl;
                    // dup2(sout,1);
                }
                execute(cp, cmd_parts, l, pi, pp, buf, parr, g);
                close(parr[1]);
                // char *ghgg=(char *)malloc(100);
                // read(parr[0],ghgg,100);
                // printf("--%d  ----   %d ----  %s--%s    \n",ptr,i,cmd_parts[0],cmd_parts[1]);
                dup2(parr[0], 0);
            }
            // if (strcmp(cmd_parts[0], "pwd") == 0)
            //     pwd();
            // else if (strcmp(cmd_parts[0], "echo") == 0)
            //     echo(cp, cmd_parts);
            // else if (strcmp(cmd_parts[0], "cd") == 0)
            //     cd(cp, cmd_parts, buf);
            // else if (strcmp(cmd_parts[0], "ls") == 0)
            //     ls(cp, cmd_parts, buf);
            // else if (strcmp(cmd_parts[0], "pinfo") == 0)
            //     pinfo(cp, cmd_parts);
            // else if (strcmp(cmd_parts[0], "history") == 0)
            //     history(cp, cmd_parts);
            // else
            //     syscmd(cp, cmd_parts, l, pi, pp);
            // execute(cp, cmd_parts, l, pi, pp, buf,parr);
            dup2(sin, 0);
            dup2(sout, 1);
            free(cmdl);
        }
    }
}