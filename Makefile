mines: startpage.o functions.o
	gcc startpage.o functions.o -lncurses -o mines

startpage.o: startpage.c
	gcc startpage.c -c -lncurses

functions.o: functions.c
	gcc functions.c -c -lncurses 
