#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <fstream>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>

using namespace std;

int main()
{
  char input[256];
  int n;
  char datestring[256];
  unsigned char isFile=0x8;
  struct tm *tm;
  cin.getline (input, 256, '\n' ); 
  struct dirent *dbuf;
  DIR *dir;
  struct group *grp;
  dir = opendir(".");
  struct stat results;
  if(input[0]=='l' && input[1]=='s' && input[2]!=' ')
  {  
         dir=opendir(".");
         while((dbuf=readdir(dir)) !=NULL)
         {
            stat(dbuf->d_name, &results);
            cout<<dbuf->d_name<<endl;
         } 
  }
  else if(input[0]=='l' && input[1]=='s' && input[2]==' ' && input[3]=='-' && input[4]=='t'   )
  {
         dir=opendir(".");

         while((dbuf=readdir(dir)) !=NULL)
         {
            stat(dbuf->d_name, &results);
            tm = localtime(&results.st_mtime);
            strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
            cout<<endl<<dbuf->d_name<<endl<<"LAST MODIFIED DATE: "<<datestring<<"     "<<"     ";
             tm = localtime(&results.st_atime);
            strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
            cout<<"LAST ACCESSED DATE: "<<datestring<<"     ";
            tm = localtime(&results.st_ctime);
            strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
            cout<<"LAST STATUS CHANGE: "<<datestring<<"     "<<endl;
         }
  }
  else if(input[0]=='l' && input[1]=='s' && input[2]==' ' && input[3]=='-' && input[4]=='l')
  {
      dir=opendir(".");

      while((dbuf=readdir(dir)) !=NULL)
      {
        stat(dbuf->d_name, &results);
        cout<<dbuf->d_name<<endl<<"OWNER ID: "<<results.st_mode<<endl<<"NUMBER OF LINKS:"<<results.st_nlink<<endl<<"SIZE:"<<results.st_size<<endl<<endl;
        tm = localtime(&results.st_mtime);
        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
        cout<<endl<<"LAST MODIFIED DATE: "<<datestring<<"     "<<"     ";
        tm = localtime(&results.st_atime);
        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
        cout<<"LAST ACCESSED DATE: "<<datestring<<"     ";
        tm = localtime(&results.st_ctime);
        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
        cout<<"LAST STATUS CHANGE: "<<datestring<<"     "<<endl<<endl;
 
     }
  }
  else if(input[0]=='l' && input[1]=='s' && input[2]==' ' && input[3]=='-' && input[4]=='f')
  {
       dir=opendir(".");
       dbuf=readdir(dir);
       int type,k, i;
       unsigned char x;
       int n=0;
       int ASCII=1, DOS=0, BIN=0; 
       ifstream currfile;
       string line;
       stat(dbuf->d_name, &results);
       while((dbuf=readdir(dir)) !=NULL)
       {
         while(dbuf->d_name[n]!='\0')
         {
            if(dbuf->d_name[n]=='.' && dbuf->d_name[n+1]!='.')
            {
              n++;
              if(dbuf->d_name[n]=='o' && dbuf->d_name[n+1]=='\0')
              {
                 cout<<dbuf->d_name<<"   is an object file"<<endl;
              }
              else if(dbuf->d_name[n]=='o' && dbuf->d_name[n+1]=='u' && dbuf->d_name[n+2]=='t')
              {
                 cout<<dbuf->d_name<<"   is an executable"<<endl;
              }
            }
            if(dbuf->d_name[n]=='\0')
            {
            }
            else
              n++;
          }
        
         if ( dbuf->d_type == isFile)
         {
           currfile.open(dbuf->d_name);
           for(k=0;k<=20;k++)
           {  
             currfile >> x;
     
             if(x<128)
             {
                if(x=='\13')
                {
                   currfile>>x;
                   if(x=='\10')
                   {
                      DOS=1;
                   }
                }
             }
             else
             { 
                ASCII=0; 
                break;
             }
           }
           currfile.close();    
          }
          if(ASCII==1)
          {
            cout<<dbuf->d_name<<" is an ASCII file"<<endl;
            if(DOS==1)
            {
              cout<<dbuf->d_name<<" is DOS file"<<endl;
              DOS=0;
            }
          }                      
          else
          {
             cout<<dbuf->d_name<<" is an unidentifiable binary file"<<endl;
             ASCII=1;
          }
          n=0; 
         cout<<endl;
       } 
   }
}

