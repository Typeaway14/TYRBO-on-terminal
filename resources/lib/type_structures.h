#ifndef TYPE_STR_H
#define TYPE_STR_H
//structure that holds the node with character value and flag
typedef struct char_dll
{
    char exp_char; //expected_char
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
    char exp_char;//stores the expected character
    // char inp_char;//stores but does nothing in current version of code
    int occurence;//counts expected char
}STK_NODE;

//structure that holds a STK_NODE and pointer to next node
typedef struct char_stack
{
    STK_NODE *data;
    struct char_stack *next;
}CH_STK;


extern TSTRING *tstring_head;
extern CH_STK *stk_head;

void string_push(char*);
void string_pop(TSTRING**);
void string_print(int);
void free_structures();
void free_dll();

//code for stack_imp
void free_stk();
// void stk_push(char,char);
void stk_push(char);
int stk_check(char);
void print_stk();
#endif