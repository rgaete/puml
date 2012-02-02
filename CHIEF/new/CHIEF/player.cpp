#include <time.h>
#include <string>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "player.hpp"
#include "wordlist.hpp"



using namespace std;

bool times_up=false;   //Global variables due to limited "signal function" can not pass values. Madminute's event loop is based on "timed".
int  status;           //used by parent to wait on child and collect status
 

void timer(int param)
{
        wait(&status);      // Wait for child process                  
        times_up=true;            //set global "timed" flag to 1 for parent to exit loop
}

int player::getdifficulty()
{
        return DIFFICULTY;
}

void player::setgamemode(int mode)
{
        Gamemode=mode;
}

int player::getgamemode()
{
        return Gamemode;
}

void player::setdifficulty(string input)
{
        DIFFICULTY=atoi(input.c_str());
}

int player::freeplay(wordlist words, player curr_player)
{
         time_t start, end;
         bool solved=false, main_menu=false;
         int index;
         int difficulty=getdifficulty();                              //grabs difficulty from player to later be used as vector index for wordlist
         double dif;
         word *tmp=new word;
         string input, scrambled_word, word;
         while(main_menu==false)                                      //run mode as long as user did not go to main menu 
         {
                time(&start);
                index=words.grabword(curr_player);
                while(solved==false)                                  //while word remains unsolved keep excecuting loop
                {
                        tmp=words.getwordclass(index, difficulty);    //returns pointer to current word
                        scrambled_word=tmp->getSCRAMBLED();           //returns scrambled word
                        cout<<scrambled_word<<">";
                        cin>>input;

                        if(input=="$quit")                            //quit program
                        {
                               exit(0);
                        }
                        else if(input=="$main")                       //exit loop and return to main menu
                        {
                                main_menu=true;
                                break;
                        }
                        else if(input=="$giveup")                               //if user gives up then tell them the word and move on
                        {
                                word=tmp->getWORD();
                                cout<<"\n\nThe word was \""<<word<<"\"\n"<<endl;
                                index=words.grabword(curr_player);              //pick new word 
                        }
                        solved=tmp->compare(input);                             //compare() tests input to word and returns 1 or 0 to solved
                        cout<<endl;
                }
                time(&end);
                dif = difftime (end,start);                            //takes time differnce from start and answer
                word=tmp->getWORD();                                   //grab final word
                cout<<"GREAT!\n\nTime: "<<dif<<" seconds to solve for \""<<word<<"\""<<endl<<endl;
                solved=false;
         }
}

int player::madminute(wordlist words, player curr_player)
{
        int index, SCORE=0, difficulty=getdifficulty();
        bool solved=false;
        word *tmp=new word;
        string input, scrambled_word, word;
        cout<<"\nYou chose MAD MINUTE. You have 60 seconds to solve as many words as you can.\nCOUNTDOWN: "<<endl;
        for(int i=3;i>0;i--)                    //coutdown till mad minute
        {
                cout<<i<<endl;
                sleep(1);
        }
        cout<<"GO!"<<endl;
        pid_t pID=fork();                       //fork process to be used as daemon timer
        if(pID<0)                               //error forking
        {
                cerr<<"ERROR: was unable to make timer"<<endl;
                exit(0);
        }
        else if(pID == 0)                      //catch child process
        {
                sleep(60);                              //child sleeps for 60 seconds while parent excecutes game loop
                kill(getppid(), SIGALRM);               //send signal to parenti
                cout<<"\n****TIME UP*****\n";
                exit(0);                                //send signal
        }
        else
        {
                while(times_up!=true)
                {
                        index=words.grabword(curr_player);

                        signal(SIGALRM, timer);                                //upon the child waking go to function timeup()
                        tmp=words.getwordclass(index, difficulty);              //returns pointer to current word
                        scrambled_word=tmp->getSCRAMBLED();                     //stores scrambled word to var
                        cout<<scrambled_word<<">";
                        cin>>input;

                        if(input=="$quit")                      //quit program
                        {
                              exit(0);
                        }
                        else if(input=="$main")                 //close game and go to main menu
                        {
                                kill(pID, SIGTERM);             //interrupt and kill daemon timer
                                wait(&status);                  //collect child process to avoid zombie
                                return 0;
                        }

                        solved=tmp->compare(input);             //compare() tests input to word and returns 1 or 0 to solved
                        cout<<endl;
                        if(solved==true)                           //if last word was solved, then incriment score
                        {
                                cout<<"Solved!"<<endl;
                                SCORE++;
                                solved=false;
                        }
                }
                setscore(SCORE);
                times_up=false;
              }
}

void player::setscore(int new_score)                            //set score of player after mad minute
{
        Score=new_score;
}

int player::getscore()
{
        return Score;
}
void player::sethighscore(int SCORE)
{ 
        int difficulty=getdifficulty();
        if(difficulty==1 && highscore_easy<SCORE)            //easy difficulty
        { 
                cout<<"*****WOW! New highscore for Easy Mad Minute******"<<endl;
                highscore_easy=SCORE;
                sleep(1);                                    //let user see message before main menu called
        } 
        else if(difficulty==2 && highscore_medium<SCORE)     //medium difficulty
        {
                cout<<"*****WOW! New highscore for Medium Mad Minute******"<<endl;
                highscore_medium=SCORE;
                sleep(1);                                    //let user see message before main menu called
        }
        else if(difficulty==3 && highscore_hard<SCORE)       //hard difficulty
        {
                cout<<"*****WOW! New highscore for Hard Mad Minute******"<<endl;
                highscore_hard=SCORE;
                sleep(1);                                    //let user see message before main menu called
        }


}
void player::reset_highscores()                              //initialize all high scores to 0
{
        highscore_easy=0;
        highscore_medium=0;
        highscore_hard=0;
}
int player::gethighscore(int difficulty)
{
        if(difficulty==1)
        {
                return highscore_easy;
        }
        else if(difficulty==2)
        {
                return highscore_medium;
        }
        else if(difficulty==3)
        {
                return highscore_hard;
        }
}
