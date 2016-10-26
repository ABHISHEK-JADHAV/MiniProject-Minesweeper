/*Mini-Project  **MINESWEEPER**
*This game will allow user to select the size of matrix (i.e. thegame pad)
*It will also allow user to select the number of mines in game
*User will have to left double click to open or unflag a block
*Left single click will be used to mark the flags
*/
#include<stdio.h>
#include<ncurses.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include"functions.h"
int main(int argc, char *argv[]) {
	if(argc > 2) {
		perror("INVALID INPUT\n");
		return errno;
	}
	if(argc == 2 && strcmp(argv[1], "-h")) {
		perror("INVALID INPUT\n");
		return errno;
	}

	if(argc == 2 && !strcmp(argv[1], "-h")) {
		printf("\nRun code normally without any extra inputs.\nSimply run the executable file 'mines' using command './mines'\nAfter running the file, there are run time instructions also. But use single click to select from the first menu of the game.\nAt the current stage of code, the custom level will not work.\n\n");
		return 1;
	}
		start();
		return 0;
}
			
