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
     int socketid, newsocketid, portno;
     socklen_t addrlength;
     char output[256];
     struct sockaddr_in serv_addr, cli_addr;
     addrlength = sizeof(cli_addr);
     time_t currtime;
     char str[80];

     int n;
     if (argc < 2) {
         fprintf(stderr,"You must have the port number as a command line arguement");
     }
     socketid = socket(AF_INET, SOCK_STREAM, 0);
     if (socketid < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);                                         

     if (bind(socketid, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     bind(socketid, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr));

     listen(socketid,4);

    while(output[0]!='q' && output[1]!='u' && output[2]!='i')
    {

      newsocketid = accept(socketid, (struct sockaddr *) &cli_addr, &addrlength);

      if (newsocketid < 0)
          error("ERROR on accept");
     bzero(output,256);

     n = read(newsocketid,output,255);
     if(output[0]=='t' && output[1] =='i' && output[2]=='m' && output[3]=='e' && output[4]!='d')
     {
      	time(&currtime);
        timecut=localtime(&currtime);
        strftime(str, 100, "the time is %H:%M", timecut);
        puts (str);
        write(newsocketid,str,100);

     }
     else if(output[0]=='d' && output[1] =='a' && output[2]=='t' && output[3]=='e')
     {
      	time(&currtime);
        timecut=localtime(&currtime);
        strftime(str, 100, "the date is the %d of %B %Y", timecut);
        puts (str);
        write(newsocketid,str,100);

     }
     else if(output[0]=='t' && output[1] =='i' && output[2]=='m' && output[3]=='e'&& output[4]=='d' && output[5] =='a' && output[6]=='t' && output[7]=='e' )
     {
      	time(&currtime);
        timecut=localtime(&currtime);
        strftime(str, 100, "the date is the %d of %B %Y and time is %H:%M", timecut);
        puts (str);
        write(newsocketid,str,100);
     }
   }
	
}




