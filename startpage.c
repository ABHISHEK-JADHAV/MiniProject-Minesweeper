/*Mini-Project  **MINESWEEPER**
*This game will allow user to select the size of matrix (i.e. thegame pad)
*It will also allow user to select the number of mines in game
*User will have to left double click to open or unflag a block
*Left single click will be used to mark the flags
*/
#include<stdio.h>
#include<ncurses.h>
#include<assert.h>
#include"functions.h"
int main() {
	int x, y, j, i, count = 0;
	int ch, exit = 0, start= 0;
	int max_x, max_y;
	MEVENT event;
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	curs_set(0);
	cbreak();
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
	attron(A_BOLD);
	mvprintw(0, 0, "PRESS ANY KEY TO ENTER THE WORLD OF MINESWEEPER!", 1769);

	attroff(A_BOLD);
	refresh();
	while((ch = getch()) != 'q') {
	
		wbkgd(stdscr, COLOR_PAIR(1));
			init_pair(2, COLOR_BLACK, COLOR_BLACK);
		init_pair(3, COLOR_BLACK, COLOR_YELLOW);
		attron(COLOR_PAIR(3));
		getmaxyx(stdscr, max_y, max_x);
		if(ch == KEY_MOUSE) {
	                assert(getmouse(&event) == OK);
			if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) && event.x < (max_x/2 + 5)) && (event.y < 37 && event.y > 33)) {
       		         	endwin();
        	        	return 1;
			}
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) && event.x < (max_x/2 + 5)) && (event.y < 33 && event.y > 29)) {
//			exit = custom();
				if(exit)
				return 1;
			}
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) && event.x < (max_x/2 + 5)) && (event.y < 29 && event.y > 25)) {
	                        exit = init(12, 20, 50);
	                        if(exit)
                                return 1;
	                }
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) && event.x < (max_x/2 + 5)) && (event.y < 25 && event.y > 21)) {
	                        exit = init(12, 15, 30);
	                        if(exit)
                                return 1;
	                }
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) && event.x < (max_x/2 + 5)) && (event.y < 21 && event.y > 17)) {
      	                  exit = init(10, 10, 15);
                	        if(exit)
                                return 1;
	                }
			
	        }
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(2));
		start = 1;
		x = max_x / 2;
		y = 6;
		mvprintw( y++,  x--, " ");
		refresh();
		i = 0;
		while(i++ < 2) {
			mvprintw(y++, x--, " ");
			refresh();
		}
		mvprintw(y--, x, " ");
		refresh();
		i = 0;
		while(i++ < 3) {
			mvprintw(y--, x, " ");
			refresh();
		}
		mvprintw(y, x, " ");
		refresh();
		x -= 3;
		mvprintw(y, x--, " ");
		refresh();
		i = 0;
		while(i++ < 3) {
			mvprintw(y, x--, " ");
			refresh();
		}
		x += 1;
		y += 1;
		i = 0;
		while(i++ < 2) {
			mvprintw(y++, x, " ");
			refresh();
		}
		y -= 1;
		x += 1;
		i = 0;
		while(i++ < 3) {
			mvprintw(y, x++, " ");
			refresh();
		}
		x -= 1;
		y += 1;
		i = 0;
		while(i++ < 2) {
			mvprintw(y++, x, " ");
			refresh();
		}
		i = 0;
		y -= 1;
		x -= 1;
		while(i++ < 3) {
			mvprintw(y, x--, " ");
			refresh();
		}
		x += 11;
		y -= 2;
		i = 0;
		while(i++ < 3) {
			mvprintw(y++, x++, " ");
			refresh();
		}
		i = 0;
		x -= 1;
		y -= 2;
		while(i++ < 4) {
			mvprintw(y--, x, " ");
			refresh();
		}
		y += 1;
		x += 3;
		i = 0;
		while(i++ < 5) {
			mvprintw(y++, x, " ");
			refresh();
		}
		y -= 1;
		x += 1;
		i = 0;
		while(i++ < 3) {
			mvprintw(y, x++, " ");
			refresh();
		}
		i = 0;
		y -= 2;
		x -= 3;
		while(i++ < 2) {
			mvprintw(y, x++, " ");
			refresh();
		}
		i = 0;
		y -= 2;
		x -= 2;
		while(i++ < 3) {
			mvprintw(y, x++, " ");
			refresh();
		}
		x += 2;
		i = 0;
		//E
		while(i++ < 5) {
			mvprintw(y++, x, " ");
			refresh();
		}
		y -= 1;
		x += 1;
		i = 0;
		while(i++ < 3) {
			mvprintw(y, x++, " ");
			refresh();
		}
		i = 0;
		y -= 2;
		x -= 3;
		while(i++ < 2) {
			mvprintw(y, x++, " ");
			refresh();
		}
		i = 0;
		y -= 2;
		x -= 2;
		while(i++ < 3) {
			mvprintw(y, x++, " ");
			refresh();
		}
		//endE
		x += 2;
		i = 0;
		while(i++ < 5) {
			mvprintw(y++, x, " ");
			refresh();
		}
		y -= 3;
		i = 0;
		while(i++ < 4) {
			mvprintw(y, x++, " ");
			refresh();
		}
		x -= 1;
		i = 0;
		while(i++ < 3) {
			mvprintw(y--, x, " "); 
			refresh();
		}
		y += 1;
		i = 0;
		while(i++ < 3) {
			mvprintw(y, x--, " ");
			refresh();
		}
		x += 6;
		i = 0;
		 while(i++ < 5) {
       	         mvprintw(y++, x, " ");
       	         refresh();
       		 }
       		 y -= 1;
       		 x += 1;
       		 i = 0;
	        while(i++ < 3) {
	                mvprintw(y, x++, " ");
	                refresh();
	        }
       		 i = 0;
       		 y -= 2;
       		 x -= 3;
       		 while(i++ < 2) {
	                mvprintw(y, x++, " ");
	                refresh();
	        }
	        i = 0;
	        y -= 2;
	        x -= 2;
	        while(i++ < 3) {
	                mvprintw(y, x++, " ");
       		        refresh();
		}
		x += 2;
		i = 0;
		while(i++ < 5) {
	                mvprintw(y++, x, " ");
	                refresh();
	        }
	        y -= 3;
	        i = 0;
       		 while(i++ < 4) {
       		         mvprintw(y, x++, " ");
        	        refresh();
		}
	        x -= 1;
        	i = 0;
	        while(i++ < 3) {
	                mvprintw(y--, x, " ");
	                refresh();
	        }
	        y += 1;
	        i = 0;
	        while(i++ < 3) {
	                mvprintw(y, x--, " ");
	                refresh();
	        }
		y += 3;
		x += 2;
		i = 0;
		while(i++ < 2) {
			mvprintw(y++, x++, " ");
			refresh();
		}
		x -= 2;
		y -= 1;
		mvprintw(y, x, " ");
		refresh();
		x -= 47;
		y -= 4;
		i = 0;
		while(i++ < 5) {
	                mvprintw(y++, x, " ");
	                refresh();
	        }
	        y -= 1;
	        x += 1;
	        i = 0;
	        while(i++ < 3) {
	                mvprintw(y, x++, " ");
       		         refresh();
       		 }
       		 i = 0;
       		 y -= 2;
	        x -= 3;
	        while(i++ < 2) {
	                mvprintw(y, x++, " ");
	                refresh();
       		 }
	        i = 0;
	        y -= 2;
	        x -= 2;
	        while(i++ < 3) {
     		         mvprintw(y, x++, " ");
	                refresh();
	        }
		x -= 7;
		i = 0;
		while(i++ < 5) {
			mvprintw(y++, x, " ");
			refresh();
		}
		y -= 2;
		x -= 1;
		i = 0;
		while(i++ < 4) {
			mvprintw(y--, x--, " ");
			refresh();
		}
		x += 1;
		y += 2;
		i = 0;
		while(i++ < 4) {
			mvprintw(y++, x, " ");
			refresh();
		}
		y -= 1;
		x -= 3;
		i = 0;
		while(i++ < 5) {
			mvprintw(y, x--, " ");
			refresh();
		}
		x += 3;
		i = 0;
		while(i++ < 4) {
			mvprintw(y--, x, " ");
			refresh();
		}
		x += 2;
		i = 0;
		while(i++ < 5) {
			mvprintw(y, x--, " ");
			refresh();
		}
		x -= 2;
		y += 4;
		i = 0;
		while(i++ < 6) {
			mvprintw(y--, x, " ");
			refresh();
		}
		y += 2;
		x -= 1;
		i = 0;
		while(i++ < 2) {
			mvprintw(y++, x--, " ");
			refresh();
		}
		y -= 2;
		i = 0;
		while(i++ < 2) {
			mvprintw(y--, x--, " ");
			refresh();
		}
		x += 1;
		y += 1;
		i = 0;
		while(i++ < 6) {
			mvprintw(y++, x, " ");
			refresh();
		}
		x--;
		
		attroff(COLOR_PAIR(2));
		//SELECT LEVEL
		attron(A_BOLD);
		attron(COLOR_PAIR(3));
	//	attron(A_REVERSE);
		mvprintw(15, (max_x/2 - 10), "SELECT DIFFICULTY LEVEL");
		mvprintw(19, (max_x/2 - 2), "EASY");
		mvprintw(23, (max_x/2 - 3), "MEDIUM");
		mvprintw(27, (max_x/2 - 2), "HARD");
		mvprintw(31, (max_x/2 - 3), "CUSTOM");
		mvprintw(35, (max_x/2 - 2), "EXIT");
		mvprintw(max_y - 1, max_x - 17, "- ABHISHEK JADHAV");
	//	attroff(A_REVERSE);
		attroff(COLOR_PAIR(3));
		attron(COLOR_PAIR(2));
		i = 0;
		x = max_x/2 - 5;
		y = 17;
		while(i++ < 10)
			mvprintw(y, x++, " ");
		refresh();
		i = 0;
		y = 21;
		x = max_x/2 - 5;
		while(i++ < 10)
			mvprintw(y, x++, " ");
		refresh();
		i = 0;
	        y = 25;
	        x = max_x/2 - 5;
       		 while(i++ < 10)
       	         mvprintw(y, x++, " ");
		refresh();
		i = 0;
	        y = 29;
	        x = max_x/2 - 5;
	        while(i++ < 10)
	                mvprintw(y, x++, " ");
		refresh();
		i = 0;
	        y = 33;
	        x = max_x/2 - 5;
	        while(i++ < 10)
	                mvprintw(y, x++, " ");
		refresh();
		i = 0;
	        y = 37;
	        x = max_x/2 - 5;
	        while(i++ < 10)
	                mvprintw(y, x++, " ");
		
		y = 17;
		x = max_x/2 - 5;
		while(y < 38)
			mvprintw(y++, x, " ");
		y = 17;
       		 x = max_x/2 + 5;
       		 while(y < 38)
                mvprintw(y++, x, " ");
		refresh();
	//	easy = newwin(3, 8, 18, max_x - 4);
	//	box(easy, 0, 0);
		refresh();
		attroff(COLOR_PAIR(2));
		attroff(A_BOLD);	
		
	}
	
		endwin();
		return 0;
}
			
