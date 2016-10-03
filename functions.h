

void create_table(int, int, int, int**);
/*Creates the gamepad (updates the game)*/
void recreate_table();
/*Use for updating */
void mark_unmark_flag(int,int);
/*Marks/Unmarks the right clicked position as potential mine*/
void open_blocks(int, int);
/*This will open the clicked and near by unnecessary blocks*/
int easy();
/*This is for the easy level game with 10 rows and 10 columns with 15 mines*/
void print_table(int, int, int**, char**);
/*Prints Table*/
void flagunflag(int** , char** , int , int , int);
/*To mark or unmark flags*/
void openblock(int**, char**, int, int, int, int, int);
/*To open the blocks*/
