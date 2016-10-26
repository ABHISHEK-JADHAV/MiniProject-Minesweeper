all: project

project: main.o graphics.o table.o
	gcc main.o graphics.o table.o -lncurses -o project

main.o: main.c functions.h
	gcc main.c -c -lncurses

graphics.o: graphics.c functions.h
	gcc graphics.c -c -lncurses

table.o: table.c functions.h
	gcc table.c -c -lncurses
