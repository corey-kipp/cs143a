#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *remove_nl(char *s) 
{
  int i = strlen(s)-1;
  if ((i > 0) && (s[i] == '\n'))
    s[i] = '\0';
  return s;
}

void parse_input(char* pInput)
{   
    char * arguments[1024];
    char *pch;
    int i = 0;
    int pid;

    pch = strtok(pInput, " ");
    while (pch != NULL)
    {
        arguments[i] = pch;
        i++;
        pch = strtok(NULL, " ");
    }
    arguments[i] = NULL;

    pid = fork();
    if (pid == 0)
    {
        if (arguments[0] == '\0' || strlen(*arguments) == 1)
        {
            exit(0);
        }
        execvp(arguments[0],arguments);
        perror("ERROR: exec failed");
        exit(1);         
    }
    else if (pid < 0)
    {
        perror("ERROR: fork failed");
        exit(2);
    }
    wait(NULL);
}


int main(int argc, char* argv[])
{
    char pInput[1024];
    while(1)
    {
        printf("$");
        fflush(stdout);
        if (fgets(pInput, sizeof(pInput), stdin) != NULL)
        {
            parse_input(remove_nl(pInput));
        }
        else
            break;
    }
    return 0;
}

