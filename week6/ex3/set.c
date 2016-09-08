#include <stdio.h>
#include <stdlib.h>

#define OVERWRITE 1

void main(int argv, char* argc[])
{
    if(argc[1] != NULL) {
        int exit_status = setenv("NUMBER", argc[1], OVERWRITE);
//        putenv("NUMBER=5");
        printf("NUMBER = %s \n", argc[1]);
        printf("Exit status: %i", exit_status);
    } else {
        printf("No value given to set");
    }
}