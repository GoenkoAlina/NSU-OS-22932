all: server client
server: server.o
	gcc server.o -o server
server: server.c
	gcc -Wall -c server.c
client: client.o
	gcc client.o -o client
server: client.c
	gcc -Wall -c client.c