main: main.o
	gcc -Wall -c main.c -lrasqal/src -lraptor2/src
	gcc -Wall -o main main.o -L/usr/local/lib  -lrasqal -lraptor2

#main.o: main.c /usr/local/include/rasqal.h
#	gcc -Wall -c main.c -lrasqal/src
#	gcc -Wall -o main main.o -L/usr/local/lib -lrasqal