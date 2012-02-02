#include <stdio.h>
#include <stdlib.h>
int makearg(char *s, char **args[]);

int main()
{
  char **argv, str[100];
  int argc, m=0, i=0, k=-1;
  printf("%s", "Enter text>");
  while(str[k]!='\n')
    {
      k++;
      str[k]=getchar();          /*receiving input*/
    }

  argc=makearg(str, &argv);                /*stores input into 2-D array via passing a pointer to the 2d array*/
  printf("\nthe amount of arguements are %d \n\n",argc);


  while(m<argc)
    {
      printf("%s", argv[m]);
      printf("\n");
      m++;
    }
}

int makearg(char *s, char **args[])
{
  int i=0, tok=0, flag=0, row=0, col=0;

  char **tmp=(char **)malloc(1000*(sizeof(char *)));/*creates 2-d array*/
  if(tmp=='\0')
    {
      return -1;
    }

  while(s[i]!='\0')
    {
      if(s[i]!=' ' && flag==0)
	{
	  tmp[col]=&s[i];                           /*have 2-d array point to input address*/
	  flag=1;
	}
      else if(s[i]==' ' && flag==1)
	{
	  tmp[col][row]='\0';/*nullifying spaces*/
	  row=0;
	  col++;/*increment to next word*/
	  flag=0;
	  tok++;
	}
      i++;
      if(s[i]=='\n')
        {
          s[i]='\0';/*when you get to \n, end array with null*/
        }

      if(flag==1)
	{
	  row++;
	}
    }
  tok++;
  *args=tmp;    /* makes args point to 2 dimensional array*/
  return tok;
}
