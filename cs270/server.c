#include <netinet/in.h>
#include <string.h>
#include <resolv.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
     struct tm *timecut;
     int socketid, newsocketid, portno, i=0;
     socklen_t addrlength;
     char output[256], temp;
     struct sockaddr_in serv_addr, cli_addr;
     addrlength = sizeof(cli_addr);
     time_t currtime;
     char str[10000];

     int n;
     if (argc < 2) { 					/*must have port specified*/
         fprintf(stderr,"You must have the port number as a command line arguement");
     }
     socketid = socket(AF_INET, SOCK_STREAM, 0);	/*creating socket with  id type AF_INET*/
     if (socketid < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);				/*convert commandline port number to portno*/
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);                /*conver port number to network byte order that sin_port can use*/                         

     if (bind(socketid, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     bind(socketid, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr));

    listen(socketid,4);									/*waiting for client*/
     newsocketid = accept(socketid, (struct sockaddr *) &cli_addr, &addrlength);	/*accepts connection to client*/


    while(1)
    {
      if (newsocketid < 0)
          error("ERROR on accept");
     bzero(output,256);					/*nullify output before reading*/
     n = read(newsocketid,output,255);                 /*read input into output array*/
     while(output[i]!='\0')
	{
		if(output[i]<='z' && output[i]>='a')	/*if lowercase then convert to upper*/
    			{
				temp=output[i];
				output[i]=(temp-32);
			}
		else
			{
				output[i]=output[i];
			}
     	   	i++;
	}
	output[i]='\0'; 			
	i=0;
	write(newsocketid,output,100);			/*send back output to the client with "write"*/
	     
     }
}

