//header file containing the prototypes for functions that will be used for typing related actions
int type_disp(char* ,int,char); //function to display text to be typed

int type_input(char*,int,char);//function that takes input from user to play the game and tracks the validity of input

void trimTrailing(char * str); //function to trim trailing spaces

void score(float,int,int,char,int);//function to calculate the user score.Parameters:(time_taken,total characters input by user,size of string)

int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,char* p,int x,int y,int color); //function to handle wrong input. returns integer value

void art_disp( char*); //function that opesn text art stored in a file

int bball_dunk(); //function to print BASKETBALL.txt on successful execution

void score_save(int gmode,float *wpm,float *acc,float *netwpm,int BBscore); //saves scores to scorefile

char* rand_string(char* ,int ,char*); //generates a random string

void type_launch(char*,char*,char ); //copies code from the file and copies it to the window being typed on

char rand_mode(); //generates a random game mode

#ifdef _WIN32 //if running a windows system
    void caps_check(); //run this
#elif __linux__ //if running a linux system
    char getch(void); //run this
#endif