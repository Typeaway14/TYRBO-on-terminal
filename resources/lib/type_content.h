//header file that contains the prototypes for functions that will be used for typing related actions

//structure that holds the node with character value and flag
typedef struct char_dll
{
    char inp_char; //input_char
    int color_flag;
}CHAR_NODE;

//structure that holds a CHAR_NODE and pointers to other nodes
typedef struct test_string
{
    struct test_string *prev;
    CHAR_NODE *data;
    struct test_string *next;
}TSTRING;

//structure that holds the node for stacks
typedef struct stack_node
{
    char inp_char;
    int occurence;
}STK_NODE;

//structure that holds a STK_NODE and pointer to next node
typedef struct char_stack
{
    STK_NODE *data;
    struct char_stack *next;
}CH_STK;

int single_type_disp(char* ,int,char);//function to display text to be typed.Parameters:(string,size of string)
int single_type_input(char*,int,char);
int type_input(int,char);//function that takes input from user to play the game and tracks right and wrong inputs.Parameters:(string,size of string,rows,columns)
void trimTrailing(char * str);
void score(float,int,int,char,int);//function to calculate the user score.Parameters:(time_taken,total characters input by user,size of string)
int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,CHAR_NODE **node,int x,int y,int size,int color);
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
void string_push(char*);
void string_pop(TSTRING**);
void string_print(int);
void free_structures();
void free_dll();

//code for stack_imp
void free_stk();
void stk_push(char);
int stk_check(char);
void print_stk();
