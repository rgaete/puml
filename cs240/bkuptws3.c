#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int readinput(char *input);
int runcmd(char **cmd, int pathspec);
int Parse(char **cmd, char *temp);
int pathcheck(char *input, char *PATH);
int aliascheck(char *input, char alias[1000][100], char aliased_cmd[1000][100]);
int addalias(char *input, char alias[1000][100], char aliased_cmd[1000][100]);
int removealias(char *input, char alias[1000][100], char aliased_cmd[1000][100], int aliasindex);
int traverse_aliases(char *input, char alias[1000][100], int searchsection, int aliastotal);
int stringcmp(char *arr, char *input, int stringsize);
int syntaxcheck(char *input, char operator);

int main()
{
  char *cmd[100], input[100], alias[1000][100], aliased_cmd[1000][100], *PATH;
  int m=0, pathspec=0, shellcmd=0, execute_sucess=0;
  FILE *twsrc=fopen(".twsrc","r");                              /*open twsrc file*/
  PATH=getenv("PATH");                                          /*grabbing the true PATH*/

  memset(alias, '\0', sizeof(char) * 1000 * 100);
  memset(aliased_cmd, '\0', sizeof(char) *1000 *100);

    while(fgets(input, 80, twsrc) != NULL)
    {
        shellcmd=aliascheck(input, alias, aliased_cmd);
    }
  while(1)
    {
      pathspec=readinput(input);                                /*take input. pathspec is a flag that determines if the user made the command path specified*/ 
      shellcmd=pathcheck(input, PATH);                          /*is input a PATH command?*/
      shellcmd=aliascheck(input, alias, aliased_cmd);           /*is input an existing alias?*/
      if(shellcmd==0)     /*skips execution step if input was just a shell command*/
	{
	  Parse(cmd, input);                                    /*parsing input into a 2 dimensional array so that execvp can use it*/	  
	  execute_sucess=runcmd(cmd, pathspec);                 /*executes child process to run shell command*/
	}
      shellcmd=0;
    }
}


int readinput(char *input)
{
  int i=-1, pathspec=0;
  printf("\n$");  /*command line symbol*/
      while(input[i]!='\n')
        {
          i++;
          input[i]=getchar();           /*grabing char by char from command line*/
          if(input[i]==EOF)
	    {
	      exit(0);                 /*if user typed control D then terminate shell*/
	    }
          else if(input[i]=='/')
            {
              pathspec=1;              /*path specified input*/
            }
        }     
      input[i+1]='\0';                 /*ending input with NULL for easier string parsing*/
      return pathspec;
}

int runcmd(char **cmd, int pathspec)
{
  int status;
  pid_t pid=fork();

 if(pid<0)   /* if it failed*/
  {
    printf("could not make child process\n");
  }
  else if(pid==0 && pathspec==0)   /*child process*/          /*if not path specific command*/
  {
    printf("it is %d", wait(&status));
    execvp(*cmd, cmd);
    exit(0);
  }
  else if(pid==0 && pathspec==1)                    /*if path specific command*/
    {
      execv(*cmd, cmd);
      pathspec=0;
    }
  else if(pid!=wait(&status))                /*wait for child process to end*/
  {
    printf("parent did not wait for child to end");
  }
  else
  {
    /*do nothing*/
  }
}


int Parse(char **cmd, char *input)
{
  int i=0, flag=0, col=0;
  while(input[i]!='\n')
    {
      if((input[i]==' ' || input[i]=='\t') && flag==1)                   /*NULLing spaces in input*/
        {
          input[i]='\0';   
	  flag=0;
	}
      else if(flag==0)      
	{
	  cmd[col]=&input[i];
	  flag=1;
	  col++;
	}
      i++;
    }
  input[i]='\0';                         /* nullifying the \n character from input*/
  printf("%s\n", input);

}

int pathcheck(char *input, char *PATH)
{
  int i, stringcmd=0;
  char pathstring[10]={'P', 'A', 'T', 'H'};
  stringcmd=stringcmp(pathstring, input, 4); 
   if(stringcmd==1)
    {
      printf("%s\n",PATH);
      return 1;
    }
   else
     {
       return 0;
     } 
}


