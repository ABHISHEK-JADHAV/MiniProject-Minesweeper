/*These are the functions used in the game
* Below them, it is their short explanation of what these functions  do.
*/
int flagsonmines, flags, open;
/*To count the flags placed correctly
* And total number of flags placed
* And the total number of boxes opened
*/

int start();
/*Prints and handles the first page of game*/

int init(int, int, int);
/*Initializes and starts the actual game*/

void create_table(int, int, int, int**, int, int);
/*Creates the gamepad (updates the game)*/

int print_table(int, int, int**, char**);
/*Prints Table*/

void flagunflag(int** , char** , int , int , int);
/*To mark or unmark flags*/

void openblock(int**, char**, int, int, int, int, int);
/*To open the blocks*/

void lost();
/*Gets called if you step on a mine*/

void win();
/*Gets called if you win*/

int choice_custom();
/*Custom level*/

int resume();
/*Game resume*/

int resumeinit(int, int, int, int**, char**, int);
/*Resumed game controlling*/
