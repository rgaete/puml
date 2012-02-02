#include <string>
#include "player.hpp"

using namespace std;

class menu
{
        public:
         void display(player &curr_player);
         void quit();
         void start(player &curr_player);
         void gamemode();
         int setdifficulty(string input);
         void setinput(string input);
         char *getinput();
         void setgamemode(int mode);
};

