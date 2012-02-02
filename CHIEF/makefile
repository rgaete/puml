wordplay: player.o word.o menu.o wordlist.o main.o file.o
	g++ player.o word.o menu.o wordlist.o main.o file.o -o wordplay
main.o: main.cpp
	g++ -c main.cpp
player.o: player.cpp
	g++ -c player.cpp
word.o: word.cpp
	g++ -c word.cpp
wordlist.o: wordlist.cpp
	g++ -c wordlist.cpp
menu.o: menu.cpp
	g++ -c menu.cpp
file.o: file.cpp
	g++ -c file.cpp
clean: 
	rm player.o word.o main.o wordlist.o menu.o file.o
