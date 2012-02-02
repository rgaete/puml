#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

class word
{
	 string WORD;	
	 string SCRAMBLED;
	public:
	 int compare(string answer);
	 void scramble();		//scrambles WORD and stores in SCRAMBLED
	 void setstring(string str);
	 char *getWORD();		//retrieves WORD
	 char *getSCRAMBLED();	//retrieves SCRAMBLED
};

class wordlist
{
	vector <word> words_easy;			//holds easy words
	vector <word> words_medium;			//holds medium words
	vector <word> words_hard;			//holds hard words
	public: 
	 void pushword(word *tmp, int difficulty);	//pushes new word into its corresponding difficulty vector
	 int grabword(int difficulty);			//randomly grabs word out of specified difficulty vector
	 word *getwordclass(int difficulty, int index);
};


class file
{
	public:
	  void readfile(wordlist &list);
};

int wordlist::grabword(int difficulty)
{
        int word_index;
        string str;
        srand(time(0));
        if(difficulty==1)
        {
                int vector_size=(int)words_easy.size();				//get vector size
                word_index = rand() % vector_size;                              //randomly indexes word in specified difficulty by moding random with vector size
                words_easy[word_index].scramble();                              //calls scramble on the word chosen
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

void playerturn(wordlist words, int index, int difficulty)
{
	 time_t start, end;
         double dif;
	 word *tmp=new word;
	 int solved=0;		
         string input, scrambled_word;
	 time(&start);
	while(solved==0)			//while word remains unsolved keep excecuting loop
	{ 
		if(input=="$quit")			//quit program
        	 {
        	      exit(0);
       	 	 }
	 	 else if(input=="$main")
	 	 {
	 	     //settings(0);
	 	 }
		tmp=words.getwordclass(index, difficulty);		//returns pointer to current word
		scrambled_word=tmp->getSCRAMBLED();			//stores scrambled word to var
		cout<<scrambled_word<<">";
		cin>>input;
		solved=tmp->compare(input);				//compare() tests input to word and returns 1 or 0 to solved
		cout<<endl;
	}
	 time(&end);
         dif = difftime (end,start);				//takes time differnce from start and answer 
         cout<<"Time: "<<dif<<" seconds"<<endl;
	
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

void settings(int &difficulty)
{
	string input;
	cout<<"Welcome to Word Play.\nType \"$quit\" any time to end game. \n\n*To return to this screen in game type \"$main\" .\n*To view highscores type \"highscores\"\n*To start, type \"start\""<<endl<<">"; 
	cin>>input;
	if(input=="start")
	{
		cout<<"\n\nSet difficulty 1-3 (3 being hardest)>";
		cin>>input;
		if(input>="1" && input<="3")
		{
			difficulty=atoi(input.c_str());				//set difficulty
		}
		else
		{
		
		}
	}
	 if(input=="$quit")
	{
		exit(0); 		//quit program
	}
	else if(input=="highscores")
	{
		//
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
	for(int swaps=0; swaps<10; swaps++)				//Swaps the elements n number of times
	{
		old_index = random_index = rand() % word_size;		//set random integer that less than or equal to string size
		temp=SCRAMBLED[random_index];				//randomly pick element
		random_index = rand() % word_size;			//randomly pick another element
		SCRAMBLED[old_index]=SCRAMBLED[random_index];		//perform swap on both elements...
		SCRAMBLED[random_index]=temp;					
	}
	
}

void file::readfile(wordlist &list)
{
        ifstream infile ("list.txt");
      	string str;
        while(!infile.eof())
        {
	        word *tmp=new word;	
	        infile >> str;
		tmp->setstring(str);						//put newly read string into newly created word

		if(str.size() <= 1)
		{
			//skip words that only have 1 letter or less
		}
	        else if(str.size() < 5)                                             //if size of word is less than 5 then put it in the easy difficulty vector
                {
                         list.pushword(tmp, 1);                                         //stores most recent read word into easy vector
                }
                else if(str.size() >= 5 && str.size() < 8)                 //if size of word is in between 5 and 8 letters then put it in the intermediate difficulty vector
                {
                 	 list.pushword(tmp, 2);						//stores most recent read word into medium vector
                }
                else if(str.size() >= 8)                                            //if size or word is over 8 letters long put it in hard difficulty vector
                {
                    	 list.pushword(tmp, 3);                                         //stores most recent read word into hard vector
                }
	}
}

void word::setstring(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);			//convert string to lowercase
	WORD=str;
	SCRAMBLED=str;
}

int main()
{
	int difficulty, word_index;
	file wordfile;	
	wordlist words;					//words of "wordlist type" holds 3 vectors (one for each difficulty)
	settings(difficulty);
	wordfile.readfile(words);			//read words from file and store in vector 
//	while(1)
//	{
	
   	        word_index=words.grabword(difficulty);			//returns an index to newly scrambled word
		playerturn(words, word_index, difficulty);			//take user answer	
//	}
}


