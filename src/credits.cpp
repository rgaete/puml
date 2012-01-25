#include <iostream>
using namespace std;

char * credits[] = {
   "Brian Bowles bowl1714",
   "David Wells well4536", 
   "Jeremy Klas klas1800",
   "Josh Armstrong arms8952",
   "Logan Evans evan1408",
   "Maxine Major majo9411",
   "Morgan Weir weir0050",
   "Nathan Krussel krus8092",
   "Zachary Curtis curt3897"
};

int main(){
    for(int i=0; i<9; i++)
	cout << credits[i] << endl;
}

//test
