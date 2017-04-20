#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>

#define PATH_MAX 4096

int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDir(const char *file_path)
{
    struct stat s;
    stat(file_path, &s);
    return S_ISDIR(s.st_mode);
}

char * condense_size(long long bytes)
{
    static char size[PATH_MAX];

    if (bytes > 999999999)
        sprintf(size, "%.1fG", (float)bytes/1000000000);
    else if (bytes > 999999)
        sprintf(size, "%.1fM", (float)bytes/1000000);

    else if (bytes > 999)
        sprintf(size, "%.1fK", (float)bytes/1000);
    else
        sprintf(size, "%d", (int)bytes);
    return size;
}

char * ls_info(char *file)
{   
    //Creates the stat structure
    struct stat fileStat;
    stat(file,&fileStat);
    
    //Prints the permissions eg -rw-----
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    
    //Number of links
    int nl = fileStat.st_nlink;
    printf(" %1d",nl);

    //username
    struct passwd *pw;
    pw = getpwuid(fileStat.st_uid);
    printf(" %-1s", pw->pw_name);
    
    //Group
    struct group *grp;
    grp = getgrgid(fileStat.st_gid);
    printf(" %-1s", grp->gr_name);
    
    
    //Prints Size
    printf(" %1s", condense_size( (long long)fileStat.st_size));
    
    //Time
    struct tm *tm;
    char buf[256];
    tm = localtime(&fileStat.st_mtime);
    strftime(buf,sizeof(buf), "%b %d %R",tm);
    printf(" %-1s", buf);

    
    //File Name
    char * pch;
    pch = strrchr(file,'/');
    printf(" %-1s\n",pch+1);
}

void do_ls(char *file)
{
    DIR *dir, *cp_dir;
    struct stat statBuffer;
    struct dirent *ent, *ent2;
    if (isFile(file))
    {
        ls_info(file);
        return;
    }
    dir = opendir(file);
    stat(file, &statBuffer);
    if (dir != NULL)
    {
        cp_dir = opendir(file);
        while ((ent2 = readdir(cp_dir)) != NULL)
        {
            if (strcmp(ent2->d_name, ".") == 0 || strcmp(ent2->d_name, "..") == 0)
                continue;

            char dir_path2[] = "";
            strcat(dir_path2,file);
            strcat(dir_path2, "/");
            strcat(dir_path2, ent2->d_name);
            ls_info(dir_path2);
        }    
    
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;

            char dir_path[] = "";
            strcat(dir_path, file);
            strcat(dir_path, "/");
            strcat(dir_path, ent->d_name);

            if (isDir(dir_path))
            {
                printf("\n%s\n",dir_path);
                printf("total \n"); // not done
                do_ls(dir_path);
            }
        }
        closedir(dir);
        closedir(cp_dir);
    }
    else
    {
        exit(0);
    }

}

int main(int argc, char *argv[])
{
    int i;
    for (i=1; argv[i] != '\0'; i++)
        {
            do_ls(argv[i]);
        }
    return 0;
}

