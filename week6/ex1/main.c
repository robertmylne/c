#include <sys/types.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>

void main(int argv, char* argc[])
{
    system("ps");
    pid_t process = fork();

    // Child
    if(process == 0)
    {
        printf("Child cloned: (%d) \n", getpid());
        kill(process, SIGKILL);
    }
    // Parent
    else if(process > 0)
    {
        printf("Hello daddy: (%d) \n", getpid());
        kill(process, SIGKILL);
    }

    system("ps");
    sleep(10);
}