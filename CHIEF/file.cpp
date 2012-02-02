#include <iostream>
#include <fstream>
#include <string>
#include "file.hpp"
using namespace std;

void file::readfile(wordlist &list)
{
        ifstream infile ("list.txt");
        string str;
        while(!infile.eof())
        {
                word *tmp=new word;
                infile >> str;
                tmp->setstring(str);                                                    //put newly read string into newly created word

                if(str.size() <= 1)
                {
                   //skip words that only have 1 letter or less
                }
                else if(str.size() < 5)                                                 //if size of word is less than 5 then put it in the easy difficulty vector
                {
                         list.pushword(tmp, 1);                                         //stores most recent read word into easy vector
                }
                else if(str.size() >= 5 && str.size() < 8)                              //if size of word is in between 5 and 8 letters then put it in the intermediate difficulty vector
                {
                         list.pushword(tmp, 2);                                         //stores most recent read word into medium vector
                }
                else if(str.size() >= 8)                                                //if size or word is over 8 letters long put it in hard difficulty vector
                {
                         list.pushword(tmp, 3);                                         //stores most recent read word into hard vector
                }
        }
}


