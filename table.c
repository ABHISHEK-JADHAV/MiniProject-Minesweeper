/*table.c
	Copyright (C) 2016  ABHISHEK JADHAV
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include<ncurses.h>
#include<time.h>
#include<limits.h>
#include<stdlib.h>
#include<assert.h>
#include"functions.h"
int resume() {
	int ifres = 0, temp = 0;
	int ch = 1, maxx, maxy;
	FILE *resf;
	resf = fopen("resumedata.txt", "r");
	
	attron(A_BOLD);
	if(resf == NULL || ((fscanf(resf, "%d", &ifres) == -1) && (temp = 1))){
		while(ch != 'q' && ch != 'Q') {
			clear();
			refresh();
			getmaxyx(stdscr, maxy, maxx);
			mvprintw(maxy/2 - 2, maxx/2 - 15, "SORRY, NO PREVIOUS GAME SAVED!");
			mvprintw(maxy/2, maxx/2 - 10, "PRESS 'q' TO GO BACK!");
			refresh();
			ch = getch();
		}
		if(temp)
			fclose(resf);
		attroff(A_BOLD);
		clear();
		refresh();
		return 0;
	}
	fclose(resf);
	clear();
	refresh();
	resf = fopen("resumedata.txt", "r");
	int i, j, y, x, mines, count;
	fread(&count, sizeof(int), 1, resf);
	fread(&y, sizeof(int), 1, resf);
	fread(&x, sizeof(int), 1, resf);
	fread(&mines, sizeof(int), 1, resf);
	refresh();
	int **game;
	char **states;
	game = (int**)malloc(y*sizeof(int*));
	game[0] = (int *)malloc(y * x * sizeof(int));
	for(i = 0; i < y; i++)
		game[i] = (*game + x * i);
	states = (char**)malloc(y*sizeof(char*));
        states[0] = (char *)malloc(y * x * sizeof(char));
        for(i = 0; i < y; i++)
                states[i] = (*states + x * i);
	for(i = 0; i < y; i++) {
		for(j = 0; j < x; j++) {
			fread(&game[i][j], sizeof(int), 1, resf);
			fread(&states[i][j], sizeof(char), 1, resf);
		}
	}
	refresh();
	fread(&flags, sizeof(int), 1, resf);
	fread(&flagsonmines, sizeof(int), 1, resf);
	fread(&open, sizeof(int), 1, resf);
	refresh();
	resumeinit(y, x, mines, game, states, count);
	fclose(resf);
	return 0;
}
	
int resumeinit(int y, int x, int mines, int **game, char **states, int count) {
	FILE *resf;
	MEVENT event;
	clear();
	refresh();
	 keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	 cbreak();
	int i, j, ch, temp;
	int startx, maxx, maxy;
	refresh();
	print_table(y, x, game, states); 
	refresh();
	getmaxyx(stdscr, maxy, maxx);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	resf = fopen("resumedata.txt", "w");
	fclose(resf);
	
	do {	
		resf = fopen("resumedata.txt", "w");
		
		clear();
		refresh();
		attron(A_BOLD);
		attron(COLOR_PAIR(3));
		mvprintw(0, maxx/2 - 9, "Number of mines = %d", mines);
		attroff(COLOR_PAIR(3));
		attroff(A_BOLD);
		getmaxyx(stdscr, maxy, maxx);
		if(ch == KEY_MOUSE) {
			assert(getmouse(&event) == OK);
			if((event.bstate & BUTTON1_CLICKED || event.bstate & BUTTON1_PRESSED) && (event.x > (maxx - x*4)/2) &&
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
		fwrite(&count, sizeof(int), 1, resf);
		fwrite(&y, sizeof(int), 1, resf);
		fwrite(&x, sizeof(int), 1, resf);
		fwrite(&mines, sizeof(int), 1, resf);
		for(i = 0; i < y; i++) {
			for(j = 0; j < x; j++) {
				fwrite(&game[i][j], 1, sizeof(int), resf);
				fwrite(&states[i][j], 1, sizeof(char), resf);
			}
		}
		fwrite(&flags, sizeof(int), 1, resf);
		fwrite(&flagsonmines, sizeof(int), 1, resf);
		fwrite(&open, sizeof(int), 1, resf);
		fclose(resf);
		if(temp == 1) {
			resf = fopen("resumedata.txt", "w");
			fclose(resf);
			while(1) {
				lost();
				
				if(getch() == 'q')
					break;
			}
		}	
		if((flags == flagsonmines && flags == mines) ||
			(open == x*y - mines) ) {
			resf = fopen("resumedata.txt", "w");
			fclose(resf);
			temp = 2;
			while(1) {
				win();
				if(getch() == 'q')
					break;;
			}
		}
	}while(!temp && (ch = getch()) != 'q');

	clear();
	refresh();
	free(states);
	free(game);
	return 0;
}
void create_table(int y, int x, int mines, int **game, int firsti, int firstj) {
	int i, j, count, start_x, start_y, temp, *temp_mine;
	temp_mine = (int *)malloc(sizeof(int) * mines);

	srandom(time(0));

	for(i = 0; i < mines; i++) {
		temp = random() % (y * x);
		if((firsti == (temp/x) && firstj == (temp%x)) 
		|| (firsti == (temp/x) - 1 && firstj == (temp%x)) 
		|| (firsti == (temp/x) - 1 && firstj == (temp%x) - 1)
		|| (firsti == (temp/x) - 1 && firstj == (temp%x) + 1) 
		||  (firsti == (temp/x)  && firstj == (temp%x) - 1) 
		||  (firsti == (temp/x) && firstj == (temp%x) + 1)
		||  (firsti == (temp/x) + 1 && firstj == (temp%x) - 1) 
		||  (firsti == (temp/x) + 1 && firstj == (temp%x)) 
		||  (firsti == (temp/x) + 1 && firstj == (temp%x) + 1)) {
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
	
int init(int y, int x, int mines) {
	FILE *resf;
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
	for(i = 0; i < y; i++)
		game[i] = (int*)malloc(x*sizeof(int));
	states = (char**)malloc(y*sizeof(char*));
	for(i = 0; i < y; i++)
		states[i] = (char*)malloc(x*sizeof(int));
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
	getmaxyx(stdscr, maxy, maxx);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	do {	
		resf = fopen("resumedata.txt", "w");
		
		clear();
		refresh();
		attron(A_BOLD);
		attron(COLOR_PAIR(3));
		mvprintw(0, maxx/2 - 9, "Number of mines = %d", mines);
		attroff(COLOR_PAIR(3));
		attroff(A_BOLD);
		getmaxyx(stdscr, maxy, maxx);
		if(ch == KEY_MOUSE) {
			assert(getmouse(&event) == OK);
			if((event.bstate & BUTTON1_CLICKED || event.bstate & BUTTON1_PRESSED) && (event.x > (maxx - x*4)/2) &&
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
		fwrite(&count, sizeof(int), 1, resf);
	
		fwrite(&y, sizeof(int), 1, resf);
		fwrite(&x, sizeof(int), 1, resf);
		fwrite(&mines, sizeof(int), 1, resf);
		for(i = 0; i < y; i++) {
			for(j = 0; j < x; j++) {
				fwrite(&game[i][j], sizeof(int), 1, resf);
				fwrite(&states[i][j], sizeof(char), 1, resf);
			}
		}
		fwrite(&flags, sizeof(int), 1, resf);
		fwrite(&flagsonmines, sizeof(int), 1, resf);
		fwrite(&open, sizeof(int), 1, resf);
		fclose(resf);
		if(temp == 1) {
			resf = fopen("resumedata.txt", "w");
			fclose(resf);
			while(1) {
				lost();
				
				if(getch() == 'q')
					break;
			}
		}	
		if((flags == flagsonmines && flags == mines) ||
			(open == x*y - mines) ) {
			resf = fopen("resumedata.txt", "w");
			fclose(resf);
			temp = 2;
			while(1) {
				win();
				if(getch() == 'q')
					break;;
			}
		}
	}while(!temp && (ch = getch()) != 'q');

	clear();
	refresh();
	free(states);
	free(game);
	return 0;
}

