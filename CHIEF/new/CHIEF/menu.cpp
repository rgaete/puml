#include <string>
#include <iostream>
#include "menu.hpp"
using namespace std;


void menu::display(player &curr_player)
{
        string input;
        bool mainmenu;
        int highscore;
        cout<<"\nWelcome to Word Play.\n\n*Type \"$quit\" any time to end game. \n*Type \"highscores\" to view highscores for current session.\n*To return to this screen in game type \"$main\" .\n*if you give up on a word type \"$giveup\"\n*To start, type \"start\""<<endl;

        do
        {
                mainmenu=true;                 //stay in main menu, unless changed later
                cout<<"\n>";
                cin>>input;
                if(input=="start")
                {
                       start(curr_player);
                }
                else if(input=="$quit")
                {
                       quit();                 //quit program
                }
                else if(input=="highscores")
                {
                        cout<<"**********Highscores*************\n";
                        highscore=curr_player.gethighscore(1);
                        cout<<"Difficulty        Words"<<endl;
                        cout<<"1                  "<<highscore<<endl;
                        highscore=curr_player.gethighscore(2);
                        cout<<"2                  "<<highscore<<endl;
                        highscore=curr_player.gethighscore(3);
                        cout<<"3                  "<<highscore<<endl;
                        mainmenu=false;       //stay in main menu
                }
                else
                {
                        cout<<"You chose none of the options\n\n"<<endl;
                        mainmenu=false;       //stays in main menu
                }
        }while(mainmenu==false);              //repeats if input was not recognized
}
void menu::start(player &curr_player)
{
        bool valid_input;
        enum gamemode{mad_minute=1, free_play=2};
        string input;
        do
        {
               valid_input=true;                                         //assumes valid input until proven otherwise
               cout<<"\n\n Pick a game mode:\n\n 1 Mad Minute\n 2 Free play\n\n>"<<flush;
               cin>>input;
               if(input=="1" || input=="Mad Minute\n")
               {
                        curr_player.setgamemode(mad_minute);
               }
               else if(input=="2" || input=="Free play\n")
               {
                        curr_player.setgamemode(free_play);
               }
               else
               {
                     cout<<"\nPlease pick a game mode\n"<<endl;
                     valid_input=false;                                  //flag for invalid input
               }
               cout<<"\n\nSet difficulty 1-3 (3 being hardest)>";
               cin>>input;
               if(input>="1" && input<="3")
               {
                      curr_player.setdifficulty(input);                  //set difficulty
               }
               else
               {
                     cout<<"\nInvalid input\n"<<endl;
                     valid_input=false;                                  //flag for invalid input

               }
        }while(valid_input==false);

}

void menu::quit()
{
        exit(0);
}

