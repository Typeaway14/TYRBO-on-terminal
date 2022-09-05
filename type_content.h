//header file that contains the prototypes for functions that will be used for typing related actions
void print_menu();//function to print the Landing Page
int menu_type(const char *p);//function to print information on terminal in a typing like simulation
void menu_del(int);//function to clear information from terminal in a typing like simulation(as though using backspace)
int menu_input(int);/*function that prints the various menus to be used throughout the program. Different codes passed to this
function implies different menus to be printed:
1)Login/Signup Page*/
int type_disp(char* ,int,char);//function to display text to be typed.Parameters:(string,size of string)
int type_input(char*,int,char);//function that takes input from user to play the game and tracks right and wrong inputs.Parameters:(string,size of string,rows,columns)
void trimTrailing(char * str);
void score(float,int,int,char,int);//function to calculate the user score.Parameters:(time_taken,total characters input by user,size of string)
int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,char* p,int x,int y,int color);
void art_disp( char*);
int bball_dunk();
void score_save(int gmode,float *wpm,float *acc,float *netwpm,int BBscore);
#ifdef _WIN32
    void caps_check();
#elif __linux__
    char getch(void);
#endif