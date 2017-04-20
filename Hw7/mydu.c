#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

char dircall[100];

int isFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDir(char *file_path)
{
    struct stat s;
    stat(file_path, &s);
    return S_ISDIR(s.st_mode);
}

long long printDiskUsageDir(char *path)
{
    struct stat statBuffer;
    stat(path, &statBuffer);
    return ((long long)statBuffer.st_blocks)/2;
}

long long walkDir(char *basedir)
{
    long long count = 0;
    DIR *dir;
    char b[512];
    struct stat statBuffer;
    struct dirent *ent;
    if (isFile(basedir))
    {
        count += printDiskUsageDir(basedir);
        return count;
    }
    dir = opendir(basedir);
    stat(basedir, &statBuffer);
    if (dir != NULL)
    {
        if (strcmp(basedir, dircall) == 0)
            count += printDiskUsageDir(basedir);
        while ( (ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;

            char entpath[] = "";
            strcat(entpath, basedir);
            strcat(entpath, "/");
            strcat(entpath, ent->d_name);

            if (isDir(entpath))
            {
                long long inner = 0;
                long long temp1 = printDiskUsageDir(entpath);
                long long temp2 = walkDir(entpath);
                count += temp1;
                count += temp2;
                inner += temp1;
                inner += temp2;
                printf("%lld\t%s\n", inner, entpath);
            }
            else
            {
                count += printDiskUsageDir(entpath);
            }
        }
        if (isDir(basedir) && strcmp(basedir, dircall) == 0)            
            printf("%lld\t%s\n", count, basedir);
        return count;
        closedir(dir);
    }
    else
    {
        exit(0);
    }

}

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; argv[i] != '\0'; i++)
    {
        strcpy(dircall,argv[i]);
        walkDir(argv[i]);
    }
    return 0;
}
