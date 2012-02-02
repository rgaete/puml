#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
     struct sockaddr_in serv_addr;
    struct hostent *server;

    char output[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
  portno = atoi(argv[2]);			/*assigns port arguement to portno*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);	/*create socket*/
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);		/*serer=host*/
   if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;				
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);				/*initializes host information*/
    serv_addr.sin_port = htons(portno);			/*convert port number into network byte type*/
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 	/*connect/if connection to server fails*/
        error("ERROR connecting");
   while(1) {

  	  printf("Please enter the message: ");
  	  bzero(output,256);
  	  fgets(output,255,stdin);                            /*takes input of client*/
  	  n = write(sockfd,output,strlen(output));	      /*sends input to server*/
  	  if (n < 0) 
  	       error("ERROR writing to socket");
  	  bzero(output,256);				     
  	  n = read(sockfd,output,255);			     /*read server output into output variable*/
  	  if (n < 0) 
       		  error("ERROR reading from socket");
    	printf("%s\n",output);
   }	
    return 0;
}


