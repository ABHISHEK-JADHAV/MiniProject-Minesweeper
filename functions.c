#include<ncurses.h>
#include<time.h>
#include<limits.h>
#include<stdlib.h>
#include<assert.h>
#include"functions.h"





void create_table(int y, int x, int mines, int **game, int firsti, int firstj) {
	int i, j, count, start_x, start_y, temp, *temp_mine;
	temp_mine = (int *)malloc(sizeof(int) * mines);

	srandom(time(0));

	for(i = 0; i < mines; i++) {
		temp = random() % (y * x);
		if((firsti == (temp/x) && firstj == (temp%x)) || (firsti == (temp/x) - 1 && firstj == (temp%x)) || (firsti == (temp/x) - 1 && firstj == (temp%x) - 1)
		|| (firsti == (temp/x) - 1 && firstj == (temp%x) + 1) ||  (firsti == (temp/x)  && firstj == (temp%x) - 1) ||  (firsti == (temp/x) && firstj == (temp%x) + 1)
		||  (firsti == (temp/x) + 1 && firstj == (temp%x) - 1) ||  (firsti == (temp/x) + 1 && firstj == (temp%x)) ||  (firsti == (temp/x) + 1 && firstj == (temp%x) + 1)) {
			i--;
			continue;
		}
		count = 0;
		for(j = 0; j < i; j++) {
			if(temp == temp_mine[j])
				count++;
		}
		if(count == 0) {
			game[temp / x][temp % x] = INT_MIN;
			temp_mine[i] = temp;
		}
		else
			i--;
	}
	for(i = 0; i < y; i++) {
		for(j = 0; j < x; j++) {
			if(game[i][j] == INT_MIN) {
				if(i != 0) {
					if(game[i - 1][j] != INT_MIN)
						game[i - 1][j]++;
					if(j != 0) {
						if(game[i - 1][j - 1] != INT_MIN)
							game[i - 1][j - 1]++;
					}
					if(j != (x - 1)) {
						 if(game[i - 1][j + 1] != INT_MIN)
							game[i - 1][j + 1]++;
					}	
				}
				if(i != (y - 1)) {
					 if(game[i + 1][j] != INT_MIN)
						game[i + 1][j]++;
                                        if(j != 0) {
						 if(game[i + 1][j - 1] != INT_MIN)
							game[i + 1][j - 1]++;
					}
                                        if(j != (x - 1)) {
						 if(game[i + 1][j + 1] != INT_MIN)
                                                	game[i + 1][j + 1]++;
        				}
	                        }
				if(j != 0) {
					 if(game[i][j - 1] != INT_MIN)
                                        	game[i][j - 1]++;
				}
                                if(j != (x - 1)) {
					 if(game[i][j + 1] != INT_MIN)
	                                        game[i][j + 1]++;
				}
			}
		}
	}


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


	mvprintw(max_y - 1, max_x - 17, "- ABHISHEK JADHAV");
	attron(A_BOLD);
	mvprintw(2, max_x / 2 - 14, "SINGLE CLICK - FLAG/UNFLAG");
	mvprintw(3, max_x / 2 - 14, "DOUBLE CLICK - OPEN");
	refresh();
	attroff(A_BOLD);
	return temp;
}	
void flagunflag(int **game, char **states, int  x, int y, int startx) {
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
        attron(A_BOLD);
        attron(COLOR_PAIR(4));
	attroff(A_BOLD);
	refresh();
	if(states[(y - 5)/2][(x - startx)/4] == 'c') {
		states[(y - 5)/2][(x - startx)/4] = 'f';
		flags++;
		if(game[(y - 5)/2][(x - startx)/4] == INT_MIN)
			flagsonmines++;
	}
	else if(states[(y - 5)/2][(x - startx)/4] == 'f') {
		states[(y - 5)/2][(x - startx)/4] = 'c';
		flags--;
		if(game[(y - 5)/2][(x - startx)/4] == INT_MIN)
			flagsonmines--;

	}
	attroff(COLOR_PAIR(4));
}
void openblock(int **game, char **states, int  i, int j, int startx, int maxy, int maxx) {
	if(states[i][j] == 'c' || states[i][j] == 'f') {
        	states[i][j] = 'o';
		open++;
		if(game[i][j] == 0) {
                                if(i != 0) {
                                        if(game[i - 1][j] != INT_MIN)
                                                openblock(game, states, i - 1, j, startx, maxy, maxx);
                                        if(j != 0) {
                                                if(game[i - 1][j - 1] != INT_MIN)
                                                         openblock(game, states, i - 1, j - 1, startx, maxy, maxx);
                                        }
                                        if(j != maxx) {
                                                 if(game[i - 1][j + 1] != INT_MIN)
                                                         openblock(game, states, i - 1, j + 1, startx, maxy, maxx);
                                        }
                                }
                                if(i != maxy) {
                                         if(game[i + 1][j] != INT_MIN)
                                                 openblock(game, states, i + 1, j, startx, maxy, maxx);
                                        if(j != 0) {
                                                 if(game[i + 1][j - 1] != INT_MIN)
                                                         openblock(game, states, i + 1, j - 1, startx, maxy, maxx);
                                        }
                                        if(j != maxx) {
                                                 if(game[i + 1][j + 1] != INT_MIN)
                                                         openblock(game, states, i + 1, j + 1, startx, maxy, maxx);
                                        }
                                }
                                if(j != 0) {
                                         if(game[i][j - 1] != INT_MIN)
                                                 openblock(game, states, i, j - 1, startx, maxy, maxx);
                                }
                                if(j != maxx) {
                                         if(game[i][j + 1] != INT_MIN)
                                                 openblock(game, states, i, j + 1, startx, maxy, maxx);
                                }
		}
	}
		
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

int init(int y, int x, int mines) {
	flagsonmines = 0;
	flags = 0;
	open = 0;
	int **game, ch, temp, k;
	char **states;
	MEVENT event;
	clear();
	refresh();
	 keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	 cbreak();
	int i, j;
	game = (int**)malloc(y*sizeof(int*));
	game[0] = (int *)malloc(y * x * sizeof(int));
	for(i = 0; i < y; i++)
		game[i] = (*game + x * i);
	states = (char**)malloc(x*sizeof(char*));
        states[0] = (char *)malloc(y * x * sizeof(char));
        for(i = 0; i < x; i++)
                states[i] = (*states + x * i);
	for(i = 0; i < y; i++)
		for(j = 0; j < x; j++)
			game[i][j] = 0;
	 for(i = 0; i < y; i++)
                for(j = 0; j < x; j++)
                        states[i][j] = 'c';
	int startx, maxx, maxy, count = 0;
	refresh();
	print_table(y, x, game, states); 
	refresh();

	do {	clear();
		refresh();

		getmaxyx(stdscr, maxy, maxx);
		if(ch == KEY_MOUSE) {
			assert(getmouse(&event) == OK);
			if((event.bstate & BUTTON1_CLICKED) && (event.x > (maxx - x*4)/2) &&
				event.x < (maxx + x*4)/2 && (event.x - (maxx - x*4) / 2) % 4 != 0 && event.y > 5 && 
				event.y < (5 + y*2) && (event.y - 5) % 2 != 0) {
				startx =  (maxx - x*4) / 2;
				i = (event.y - 5)/2;
				j = (event.x - startx)/4;
				if(count == 0) {
					count++;
					create_table(y, x, mines, game, i, j);
				}
				flagunflag(game, states, event.x, event.y, startx);
			}
			if((event.bstate & BUTTON1_DOUBLE_CLICKED) && (event.x > (maxx - x*4)/2) &&
                                event.x < (maxx + x*4)/2 && event.x - (maxx - x*4) / 2 % 4 != 0 && event.y > 5 && 
                                event.y < (5 + y*2) && (event.y - 5 ) % 2 != 0) {
				startx =  (maxx - x*4) / 2;
				i = (event.y - 5)/2;
				j = (event.x - startx)/4;
				if(count == 0) {
					count++;
					create_table(y, x, mines, game, i, j);
				}
				openblock(game, states, i, j, startx, y - 1, x - 1);
                        }
		}
		temp = print_table(y, x, game, states);
		if((flags == flagsonmines && flags == mines) ||
			(open == x*y - mines) ) {

			temp = 2;
			while(1) {
				win();
				if(getch() == 'q')
					break;;
			}
		}
		if(temp == 1) {
			
			while(1) {
				lost();
				
				if(getch() == 'q')
					break;
			}
		}	
	}while(!temp && (ch = getch()) != 'q');

	clear();
	refresh();
	free(states);
	free(game);
	return 0;
}

