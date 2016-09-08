#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int child_main()
{
	sleep(5);
	//print the message
	printf("parent set msg as %s\n" , getenv("msg"));

	return 6;
}

int main()
{
	//create a message
	char msg [ ] = "hello child, how are you?";

	//put a message
	char buffer [ 30 ];
	sprintf(buffer, "msg=%s", msg);
	

	int id = fork();

	switch(id)
	{
		/*fork failed*/
		case -1 : exit(-1);

		/*child action*/
		case 0  : exit( child_main() );

		/*parent action*/
		default : putenv(buffer), wait(NULL), puts("child finished\n");
	}
	
	return 0;
	
}


