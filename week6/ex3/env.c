#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OVERWRITE 1

void set_env(char* env)
{
    setenv("NUMBER", env, OVERWRITE);
}

void get_env()
{
    pid_t process = fork();

    if(process == 0) {
        printf("NUMBER = %s \n", getenv("NUMBER"));
    }
}

void main(int argv, char* argc[])
{
    if(argc[1] != NULL) {
        set_env(argc[1]);
        get_env();
    } else {
        printf("No value given to set");
    }
}