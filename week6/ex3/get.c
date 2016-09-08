#include <stdio.h>
#include <stdlib.h>

void main(int argv, char* argc[])
{
    printf("NUMBER: %s \n", getenv("NUMBER"));
}