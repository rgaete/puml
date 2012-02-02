#include <time.h>
#include <iostream>
#include "wordlist.hpp"
#include "word.hpp"
using namespace std;


int wordlist::grabword(player &curr_player)
{
        int word_index, difficulty;
        string str;
        srand(time(0));
        difficulty=curr_player.getdifficulty();
        if(difficulty==1)
        {
                int vector_size=(int)words_easy.size();                         //get vector size
                word_index = rand() % vector_size;                              //randomly indexes word in specified difficulty by moding random with vector size
                words_easy[word_index].scramble();                              //calls scramble on the word chosen
        }
        if(difficulty==2)
        {
                int vector_size=(int)words_medium.size();                         //get vector size
                word_index = rand() % vector_size;                              //randomly indexes word in specified difficulty by moding random with vector size
                words_medium[word_index].scramble();                              //calls scramble on the word chosen
        }
        if(difficulty==3)
        {
                int vector_size=(int)words_hard.size();                         //get vector size
                word_index = rand() % vector_size;                              //randomly indexes word in specified difficulty by moding random with vector size
                words_hard[word_index].scramble();                              //calls scramble on the word chosen
        }

        return word_index;

}

void wordlist::pushword(word *tmp, int difficulty)
{
        if(difficulty==1)
        {
                words_easy.push_back(*tmp);
        }
        else if(difficulty==2)
        {
                words_medium.push_back(*tmp);
        }
        else if(difficulty==3)
        {
                words_hard.push_back(*tmp);
        }
}

word *wordlist::getwordclass(int index,int difficulty)
{
        if(difficulty==1)
        {
                return &words_easy[index];
        }
        if(difficulty==2)
        {
                return &words_medium[index];
        }
        if(difficulty==3)
        {
                return &words_hard[index];
        }
}

