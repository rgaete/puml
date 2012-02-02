#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int linecount(int argc, char *argv[]);
int textfilecheck(int argc, char *argv[]);
int wordcount(int argc, char *argv[]);
int charcount(int argc, char *argv[]);
int uppercase(int argc, char *argv[], int flag_s);
int numberlines(int argc, char *argv[], int flag_s);
char *itoa(int n, char s[], int b);
void reverse(char s[]);
char *strrev(char *str);
size_t strlen(const char *string);
int uppercasestd(int argc, char std[20], int flag_s);
int numberlinesstd(int argc, char std[20], int flag_s);
int wordcountstd(int argc, char std[20]);
int charcountstd(int argc, char std[20]);
int linecountstd(int argc, char std[20]);



int main(int argc, char *argv[]) 
{	

	int linenum, read=0, wordnum, charnum, n=1, i=0, flag_l=0, flag_w=0, flag_c=0, flag_u=0, flag_n=0, flag_s=0,m=1;
	char flag, stdfile[20];                         /*holds flags from commandline*/
        
	if(argc<2)
        {
		exit(0);
        }

	
	while(argv[m][0]=='-')
	{
	 	if(argv[argc-1][0]=='-')                /*if there was no filename given then exit*/
 	        {
             	        printf("\n%s", "enter a file name>");
             	        do
			{
				stdfile[i]=getchar();	
				i++;			
			}while(stdfile[i-1]!='\n');
			stdfile[i-1]='\0';
			 read=1;
		}

		while(argv[m][n]!='\0')              /*grab every flag*/
	        {	
          		flag=argv[m][n];	     
		
			if(flag=='l')                 /*set flags based on command line flags*/
			{
				flag_l=1;
			}
			if(flag=='w')
			{
				flag_w=1;
			}
			if(flag=='c')
			{
				flag_c=1;
			}
			n++;
			if(flag=='u')
			{
				flag_u=1;
			} 
			if(flag=='n')
			{
				flag_n=1;
			}
	    		if(flag=='s')
			{
				flag_s=1;
			}
		}
       	        if(argv[argc-1][0]=='-')      
                {
                     break; 
                }

		n=1;
		m++;
	}
	if(argv[argc-1][0]!='-')		     /*if last arguement is not a flag*/
	{
		textfilecheck(argc-1, argv);
	} 
        if(flag_l==1)                                /*line count flag*/
	{
		if(read==1)
                {
                        linenum=linecountstd(argc, stdfile);
                }
		else
		{
			linenum=linecount(argc, argv);
		}
		printf("\n\nnumber of lines is: %d\n", linenum); 
	}
	if(flag_w==1)                                /*word count flag*/
	{
		if(read==1)
                {
			wordnum=wordcountstd(argc, stdfile);
                }
		else
		{
			wordnum=wordcount(argc, argv);
		}
		printf("\n\nnumber of words is: %d\n", wordnum);
	}

	if(flag_c==1)				    /*char count flag*/
	{
		if(read==1)
                {
                        charnum=charcountstd(argc, stdfile);
                }
		else
		{
			charnum=charcount(argc, argv);
		}
		printf("\n\nnumber of characters is: %d\n", charnum);
	}
	if(flag_u==1)				    /*convert lower case to uppercase*/
	{
		if(read==1)
		{
			uppercasestd(argc, stdfile, flag_s);
		}
		else
		{
	        	uppercase(argc,argv, flag_s);
		}
	}
	if(flag_n==1)
	{
  	        if(read==1)
                {
                        numberlinesstd(argc, stdfile, flag_s);
                }
		else
		{
			numberlines(argc, argv, flag_s);
		}
	}

	printf("\n");                                  /*format*/
}

int linecount(int argc, char *argv[])
{
	FILE *fp;
	char ch;
	int linenum=0;

	fp=fopen(argv[argc-1], "r");
	while(1)
	{
		ch=fgetc(fp);
		if(ch==EOF)
		{
			break;
		}
		else if(ch=='\n')
		{
			linenum++;    /*for every new line char incriment line number*/
		}
	}
	return linenum;
}       

int linecountstd(int argc, char std[20])
{
        FILE *fp;
        char ch;
        int linenum=0;

        fp=fopen(std, "r");
        while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }
                else if(ch=='\n')
                {
                        linenum++;    /*for every new line char incriment line number*/
                }
        }
        return linenum;
}
 

int wordcount(int argc, char *argv[])
{
	FILE *fp;
        char ch;
        int wordnum=0;

        fp=fopen(argv[argc-1], "r");                      /*open file with read priv*/
        
	while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }
                else if(ch==' ' || ch=='\t' || ch=='\n')		/*any space or tab represents a new word*/
                {
			while(ch==' ' || ch=='\t' || ch=='\n')
			{
				ch=fgetc(fp);
			}
                        wordnum++;
                }
        }
        return wordnum;
}

int wordcountstd(int argc, char std[20])
{
        FILE *fp;
        char ch;
        int wordnum=0;

        fp=fopen(std, "r");                      /*open file with read priv*/

        while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }
                else if(ch==' ' || ch=='\t' || ch=='\n')                /*any space or tab represents a new word*/
                {
                        while(ch==' ' || ch=='\t' || ch=='\n')
                        {
                                ch=fgetc(fp);
                        }
                        wordnum++;
                }
        }
        return wordnum;
}

int textfilecheck(int argc, char *argv[])
{
        FILE *fp;
	char ch;

        fp=fopen(argv[argc], "r");			/*open file with read priv*/
         while(1)
         {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                     break;
                }
                else if( ((ch < '\0') || (ch > '~')))		/*if it contains ascii outside of alphabet bound then it is not a text file*/
                {    
                    printf("\n%s\n\n", "this is not a text file");                  
                    exit(0);
                }
          }
}

