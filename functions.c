#include<ncurses.h>
#include<time.h>
#include<limits.h>
#include<stdlib.h>
#include<assert.h>
#include"functions.h"


void create_table(int y, int x, int mines, int **game) {
	int i, j, count, start_x, start_y, temp, *temp_mine;
	temp_mine = (int *)malloc(sizeof(int) * mines);

	srandom(time(0));

	for(i = 0; i < mines; i++) {
		temp = random() % (y * x);
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
void print_table(int y, int x, int **game, char **states) {
	int i, j, max_x, max_y;
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
                		else {
                        		mvprintw(6 + i*2, start_x + 1 + j*4, " %d ", game[i][j]);
                        		refresh();
                		}
				attroff(A_REVERSE);
			}
		}	
	}
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
}	
void flagunflag(int **game, char **states, int  x, int y, int startx) {
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
        attron(A_BOLD);
        attron(COLOR_PAIR(4));
	attroff(A_BOLD);
	refresh();
	if(states[(y - 5)/2][(x - startx)/4] == 'c')
		states[(y - 5)/2][(x - startx)/4] = 'f';
	else if(states[(y - 5)/2][(x - startx)/4] == 'f')
		states[(y - 5)/2][(x - startx)/4] = 'c';
	attroff(COLOR_PAIR(4));
}
void openblock(int **game, char **states, int  i, int j, int startx, int maxy, int maxx) {
	if(states[i][j] == 'c' || states[i][j] == 'f') {
        	states[i][j] = 'o';
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
int init(int y, int x, int mines) {
	int **game, ch;
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
	create_table(y, x, mines, game);
	int startx, maxx, maxy;
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
				flagunflag(game, states, event.x, event.y, startx);
			}
			if((event.bstate & BUTTON1_DOUBLE_CLICKED) && (event.x > (maxx - x*4)/2) &&
                                event.x < (maxx + x*4)/2 && event.x - (maxx - x*4) / 2 % 4 != 0 && event.y > 5 && 
                                event.y < (5 + y*2) && (event.y - 5 ) % 2 != 0) {
				startx =  (maxx - x*4) / 2;
				i = (event.y - 5)/2;
				j = (event.x - startx)/4;
				openblock(game, states, i, j, startx, y - 1, x - 1);
                        }
		}
		print_table(y, x, game, states); 
	}while((ch = getch()) != 'q');
	clear();
	refresh();
	free(states);
	free(game);
	return 0;
}

