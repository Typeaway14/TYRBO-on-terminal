#ifndef TYPE_CONT_H
#define TYPE_CONT_H
//header file that contains the prototypes for functions that will be used for typing related actions

int single_type_disp(char* ,int,char);//function to display text to be typed.Parameters:(string,size of string)
int single_type_input(char*,int,char);
int type_input(int,char);//function that takes input from user to play the game and tracks right and wrong inputs.Parameters:(string,size of string,rows,columns)
void trimTrailing(char * str);
void score(float,int,int,char,int);//function to calculate the user score.Parameters:(time_taken,total characters input by user,size of string)

void art_disp(char*);
int bball_dunk();
void score_save(int gmode,float *wpm,float *acc,float *netwpm,int BBscore);
char* rand_string(char* ,int ,char*);
void type_launch(char*,char*,char );
char rand_mode();
char* get_color_code();
void change_color_code(char);

#ifdef _WIN32
    void caps_check();
#elif __linux__
    char getch(void);
#endif

//code for dll_imp
int type_disp(int,char);//function to display text to be typed.Parameters:(string,size of string)
void problem_keys_analysis();
#endif