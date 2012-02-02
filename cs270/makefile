all: pro
pro: client.o server.o
client.o: client.c 
	gcc -c client.c
server.o: server.c
	gcc -c server.c
clean:
	rm -rf *o pro
