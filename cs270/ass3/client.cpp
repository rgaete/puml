#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <string.h>

int main()
{
  sockaddr_in serverAddr;
  sockaddr &serverAddrCast=(sockaddr &) serverAddr;

  int socketid= socket(AF_INET, SOCK_STREAM, 0);
  bzero(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family=AF_INET;
   serverAddr.sin_port=htons(4500);
  connect(socketid, &serverAddrCast, sizeof(serverAddr));
shutdown(socketid, 2);
close(socketid);
}

