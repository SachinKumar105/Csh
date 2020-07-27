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
#include "header.h"
int jobs(char **nm,int qq[],int bgp)
{  // printf("woooooooooooow\n");
    
    // for(int i=0;i<bgp;i++)
    // {  // qq[i]=-100;
    //     // printf("made qq[%d] = -100  %d\n",i,qq[i]); 
    // }
    int k=0;
    for(int i=0;i<bgp;i++)
    {   if(qq[i]!=-100)
        {
            int g, line_count = 0;
            char *f, h[10], ad[100] = "", aa[100], ff[100],ff1[100], *line_buf = NULL;
            f = malloc(sizeof(char)*100);
            size_t line_buf_size = 0;
            ssize_t line_size;
            // printf("woooooooooooow\n");
            sprintf(f,"%d",qq[i]);
            // printf("woooooooooooow\n");
            strcat(ad, "/proc/");
            strcat(ad, f);
            strcpy(aa, ad);
            strcat(ad, "/status");
            strcpy(aa, "/comm");
            // printf("---%s---\n",ad);
            FILE *fp = fopen(ad, "r");
            FILE *fp1 = fopen(ad, "r");
            if (fp == NULL)
            {
                perror("Error opening file");
                printf("%s",ad);
                return;
            }
            // printf("pid -- %s\n", f);
            char pf[100],ff2[100];
            strcpy(pf,f);
            // strcpy(ff2,nm[i]);
            int j =i;
            int i = 0;
            fgets(ff1, sizeof(ff1),fp1);
            // printf("%s",ff1);
            while (fgets(ff, sizeof(ff), fp))
            {
                if (i == 2)
                {
                    int nn = 0;
                    char *ab, *token;
                    ab = ff;
                    char *ac[5];
                    while ((token = strtok_r(ab, "(", &ab)))
                    {
                        ac[nn] = token;
                        nn++;
                    }
                    int len1 = strlen(ac[1]);
                    ac[1][len1-2]='\0';
                    int len2 = strlen(ff1);
                    ff1[len2-1]='\0';
                    // printf("%d  ",len2);
                    printf("[%d] %s %s [%s]\n", j+1,ac[1],ff1+6,pf);
                }
                i++;
            }
            k++;
        }
    }
    return 0;
}
int kjob(int qq[],int bgp,char **cmd_parts)
{   //int k=1,i;
    // printf("kjob\n");
    int jid = atoi(cmd_parts[1]);
    int sgnl = atoi(cmd_parts[2]);
    // for(i=0;i<bgp && k!= jid;i++)
    // {   if(qq[i]!=-100)
            // k++;
    // }
    // printf("%d",qq[jid-1]);
    kill(qq[jid-1],sgnl);
}
int bg(int qq[],int bgp,char **cmd_parts)
{   int jid = atoi(cmd_parts[1]);
    kill(qq[jid-1],18);
}
int overkill(int qq[],int bgp,char **cmd_parts)
{   for(int i=0;i<bgp;i++)
    {   
        if(qq[i]!=-100 && qq[i]!=0 )
        {   //printf("id=%d\n",qq[i]);
            // fflush(stdout);
            kill(qq[i],SIGKILL);
            qq[i]=-100;

        }
    }
    // for(int i=0;i<bgp;i++)
    // {   qq[i]=-100;
    //     // printf("made qq[%d] = -100  %d\n",i,qq[i]); 
    // }
}
int fg(int qq[],int bgp,char **cmd_parts,int parpid)
{   printf("in fg\n");
    // int jid = atoi(cmd_parts[1]);
    // int pid = qq[jid-1];
    // printf("jid=%d pid=%d\n",jid,pid);
    // signal(SIGTTOU, SIG_IGN);
    // tcsetpgrp(0, getpgid(pid));
    // signal(SIGTTOU, SIG_DFL);
    // waitpid(pid, NULL, WUNTRACED);
    // signal(SIGTTOU, SIG_IGN);
    // tcsetpgrp(0, getpgid(parpid));
    // signal(SIGTTOU, SIG_DFL);
    int jid = atoi(cmd_parts[1]);
    // printf("in fg killed1\n");
    kill(qq[jid-1],18);
    // printf("in fg killed\n");
    fore = qq[jid-1];

    int sin = dup(0);
    int g, line_count = 0;
    char f[100], h[10], ad[100] = "", aa[100], ff[100], *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    // printf("hello %d\n",qq[jid-1]);
    sprintf(f,"%d",qq[jid-1]);
    // printf("hello hai\n");
    strcat(ad, "/proc/");
    strcat(ad, f);
    strcpy(aa, ad);
    strcat(ad, "/fd/0");
    strcat(aa,"/stat");
    printf("%s\n",aa);
    FILE *fp = fopen(aa, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        printf("%s",aa);
        return;
    }
    
    dup2(fp,0);
    while(1)
    {   
        int fp1 = open(aa,O_APPEND);
        // printf("fp1 = %d\n",fp1);
        fgets(ff, sizeof(ff), fp);
        char **aaa = malloc((sizeof(char) * 1000) * 1000);
        int a = parse(ff,aaa);
        // printf("aaa = %s\n",aaa[2]);
        if(strcmp(aaa[2],"Z")==0 || fp1==-1)
        {   qq[jid-1]=-100;   
            break;
        }
        else if(strcmp(aaa[2],"T")==0)
        {   qq[jid-1]=-100;
            break;
        }
        close(fp1);
        free(aaa);
    }
    dup2(sin,0);
    close(sin);
    close(fp);
    return; 
        // int i=0;
        // while (fgets(ff, sizeof(ff), fp))
        // {
        //     if (i == 2)
        //     {
        //         int nn = 0;
        //         char *ab, *token;
        //         ab = ff;
        //         char *ac[5];
        //         while ((token = strtok_r(ab, " ", &ab)))
        //         {
        //             ac[nn] = token;
        //             nn++;
        //         }
        //         int len1 = strlen(ac[1]);
        //         ac[1][len1-2]='\0';
        //         // int len2 = strlen(ff1);
        //         // ff1[len2-1]='\0';
        //         // printf("%d  ",len2);
        //         printf("%s [%s]\n",ac[1],f);
        //     }
        //     i++;
        // }

    // }

}