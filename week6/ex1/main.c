#include <sys/types.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <wait.h>

void main(int argv, char *argc[])
{
    // Protect against zombie processes
    signal(SIGCHLD, SIG_IGN);

    pid_t process = fork();

    int wait_for_child = atoi(argc[1]);

    // Child
    if (process == 0)
    {
        printf("Child: (%d) \n", getpid());
        exit(0);
    }
    // Parent
    else if (process > 0)
    {
        // Don't wait for child
        if (wait_for_child)
        {
            if (wait(NULL)) {
                printf("Waited Parent: (%d) \n", getpid());
                kill(process, SIGKILL);
                printf("Killed: (%d) \n", getpid());
            }
        }
        // Wait for child to be killed
        else
        {
            printf("Parent: (%d) \n", getpid());
            kill(process, SIGKILL);
            printf("Killed: (%d) \n", getpid());
        }
    }
}