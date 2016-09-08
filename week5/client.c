#include <elf.h>
#include <netdb.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#define DATA_SIZE 1024

void main(int argc, char *argv[])
{
   struct addrinfo hints;
   struct addrinfo *result, *rp;
   int sfd, s, j;
   size_t len;
   ssize_t nread;
   char buf[DATA_SIZE];

   // Obtain address matching the host / port
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = 0;
   hints.ai_protocol = 0;

   // "127.0.0.1", "80", service requested, successful results stored in result
   s = getaddrinfo(argv[1], argv[2], &hints, &result);

   // getaddrinfo() returns a list of address structures
   // Try each address until we connect, if it fails close the socket and try again
   for(rp = result; rp != NULL; rp = rp->ai_next) {
       sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
       if(sfd == -1)
           continue;
       if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
           break;

       close(sfd);
   }

   freeaddrinfo(result);

   for(j = 3; j < argc; j++) {
       printf("%s \n", buf);
   }
}
