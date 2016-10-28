#include<ncurses.h>
#include<time.h>
#include<limits.h>
#include<stdlib.h>
#include<assert.h>
#include"functions.h"



int start() {
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
			if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) 
				&& event.x < (max_x/2 + 5)) && (event.y < 41 && event.y > 37)) {
       		         	endwin();
        	        	return 1;
			}
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) 
				&& event.x < (max_x/2 + 5)) && (event.y < 37 && event.y > 33)) {
			exit = choice_custom();
				if(exit)
				return 1;
			}
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) 
				&& event.x < (max_x/2 + 5)) && (event.y < 33 && event.y > 29)) {
	                        exit = init(12, 20, 50);
	                        if(exit)
                                return 1;
	                }
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) 
				&& event.x < (max_x/2 + 5)) && (event.y < 29 && event.y > 25)) {
	                        exit = init(12, 15, 30);
	                        if(exit)
                                return 1;
	                }
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) 
				&& event.x < (max_x/2 + 5)) && (event.y < 25 && event.y > 21)) {
      	                  	exit = init(10, 10, 15);
                	        if(exit)
                                return 1;
	                }
			else  if(start && (event.bstate & BUTTON1_CLICKED) && (event.x > (max_x/2 - 5) 
				&& event.x < (max_x/2 + 5)) && (event.y < 21 && event.y > 17)) {
      	                  	exit = resume();
                	        if(exit)
                                return 1;
	                }
	        }
		getmaxyx(stdscr, max_y, max_x);
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
		
		attron(A_BOLD);
		attron(COLOR_PAIR(3));

		mvprintw(15, (max_x/2 - 10), "SELECT DIFFICULTY LEVEL");
		mvprintw(19, (max_x/2 - 3), "RESUME");
		mvprintw(23, (max_x/2 - 2), "EASY");
		mvprintw(27, (max_x/2 - 3), "MEDIUM");
		mvprintw(31, (max_x/2 - 2), "HARD");
		mvprintw(35, (max_x/2 - 3), "CUSTOM");
		mvprintw(39, (max_x/2 - 2), "EXIT");
		mvprintw(max_y - 1, max_x - 17, "- ABHISHEK JADHAV");
	
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
		
		i = 0;
		y = 41;
		x = max_x/2 - 5;
		while(i++ < 10)
			mvprintw(y, x++, " ");
		y = 17;
		x = max_x/2 - 5;
		while(y < 42)
			mvprintw(y++, x, " ");
		y = 17;
       		 x = max_x/2 + 5;
       		 while(y < 42)
                mvprintw(y++, x, " ");
		refresh();
		attroff(COLOR_PAIR(2));
		attroff(A_BOLD);	
		
	}
	
		endwin();
}

int print_table(int y, int x, int **game, char **states) {
	
	int i, j, max_x, max_y, temp = 0;
	getmaxyx(stdscr, max_y, max_x);
	for(i = 0; i < y; i++){
		for(j = 0; j < x; j++) {
			if(game[i][j] == INT_MIN) {
				mvprintw(i, j, "*");
			}
			else
				mvprintw(i, j, "%d", game[i][j]);
			mvprintw(i + 20, j, "%c", states[i][j]);
		}
	}
	int start_x, start_y, tempx, tempy;
	start_x = max_x/2 - (x*4)/2;
	start_y = 5;
	i = 0;
	j = 0;
	tempx = start_x;
	tempy = start_y;
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	while(i < x + 1) {
		while(j < 2*y + 1) {
			mvprintw(tempy++, tempx, " ");
			j++;
		}
		tempy = start_y;
		tempx += 4;
		i++;
		j = 0;
	}
	tempx = start_x;
	tempy = start_y;
	i = 0;
	j = 0;
	while(i < y + 1) {
		while(j < 4*x + 1) {
			mvprintw(tempy, tempx++, " ");
			j++;
		}
		tempx = start_x;
		tempy += 2;
		j = 0;
		i++;
	}
	attroff(COLOR_PAIR(2));
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);

	attron(COLOR_PAIR(3));
	
	for(i = 0; i < y; i++) {
		for(j = 0; j < x; j++) {
			if(states[i][j] == 'f')
				mvprintw(start_y + 1 + i*2, start_x + 2 + 4*j, "f");
			else if(states[i][j] == 'o') { 
				attron(A_REVERSE);
                		if(game[i][j] == 0) {
                        		mvprintw(6 + i*2, start_x + 1 + j*4, "   ");
                        		refresh();
                		}
				else if(game[i][j] == INT_MIN) {
					mvprintw(6 + i*2, start_x + 1 + j*4, " * ");
					refresh();
					temp = 1;
				}
                		else {
                        		mvprintw(6 + i*2, start_x + 1 + j*4, " %d ", game[i][j]);
                        		refresh();
                		}
				attroff(A_REVERSE);
			}
		}	
	}
