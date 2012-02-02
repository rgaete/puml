#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <string.h>

void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
     int socketid, n, newsocketid, portno, clilen;
     char buffer[256];
     portno=4500;
     struct sockaddr_in serv_addr, cli_addr;
     socketid = socket(AF_INET, SOCK_STREAM, 0);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    bind(socketid, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
     listen(socketid, 5);
     clilen = sizeof(cli_addr);
     newsocketid = accept(socketid, (struct sockaddr *)&cli_addr, NULL);
      bzero(buffer,256);
     n = read(newsocketid,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsocketid,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     return 0;
}



