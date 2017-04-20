#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int sigI, sigQ, sigST = 0; 

void sig_handler(int signum)
{
    switch(signum)
    {
        case SIGINT:
            printf("I");
            fflush(stdout);
            sigI++;
            break;
        case SIGQUIT:
            printf("Q");
            fflush(stdout);
            sigQ++;
            break;
        case SIGTSTP:
            printf("S");
            fflush(stdout);
            sigST++;
            if (sigST >= 3)
            {
                printf("\nInterrupt: %d\nStop: %d\nQuit: %d\n",sigI,sigST,sigQ);
                fflush(stdout);
                exit(0);
            }
            break;
        default:
            break;
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    
    while(1)
    {
        sleep(1);
    }

    return 0;

}
