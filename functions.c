#include<ncurses.h>
#include<time.h>
#include<limits.h>
#include<stdlib.h>
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
	attron(A_BOLD);
	attron(COLOR_PAIR(3));
	mvprintw(max_y - 1, max_x - 17, "- ABHISHEK JADHAV");
	attroff(COLOR_PAIR(3));
	attroff(A_BOLD);		
}	

int init(int y, int x, int mines) {
	int **game;
	char **states;
	clear();
	refresh();

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

	refresh();
	do {	clear();
		refresh();
		print_table(y, x, game, states); 
	}while(getch() != 'q');
	clear();
	refresh();
	free(states);
	free(game);
	return 0;
}

