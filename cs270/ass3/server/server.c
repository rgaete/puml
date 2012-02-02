#include <netinet/in.h>
#include <string.h>
#include <resolv.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
//#define socklen_t int

void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
     struct tm *timecut;
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     clilen = sizeof(cli_addr);
     time_t currtime;
     char str[80];

     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
      
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr));
    
     listen(sockfd,5); 

   /* clilen = sizeof(cli_addr);*/
        newsockfd = accept(sockfd, 
                  (struct sockaddr *) &cli_addr, &clilen);
     
      if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
 
     n = read(newsockfd,buffer,255);
     if(buffer[0]=='t' && buffer[1] =='i' && buffer[2]=='m' && buffer[3]=='e' && buffer[4]!='d')
     {
        time(&currtime);
        timecut=localtime(&currtime);
        strftime(str, 100, "the time is %H:%M", timecut);
        puts (str);
     }
     else if(buffer[0]=='d' && buffer[1] =='a' && buffer[2]=='t' && buffer[3]=='e')
     {
        time(&currtime);
        timecut=localtime(&currtime);
        strftime(str, 100, "the date is the %d of %B %Y", timecut);
        puts (str);
     }
     else if(buffer[0]=='t' && buffer[1] =='i' && buffer[2]=='m' && buffer[3]=='e'&& buffer[4]=='d' && buffer[5] =='a' && buffer[6]=='t' && buffer[7]=='e' )
     {
        time(&currtime);
        timecut=localtime(&currtime);
        strftime(str, 100, "the date is the %d of %B %Y and time is %H:%M", timecut);
        puts (str);
     }
     if (n < 0) error("ERROR reading from socket");
     fprintf(stderr, "Here is the message: %s\n",buffer);
     if (n < 0) error("ERROR writing to socket");
     return 0; 
}
