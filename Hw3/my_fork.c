#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_n_characters(int n, char c)
{
    for (int i = 0; i<n; i++)
    {
        printf("%c", c);
        fflush(stdout);
    }
}

int main(int argc, char* argv[])
{
    int loop_count;
    if (argc > 1)
    {
        loop_count = atoi(argv[1]);
    }
    else
    {
        loop_count = 10;
    }
    char c;
    for (c='A'; c <= 'D'; c++)
    {
        int pid;
        pid = fork();
        if (pid < 0)
        {
            exit(1);
        }
        else if (pid == 0)
        {
            print_n_characters(loop_count,c);
            exit(0);
        }
    }
    for (int i =0; i<4; i++)
    {
        wait(NULL);
    }
    return 0;
}
