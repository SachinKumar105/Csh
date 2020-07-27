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
int ls(int n, char **cmd_parts, char buf[])
{
    int f[2], nd = 0, d[n];
    for (int i = 0; i < n; i++)
        d[i] = 0;
    f[0] = 0;
    f[1] = 0;
    for (int i = 1; i < n; i++)
    {
        if (strcmp(cmd_parts[i], "-l") == 0)
            f[0] = 1;
        else if (strcmp(cmd_parts[i], "-a") == 0)
            f[1] = 1;
        else if (strcmp(cmd_parts[i], "-la") == 0)
        {
            f[0] = 1;
            f[1] = 1;
        }
        else if (strcmp(cmd_parts[i], "-al") == 0)
        {
            f[0] = 1;
            f[1] = 1;
        }
        else
        {
            d[i] = 1;
            nd++;
        }
    }
    if (nd == 0)
    {
        struct dirent **nl;
        int l;
        l = scandir(".", &nl, NULL, alphasort);
        while (l--)
        {
            if ((f[1] == 1 || nl[l]->d_name[0] != '.') && f[0] == 0)
            {
                printf("%s\n", nl[l]->d_name);
                free(nl[l]);
            }
            if (f[0] == 1 && (f[1] == 1 || nl[l]->d_name[0] != '.'))
            {
                struct stat fileStat;
                if (stat(nl[l]->d_name, &fileStat) < 0)
                    return 1;
                struct passwd *pw = getpwuid(fileStat.st_uid);
                struct group *gr = getgrgid(fileStat.st_gid);
                printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld", fileStat.st_nlink);
                printf("\t%s\t%s", pw->pw_name, gr->gr_name);
                printf("\t%ld", fileStat.st_size);
                printf("\t%.19s", ctime(&fileStat.st_mtime));
                printf("\t%s\n", nl[l]->d_name);
            }
        }
        free(nl);
        printf("\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (d[i] == 1)
            {
                struct dirent **nl;
                int l;
                // printf("%s-----%d\n",cmd_parts[i],n);
                if (cmd_parts[i][0] != '~')
                    l = scandir(cmd_parts[i], &nl, NULL, alphasort);
                else
                {
                    char lol[200] = "";
                    strcat(lol, buf);
                    strcat(lol, &cmd_parts[1][1]);
                    l = scandir(lol, &nl, NULL, alphasort);
                }
                if (l == -1)
                {
                    perror(cmd_parts[i]);
                    return 1;
                }
                printf("%s:\n", cmd_parts[i]);
                while (l--)
                {
                    if ((f[1] == 1 || nl[l]->d_name[0] != '.') && f[0] == 0)
                        printf("%s\n", nl[l]->d_name);
                    if (f[0] == 1 && (f[1] == 1 || nl[l]->d_name[0] != '.'))
                    {
                        struct stat fileStat;
                        char fn[1000] = "";
                        if (cmd_parts[i][0] != '/' && cmd_parts[i][0] != '~')
                        {
                            if(getcwd(fn, 1000))
                                perror("");
                            strcat(fn, "/");
                            strcat(fn, cmd_parts[i]);
                            strcat(fn, "/");
                            strcat(fn, nl[l]->d_name);
                        }
                        // else if()
                        else if (cmd_parts[i][0] == '/')
                        {
                            strcat(fn, cmd_parts[i]);
                        }
                        if (stat(fn, &fileStat) < 0)
                            return 1;
                        struct passwd *pw = getpwuid(fileStat.st_uid);
                        struct group *gr = getgrgid(fileStat.st_gid);
                        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                        printf(" %ld", fileStat.st_nlink);
                        printf("\t%s\t%s", pw->pw_name, gr->gr_name);
                        printf("\t%ld", fileStat.st_size);
                        printf("\t%.19s", ctime(&fileStat.st_mtime));
                        printf("\t%s\n", nl[l]->d_name);
                    }
                    free(nl[l]);
                }
                free(nl);
                printf("\n");
            }
        }
    }
}