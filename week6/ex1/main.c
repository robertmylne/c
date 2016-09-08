#include <sys/types.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <wait.h>

void main(int argv, char* argc[])
{
    pid_t process = fork();

    int wait_for_child = atoi(argc[1]);

    if(wait_for_child) {
        int exit_status;
        if(waitpid(process, &exit_status, 0)) {
            printf("Parent: (%d) \n", getpid());
        }
    } else {
        printf("Parent: (%d) \n", getpid());
    }

    // Child
    if(process == 0)
    {
        printf("Child: (%d) \n", getpid());
        kill(process, SIGKILL);
        printf("child killed \n");
    }
    // Parent - wait for child
    else if(process > 0)
    {
        kill(process, SIGKILL);
        printf("parent killed \n");
    }
}