#include<iostream>
#include <fstream>
#include<string>
using namespace std;


int main()
{
	string ip;
	ifstream file ("wordlist.cpp");
	if(file.is_open())
	{
		getline(file,ip);
	}
	char df[20];
	cout<<"\n"<<ip<<endl;
}
