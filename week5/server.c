#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <memory.h>

#define SERVER_PORT 1067
#define MAX_LENGTH 80

void main()
{
    int sock, connection, client_length;
    struct sockaddr_in server, client;

    // Protect against zombie processes
    signal(SIGCHLD, SIG_IGN);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("creating steam socket");
        exit(1);
    }

    // Create server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVER_PORT);

    // Bind port
    if(bind(sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("binding socket");
        exit(2);
    }

    // Listen
    listen(sock, 5);
    printf("Listening on port %i\n", SERVER_PORT);

    while(1)
    {
        // Messages
        char input[MAX_LENGTH], output[MAX_LENGTH];

        // Accept
        client_length = sizeof(client);
        connection = accept(sock, (struct sockaddr*) &client, &client_length);
        if(connection < 0) {
            perror("accepting connection");
            exit(3);
        }

        // Connection
        if(fork() == 0) {
            close(sock);
            printf("Client connected: (pid %d) | Using descriptor: %d \n", getpid(), sock);

            // While requests coming in
            while(read(connection, input, MAX_LENGTH))
            {
                sprintf(output, "Server: %s", input);
                write(connection, output, strlen(output));
            }

            printf("Client exited: (pid %d) \n", getpid());
            exit(0);
        }

        // Close connection
        close(connection);
    }
}