int aliascheck(char *input, char alias[1000][100], char aliased_cmd[1000][100])
{
  int i, aliascmd=0, aliasindex, unaliascmd=0, q=0,m=0, p=0, correct_syntax=0; 
  static int aliastotal;
  char aliasstring[10]={'a', 'l', 'i','a', 's'};                 /*the string "alias" to compare to user input*/
  char unaliasstring[10]={'u', 'n', 'a', 'l', 'i', 'a', 's'};    /*the string "unalias" to compare to user input*/

  aliascmd=stringcmp(aliasstring, input, 5);                 /*did the user type alias?*/
  unaliascmd=stringcmp(unaliasstring, input, 7);    

  if(aliascmd==1)                      /*****************if input is defining an alias***********************/
    {
      correct_syntax=syntaxcheck(input, '=');                  /*checks if correct syntax was used for alias*/
      
        if(correct_syntax!=1)                                  /*if they used incorrect syntax, ignore command and restart input*/
	  {
	    printf("\n%s\n", "Incorrect usage of alias. example: use alias ls=l");
	  }
        else
	  {
	    aliastotal=addalias(input, alias, aliased_cmd);                   /*if they typed alias, then add the new alias*/
	  }  
	return 1;                                                  /*skip exec command*/
    }
  else if(unaliascmd==1)
    {  
      aliasindex=traverse_aliases(input, alias, 8, aliastotal);
      if(aliasindex==-1)
	{
	  printf("%s\n", "no such alias defined");
	  return 1;
	}
      else
	{
          removealias(input, alias, aliased_cmd, aliasindex);
	}
    }
  else                                 /**************check if input is a pre-existing alias*********************/
    {
      printf("score");
      m=traverse_aliases(input,alias,0,aliastotal);	     
       if(m!=-1)                /*if this is a pre defined alias then use it's real command*/ 
	 {
       	     while(aliased_cmd[m][p]!='\0')
	     {
               input[p]=aliased_cmd[m][p];
	       p++;
	     }
	     input[p]='\0';
       	 }
    }
  return 0;
}

int addalias(char *input, char alias[1000][100], char aliased_cmd[1000][100])
{
  static int aliastotal=0;
  int i=6,m=0;                                       /*i starts as 6 to skip over the "alias" command in string*/
  while(input[i]!='=')
    {
      alias[aliastotal][m]=input[i];
      i++;
      m++;
    }
  m=0;
  i++;                                               /*skip '=' sign*/
   while(input[i]!='\0')
    {
      aliased_cmd[aliastotal][m]=input[i];          /*grab right side of equal sign and store real cmd in aliased_cmd*/
      i++;
      m++;
    }
    aliastotal++;
    return aliastotal;
}


int removealias(char *input, char alias[1000][100], char aliased_cmd[1000][100],int aliasindex)
{
  while(*alias[aliasindex]!='\0')
    {
      *alias[aliasindex]=*alias[aliasindex+1];
      *aliased_cmd[aliasindex]=*aliased_cmd[aliasindex+1];
      aliasindex++;
    }
}

int traverse_aliases(char *input, char alias[1000][100], int searchsection, int aliastotal)
{
  printf("the alias total is %d", aliastotal);
  int n=0, p=0, k=0, i=searchsection;
  while(alias[n][p]!='\0')
    {
      printf("%s\n%s\n", input, alias[n]);
      if(alias[n][p]==input[i])    /*traverse aliases in search of portion of input specified by searchsection*/
	{
	  k=1;
	  p++;
	  i++;
	}
      else
	{
	  k=0;
	  n++;
	  p=0;
	  i=searchsection;
	}
    }
 if(k==1)
   {
     return n;          /*returns which block in the alias array that the alias is stored*/
   }
 else
   {
     return -1;
   }
}

int stringcmp(char *arr, char *input, int stringsize)
{
  int i=0, g=0;
  for(i=0;i<stringsize;i++)
    {
      if(arr[i]==input[i])     /*did the user type alias?*/
        {
          g=1;
        }
      else
        {
          g=0;
          return 0;
        }
    }
  return 1;
}
int syntaxcheck(char *input, char operator)
{
  int correct_syntax=0, q=0;
  while(input[q]!='\0')
    {
      if(input[q]==operator)
	{
	  correct_syntax=1;                              /*checks for correct usage of alias (i.e. alias ls=l)*/
	  return 1;
	}
      q++;
    }
  if(correct_syntax!=1)                                  /*if they used incorrect syntax, ignore command and restart input*/
    {
      return 0;
    }
}
