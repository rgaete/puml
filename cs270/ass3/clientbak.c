#include <netinet/in.h>
#include <string.h>
#include <resolv.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
    int socketid, port, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char output[256];
    if (argc < 3) {
       fprintf(stderr,"you need a hostname and then a port number as command line arguements");
    }
  while(output[0]!='q' && output[1]!='u' && output[2]!='i')
  {

    port = atoi(argv[2]);
    socketid = socket(AF_INET, SOCK_STREAM, 0);
    if (socketid < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

		serv_addr.sin_port = htons(port);
		int size=sizeof(serv_addr);                                          
		    connect(socketid, (struct sockaddr *) &serv_addr,size);
     		    printf("Please enter the message: ");
		    bzero(output,256);
		    fgets(output,255,stdin);
		    n = write(socketid,output,strlen(output));
		    bzero(output,256);
		    n = read(socketid,output,255);

		    printf("%s\n",output);
   } 
      return 0;
}


