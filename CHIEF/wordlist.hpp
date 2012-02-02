#ifndef WORDLIST_H
#define WORDLIST_H
#include <vector>
#include "word.hpp"
#include "player.hpp"

using namespace std;

class wordlist
{
        vector <word> words_easy;                       //holds easy words
        vector <word> words_medium;                     //holds medium words
        vector <word> words_hard;                       //holds hard words
        public:
         void pushword(word *tmp, int difficulty);      //pushes new word into its corresponding difficulty vector
         int grabword(player &curr_player);                     //randomly grabs word out of specified difficulty vector
         word *getwordclass(int difficulty, int index);
};
#endif
