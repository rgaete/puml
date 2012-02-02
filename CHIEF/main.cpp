#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include "menu.hpp"
#include "file.hpp"
#include "player.hpp"

using namespace std;

int main()
{
        int score, gamemode; 
        enum gametype{mad_minute=1, free_play=2};
        file wordfile;
        wordlist words;                                         //words of "wordlist type" holds 3 vectors (one for each difficulty)
        menu Main;
        player Player_1;
        while(true)
        {
                Main.display(Player_1);                         //show menu and set settings
                gamemode=Player_1.getgamemode();                //grabs game mode that was recently set in menui
                wordfile.readfile(words);                       //read words from file and store in vector 
                if(gamemode==mad_minute)
                {
                        Player_1.madminute(words, Player_1);
                        score=Player_1.getscore();              //returns score from game session
                        Player_1.sethighscore(score);           //checks to see if highscore should be set for player
                }
                else if(gamemode==free_play)
                {
                        Player_1.freeplay(words, Player_1);
                }
        }
}
