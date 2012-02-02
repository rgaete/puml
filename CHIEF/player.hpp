#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class wordlist;                    //prototype to avoid circular dependency

class player
{
        int DIFFICULTY;
        int Gamemode;
        int Score;
        int highscore_easy;
        int highscore_medium;
        int highscore_hard;
        string Name;
        public:
         player();
	 void turn();
         int freeplay(wordlist words, player curr_player);
         int madminute(wordlist words, player curr_player);
         void setdifficulty(string input);
         void setscore(int score);
         void sethighscore(int score);
         void setgamemode(int mode);
         void reset_highscores();
         int getdifficulty();
         int getgamemode();
         int getscore();
         int gethighscore(int difficulty);
};
#endif
