#ifndef WORD_H
#define WORD_H
#include <string>

using namespace std;

class word
{
        string WORD;
        string SCRAMBLED;
        public:
         int compare(string answer);
         void scramble();               //scrambles WORD and stores in SCRAMBLED
         void setstring(string str);
         char *getWORD();               //retrieves WORD
         char *getSCRAMBLED();  //retrieves SCRAMBLED
};
#endif
