#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int runcmd(char **cmd);
int Parse(char **cmd,char *temp);
void history(char *temp, char hist_buff[100][100], int hist_n, int hist_max, int i);

int main()
{
  char *cmd[100], temp[100], hist_buff[100][100];
  int i=-1, m=0, hist_max=100, hist_n=0;
 
   while(temp[i]!=EOF)
    {
      printf("\n$");  /*command line symbol*/
      while(temp[i]!='\n')
	{
	  i++;
	  temp[i]=getchar(); /*grabing char by char from command line*/
          if(temp[i]==EOF)
          {
             exit(0);
          }
        }

      history(temp, hist_buff, hist_n, i, hist_max);

      Parse(cmd, temp);    /*parsing input into a 2 dimensional array so that execvp can use it*/
      runcmd(cmd);         /*executes child process to run shell command*/
      i=-1;
    } 
}


int runcmd(char **cmd)
{
  int status;
  pid_t pid=fork();

 if(pid<0)   /* if it failed*/
  {
    printf("could not make child process\n");
  }
  else if(pid==0)   /*child process*/
  {
    printf("it is %d", wait(&status));
    execvp(*cmd, cmd);
    exit(0);
  }
  else if(pid!=wait(&status))                /*wait for child process to end*/
  {
    printf("parent did not wait for child to end");
  }
  else
  {
    // exit(0);
  }
}


int Parse(char **cmd, char *temp)
{
  int i=0, flag=0, col=0;
  while(temp[i]!='\n')
    {
      if((temp[i]==' ' || temp[i]=='\t') && flag==1)  /*NULLing spaces in input*/
        {
          temp[i]='\0';   
	  flag=0;
	}
      else if(flag==0) 
	{
	  cmd[col]=&temp[i];
	  flag=1;
	  col++;
	}
      i++;
    }
  temp[i]='\0';  /* nullifying the \n character from input*/
}

void history(char *temp, char hist_buff[100][100], int hist_n, int i, int hist_max)
{
  int k, g;
    for(k=0;k<=i;k++)
    {
      hist_buff[hist_n][k]=temp[k];      /* transfer last input into history buffer*/
    }
   for(g=0;g<i;g++)
     {
       printf("array has %c", hist_buff[hist_n][g]);
     }
}