int charcount(int argc, char *argv[])
{
        FILE *fp;
        char ch;
        int charnum=0;

        fp=fopen(argv[argc-1], "r");			/*open file with read priv*/
        while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }
                charnum++;				/*for every char read, incriment charnum*/
        }
        return charnum;
}

int charcountstd(int argc, char std[20])
{
        FILE *fp;
        char ch;
        int charnum=0;

        fp=fopen(std, "r");                    /*open file with read priv*/
        while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }
                charnum++;                              /*for every char read, incriment charnum*/
        }
        return charnum;
}

int uppercase(int argc, char *argv[], int flag_s)
{
	FILE *fp;
        char ch, CH;

        fp=fopen(argv[argc-1], "r+");
        while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }
		if(ch >= 'a' && ch <= 'z')            /*if lowercase*/
		{ 
			CH=ch-32;		      /*convert to upper*/

   			if(flag_s==1)
			{
				printf("%c", CH);
			}
			else
			{	
				fseek(fp, -1, SEEK_CUR);      /*overwrite lower case letter with new uppercase*/
				fputc(CH, fp);
			}
		}
		if(flag_s==1 && ch==' ')
		{
			printf("%c", ' ');
		}
		 if(flag_s==1 && ch=='\n')
                {
                        printf("%c", '\n');
                }
	        if(flag_s==1 && (ch>='A' && ch<='Z'))
                {
                        printf("%c", ch);
                }
        }
}

int uppercasestd(int argc, char std[20], int flag_s)
{
        FILE *fp;
        char ch, CH;

        fp=fopen(std, "r+");
        if(fp==NULL)
        {
                printf("no such file");
                exit(0);
        }

        while(1)
        {
                ch=fgetc(fp);
                if(ch==EOF)
                {
                        break;
                }

                if(ch >= 'a' && ch <= 'z')            //if lowercase
               	{
               	        CH=ch-32;                      //   convert to upper

      	               	if(flag_s==1)
       	              	{
       	                   	  printf("%c", CH);
       	              	}
                   	 else
                      	{
                         	 fseek(fp, -1, SEEK_CUR);    
				fputc(CH, fp);
               		}
		 }
                if(flag_s==1 && ch==' ')
                {
                        printf("%c", ' ');
                }
                 if(flag_s==1 && ch=='\n')
                {
                        printf("%c", '\n');
                }
                if(flag_s==1 && (ch>='A' && ch<='Z'))
                {
                        printf("%c", ch);
                }
        }
}




int numberlines(int argc, char *argv[], int flag_s)
{ 
        FILE *fp;
        char ch[100000], convert[128];
	int linenum=1, n=0;
	
        fp=fopen(argv[argc-1], "r+");		/*open with read/write privliges*/
        if(fp==NULL)
        {
                printf("no such file");
                exit(0);
        }

	while(1)
        {
                ch[n]=fgetc(fp);
                if(ch[n]==EOF)
                {
                        break;			/*break once at enf of file*/
                }
		n++;
        
	}
	n++;
	ch[n]='\0';				/*nullifying array*/
	n=0;
	while(ch[n+1]!='\0')
	{
		if(flag_s==1)
		{
			printf("%d ", linenum);
			while(ch[n]!='\n')
                        {
                                printf("%c", ch[n]);
                                n++;
                        }
			printf("%c", '\n');
			linenum++;
			n++;
			
		}
		else
		{
	  	        fseek(fp, n, SEEK_SET);         /*overwrite old text*/
                      	 itoa(linenum, convert, 10);     /*convert int to char*/
         	        fputs(convert, fp);             /*put converted int to string in front of line*/
    	                fputc(' ', fp);               /*format*/
                 
			while(ch[n]!='\n')
			{
				fputc(ch[n], fp);
				n++;
			}
			fseek(fp, n, SEEK_SET); 
			fputc('\n',fp);			/*place new line down after a new line was read*/
			linenum++;
			n++;
		}
	}
}

int numberlinesstd(int argc, char std[20], int flag_s)
{
	 FILE *fp;
        char ch[100000], convert[128];
        int linenum=1, n=0;

        fp=fopen(std, "r+");           /*open with read/write privliges*/
        if(fp==NULL)
	{
		printf("no such file");
		exit(0);
	}
	while(1)
        {
                ch[n]=fgetc(fp);
                if(ch[n]==EOF)
                {
                        break;                  /*break once at enf of file*/
                }
                n++;

        }
        n++;
        ch[n]='\0';                             /*nullifying array*/
        n=0;
        while(ch[n+1]!='\0')
        {
                if(flag_s==1)
                {
                        printf("%d ", linenum);
                        while(ch[n]!='\n')
                        {
                                printf("%c", ch[n]);
                                n++;
                        }
                        printf("%c", '\n');
                        linenum++;
                        n++;

                }
                else
                {
                        fseek(fp, n, SEEK_SET);         /*overwrite old text*/
                         itoa(linenum, convert, 10);     /*convert int to char*/
                        fputs(convert, fp);             /*put converted int to string in front of line*/
                        fputc(' ', fp);               /*format*/

                        while(ch[n]!='\n')
                        {
                                fputc(ch[n], fp);
                                n++;
                        }
                        fseek(fp, n, SEEK_SET);
                        fputc('\n',fp);                 /*place new line down after a new line was read*/
                        linenum++;
                        n++;
                }
        }
}


	
char *itoa(int n, char *s, int b) {                  /*function i found on the internet*/
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;
    
	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	return strrev(s);
}

char *strrev(char *str) {				 /*function i found on the internet*/

	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}

size_t strlen(const char *string) {		 /*function i found on the internet*/

	const char *s;

	s = string;
	while (*s)
		s++;
	return s - string;
}
