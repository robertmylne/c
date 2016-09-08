#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    // "date > file.txt" THEN "cat file.txt" THEN ls
    int exit_status = WEXITSTATUS(system(argv[1]));
    printf("Exit status: %i \n", exit_status);
}