#include <string>
#include <algorithm>
#include "word.hpp"
using namespace std;

int word::compare(string answer)
{
        if(answer==WORD)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

char *word::getWORD()
{
        char *cstr;
        cstr = new char [WORD.size()+1];
        strcpy (cstr, WORD.c_str());
        return cstr;
}

char *word::getSCRAMBLED()
{
        char *cstr;
        cstr = new char [SCRAMBLED.size()+1];
        strcpy (cstr, SCRAMBLED.c_str());
        return cstr;
}
void word::scramble()
{
        int random_index, old_index, word_size;
        char temp;
        string str;
        srand( time(0) );
        word_size=WORD.size();
        for(int swaps=0; swaps<10; swaps++)                             //Swaps the elements n number of times
        {
                old_index = random_index = rand() % word_size;          //set random integer that less than or equal to string size
                temp=SCRAMBLED[random_index];                           //randomly pick character and store in temp
                random_index = rand() % word_size;                      //randomly pick another character
                SCRAMBLED[old_index]=SCRAMBLED[random_index];           //perform swap on both elements...
                SCRAMBLED[random_index]=temp;                      
        }

}

void word::setstring(string str)
{
        transform(str.begin(), str.end(), str.begin(), ::tolower);                      //convert string to lowercase
        WORD=str;
        SCRAMBLED=str;
}

