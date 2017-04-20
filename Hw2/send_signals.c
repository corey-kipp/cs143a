#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int sigCount = 0;

void send_signal_handler(int signum)
{
    switch(signum)
    {
        case SIGINT:
            printf("Signals: %d\n",sigCount);
            exit(0); 
            break;
        case SIGUSR1:
            kill(getppid(), SIGUSR2);
            sigCount++;
            break;
        default:
            break;
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = send_signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    while(1)
    {
        sleep(1);
    }
    return 0;
}