//	The commented part is written for debugging purpose.
/*
	mvprintw(16, 0, "This is just for testing some cases");
	mvprintw(17, 0, "like first click will always be a zero.");
	for(i = 0; i < y; i++){
                for(j = 0; j < x; j++) {
                        if(game[i][j] == INT_MIN) {
                                mvprintw(i, j, "*");
                        }
                        else
                                mvprintw(i, j, "%d", game[i][j]);
                        mvprintw(i + 20, j, "%c", states[i][j]);
                }
        }

*/
	mvprintw(max_y - 1, max_x - 17, "- ABHISHEK JADHAV");
	attron(A_BOLD);
	mvprintw(2, max_x / 2 - 14, "SINGLE CLICK - FLAG/UNFLAG");
	mvprintw(3, max_x / 2 - 14, "DOUBLE CLICK - OPEN");
	refresh();
	attroff(A_BOLD);
	return temp;
}
int choice_custom() {
	clear();
	refresh();
	int maxy, maxx, i, y, x, ch, count = 0, ROWS, COLS, MINES;
	char rows[4] = {' ', ' ', ' ', ' '}, cols[4] = {' ', ' ', ' ', ' '}, mines[4] = {' ', ' ', ' ', ' '};
	
	int select = 0, rready = 0, cready = 0, mready = 0;
	MEVENT event;
	ch = 1;
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	attron(COLOR_PAIR(5)); 
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	cbreak();
	attron(A_BOLD);
	while(ch != 'q' && ch != 'Q') {
		clear();
		refresh();
		getmaxyx(stdscr, maxy, maxx);
		mvprintw(3, maxx/2 - 11, "Press 'q' to go back!!");
		mvprintw(5, maxx/2 - 9, "ENTER YOUR CHOICES !");
		mvprintw(7, maxx/2 - 16, "Press 'ENTER' after every entry!");

		mvprintw(10, maxx/2 - 30, "Number of rows (5 to 20)");
		attron(A_REVERSE);
		mvprintw(10, maxx/2 + 1, " ");
		i = 0;
		y = 9;
		x = maxx/2 + 1;
		while(i++ < 6)
			mvprintw(y, x++, " ");
		i = 0;
		y = 11;
		x = maxx/2 + 1;
		while(i++ < 6)
			mvprintw(y, x++, " ");
		mvprintw(10, maxx/2 + 6, " ");
		attroff(A_REVERSE);
		
		init_pair(6, COLOR_BLACK, COLOR_WHITE);
		attroff(COLOR_PAIR(5));
		attron(COLOR_PAIR(6));
		x = maxx/2 + 2;
		y = 10;
		for(i = 0; i < 4; i++)
			mvprintw(y, x++, "%c",rows[i]);
		x = maxx/2 + 2;
		y = 13;
		for(i = 0; i < 4; i++)
			mvprintw(y, x++, "%c", cols[i]);
		x = maxx/2 + 2;
		y = 16;
		for(i = 0; i < 4; i++)
			mvprintw(y, x++, "%c", mines[i]);
		attroff(COLOR_PAIR(6));
		attron(COLOR_PAIR(5));
	
		mvprintw(13, maxx/2 - 30, "Number of columns (5 to 20)");
		attron(A_REVERSE);
		mvprintw(13, maxx/2 + 1, " ");
		i = 0;
		y = 12;
		x = maxx/2 + 1;
		while(i++ < 6)
			mvprintw(y, x++, " ");
		i = 0;
		y = 14;
		x = maxx/2 + 1;
		while(i++ < 6)
			mvprintw(y, x++, " ");
		mvprintw(13, maxx/2 + 6, " ");
		attroff(A_REVERSE);
		mvprintw(16, maxx/2 - 30, "Number of mines");
		attron(A_REVERSE);
		mvprintw(16, maxx/2 + 1, " ");
		i = 0;
		y = 15;
		x = maxx/2 + 1;
		while(i++ < 6)
			mvprintw(y, x++, " ");
		i = 0;
		y = 17;
		x = maxx/2 + 1;
		while(i++ < 6)
			mvprintw(y, x++, " ");
		mvprintw(16, maxx/2 + 6, " ");
		attroff(A_REVERSE);
		refresh();
		ch = getch();
		if(ch == KEY_MOUSE) {
			assert(getmouse(&event) == OK);
			if(((event.bstate & BUTTON1_CLICKED) || (event.bstate & BUTTON1_DOUBLE_CLICKED) || (event.bstate && BUTTON1_PRESSED)) && (event.x > (maxx/2 + 1)) &&
				(event.x < (maxx/2 + 6)) && ((event.y == 10 && (select = 1)) || (event.y == 13 && (select = 2)) || (event.y == 16 && (select = 3)))) {
					move(event.y, maxx/2 + 3);

					attroff(COLOR_PAIR(5));
					attron(COLOR_PAIR(6));
					if(select == 1) {
						ROWS = 0;
						while((ch = getch()) != 10 && (ch != KEY_MOUSE )) {
							
							if(ch >= '0' && ch <= '9') {
								rows[count + 1] = ch;
								ROWS = ROWS*10 + ch - '0';
								count++;
								printw("%c", ch);
								refresh();
								if(count == 2)
									break;
							}		
						}
						if(ROWS > 20 || ROWS < 5) {
							rows[1] = ' ';
							rows[2] = ' ';
							rready = 0;
						}
						else
							rready = 1;
						count = 0;
					}
				
					else if(select == 2) {	
						COLS = 0;
						while((ch = getch()) != 10 && (ch != KEY_MOUSE )) {
							
							if(ch >= '0' && ch <= '9') {
								cols[count + 1] = ch;
								COLS = COLS*10 + ch - '0';
								count++;
								printw("%c", ch);
								refresh();
								if(count == 2)
									break;
							}
						}
						if(COLS > 20 || COLS < 5) {
							cols[1] = ' ';
							cols[2] = ' ';
							cready = 0;
						}
						else
							cready = 1;
						count = 0;
					}
					else if(select == 3) {
						MINES = 0;
						move(event.y, maxx/2 + 2);
						while((ch = getch()) != 10 && (ch != KEY_MOUSE )) {
							
							if(ch >= '0' && ch <= '9') {
								mines[count] = ch;
								MINES = MINES*10 + ch - '0';
								count++;
								printw("%c", ch);
								refresh();
								if(count == 3)
									break;
							}
						}
						if(MINES > (ROWS*COLS - 9) || MINES == 0) {
							mines[0] = ' ';
							mines[1] = ' ';
							mines[2] = ' ';
							mready = 0;
						}
						else
							mready = 1;
						count = 0;
					}
					if(rready && cready && mready) {
						init(ROWS, COLS, MINES);
						return 0;
					}

					refresh();
					attroff(COLOR_PAIR(6));
					attron(COLOR_PAIR(5));
			}
		}
		attroff(A_REVERSE);
	}
	attroff(A_BOLD);
	attroff(COLOR_PAIR(5));
	clear();
	refresh();
	return 0;
}	
void lost() {
	int y, x, i, j, k;
	
	getmaxyx(stdscr, y, x);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	attron(COLOR_PAIR(4));
	k = 0;
	i = 2;
	j = x/2 - 14;
	while(k++ < 28)
		mvprintw(i, j++, " ");
	k = 0;
	i = 3;
	j = x/2 - 14;	
	while(k++ < 28)
		mvprintw(i, j++, " ");
	refresh();
	mvprintw(2, x/2 - 5, "YOU LOST!!");
	mvprintw(3, x/2 - 11, "PRESS 'q' to go back!");
	refresh();
	attroff(COLOR_PAIR(4));
}
void win() {
	int y, x, i, j, k;
	getmaxyx(stdscr, y, x);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	attron(COLOR_PAIR(4));
	k = 0;
	i = 2;
	j = x/2 - 14;
	while(k++ < 28)
		mvprintw(i, j++, " ");
	k = 0;
	i = 3;
	j = x/2 - 14;	
	while(k++ < 28)
		mvprintw(i, j++, " ");
	refresh();
	mvprintw(2, x/2 - 5, "YOU WON!!!");
	mvprintw(3, x/2 - 11, "PRESS 'q' to go back!");
	refresh();

	attroff(COLOR_PAIR(4));
}

