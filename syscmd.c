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
int bl, mm = 0, qq[100], bgp = 0;
char nm[100][100];
void signalHandler(int signal)
{
    // printf("Im dead  %d -- %d---\n", signal, SIGCHLD);
    int q, z, i;
    if (signal == SIGCHLD)
    {
        // printf("\n");
        int id = waitpid(-1, &q, WNOHANG);
        for (i = 0; i < 100; i++)
        {
            // printf("Im dead  %d -- %d---%d+++%d---%d\n", signal, SIGCHLD,id,i,qq[i]);

            if (qq[i] == id && id != 0)
            {
                // printf(" killed  %d\n", qq[i]);
                qq[i] = -100;
                fprintf(stderr, "%s with pid %d exited ", nm[i], id);
                if (q == 0)
                    fprintf(stderr, "normally\n");
                else
                    fprintf(stderr, "abnormally\n");
                fflush(stdout);
                break;
            }
        }
    }
}

int sgtstp(signal)
{   //printf("in sgtstp\n");
    if (signal == SIGTSTP)
    {//   printf("in sgtstp 1\n");
        if (fore > 0)
        { //  printf("in sgtstp,fore>0\n");
            kill(fore, 19);
            // printf("after kill\n");
            qq[bgp++]=fore;
            // printf("after kill 1\n");
        }
    }
}
void execute(int cp, char **cmd_parts, int l, int pi[], int pp[], char buf[], int parr[], int g)
{
    int n = cp;
    bl = 0;
    int lol;
    for (int i = 1; i < n; i++)
    {
        if (strcmp(cmd_parts[i], "&") == 0)
        {
            bl = 1;
        }
    }
    // strcpy(nm[mm++], cmd_parts[0]);
    if (bl == 1)
        signal(SIGCHLD, signalHandler);
    char **a;
    a = cmd_parts;
    // a[n] = NULL;
    a[n - bl] = NULL;
    // char *ba[] = {cmd_parts[0], NULL};
    // if (strcmp(cmd_parts[0], "pinfo") == 0)
    // {
    //     dup2(parr[1], 1);
    //     pinfo(cp, cmd_parts);
    //     // close(parr[1]);
    //     // return;
    // }
    if (strcmp(cmd_parts[0], "cd") == 0)
        cd(cp, cmd_parts, buf);
    else if (strcmp(cmd_parts[0], "overkill") == 0)
    { //printf("bla bla bla\n");
        overkill(qq, bgp, cmd_parts);
    }
    else if (strcmp(cmd_parts[0], "cronjob") == 0)
    { //printf("bla bla bla\n");
        cronjob(cp,cmd_parts);
    }
    else if (strcmp(cmd_parts[0], "setenv") == 0)
    { //printf("bla bla bla\n");
        setenvvar(cp, cmd_parts);
    }
    else if (strcmp(cmd_parts[0], "unsetenv") == 0)
    { //printf("bla bla bla\n");
        unsetenvvar(cp, cmd_parts);
    }
    else if (strcmp(cmd_parts[0], "quit") == 0)
    { //printf("bla bla bla\n");
        exit(0);
    }
    else if (strcmp(cmd_parts[0], "vim") == 0)
    { 
        int pid = fork();
        if(pid==0)
        {   execvp(a[0],a);
        }
        if(pid>0)
        { if (bl != 1)
            {   int foo = getpid();
                setpgid(foo, foo);
                int t;
                waitpid(pid, &t, WUNTRACED);
            }
            else
            {
                setpgid(pid, pid);
                strcpy(nm[bgp], cmd_parts[0]);
                qq[bgp] = pid;
                bgp++;
                return;
            }  

        }
    }
    else
    {
        int pid = fork();
        if (pid == 0)
        {
            int q;
            dup2(parr[1], 1);
            int foo = getpid();
            setpgid(foo, foo);
            // printf("sfdfbsdfbf\n");
            if (strcmp(cmd_parts[0], "pwd") == 0)
                pwd();
            else if (strcmp(cmd_parts[0], "echo") == 0)
                echo(cp, cmd_parts);
            // else if (strcmp(cmd_parts[0], "cd") == 0)
            //     cd(cp, cmd_parts, buf);
            else if (strcmp(cmd_parts[0], "pinfo") == 0)
            {
                dup2(parr[1], 1);
                // printf("pinfo\n");
                pinfo(cp, cmd_parts, g);
                // close(parr[1]);
                // return;
            }
            else if (strcmp(cmd_parts[0], "jobs") == 0)
            { //printf("bla bla bla\n");
                jobs(nm, qq, bgp);
            }
            else if (strcmp(cmd_parts[0], "kjob") == 0)
            { //printf("bla bla bla\n");
                kjob(qq, bgp, cmd_parts);
            }
            else if (strcmp(cmd_parts[0], "bg") == 0)
            { //printf("bla bla bla\n");
                bg(qq, bgp, cmd_parts);
            }
            else if (strcmp(cmd_parts[0], "fg") == 0)
            { //printf("bla bla bla\n");
                fg(qq, bgp, cmd_parts, g);
            }
            else if (strcmp(cmd_parts[0], "overkill") == 0)
            { //printf("bla bla bla\n");
                overkill(qq, bgp, cmd_parts);
            }
            else if (strcmp(cmd_parts[0], "ls") == 0)
                ls(cp, cmd_parts, buf);
            // else if (strcmp(cmd_parts[0], "pinfo") == 0)
            //     pinfo(cp, cmd_parts);
            else if (strcmp(cmd_parts[0], "history") == 0)
                history(cp, cmd_parts);
            else
            {   //printf("a[0]==%s\n",a[0]);
                // syscmd(cp, cmd_parts, l, pi, pp);
                // if (bl == 1 && n == 2)
                // {
                //     q = execvp(a[0], a);
                // }
                // else
                    q = execvp(a[0], a);
            }
            // close(parr[1]);
            exit(0);
        }
        if (pid > 0)
        {
            // qq[mm - 1] = pid;
            // bgp++;
            if (bl != 1)
            {
                fore = pid;
                // setpgid(pid, pid);
                // while (wait(&bl) != pid)
                // {
                //     ;
                // }
                int t;
                waitpid(pid, &t, WUNTRACED);
            }
            else
            {
                setpgid(pid, pid);
                strcpy(nm[bgp], cmd_parts[0]);
                qq[bgp] = pid;
                bgp++;
                // signal(SIGCHLD, signalHandler);

                return;
            }
        }
    }
}