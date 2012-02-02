#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <string.h>

int main()
{
sockaddr_in serverAddr;
sockaddr &serverAddrCast = (sockaddr &) serverAddr;

int socketid=socket(AF_INET, SOCK_STREAM, 0);

bzero(&serverAddr, sizeof(serverAddr));
serverAddr.sin_family=AF_INET;

serverAddr.sin_addr.s_addr=htons(INADDR_ANY);
serverAddr.sin_port=htons(4501);

bind(socketid, &serverAddrCast, sizeof(serverAddr));

listen(socketid, 5);

for ( ; ; ) 
{
  int connectFd = accept(socketid, (sockaddr *) NULL, NULL);
  shutdown(connectFd,2);
  close(connectFd);
}
}
