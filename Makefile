all: mines

mines: startpage.o functions.o
	gcc startpage.o functions.o -lncurses -o mines

startpage.o: startpage.c functions.h
	gcc startpage.c -c -lncurses

functions.o: functions.c functions.h
	gcc functions.c -c -lncurses 
