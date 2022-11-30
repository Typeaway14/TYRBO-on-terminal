#ifndef TYPE_STR_H
#define TYPE_STR_H

typedef struct char_dll
{
    char exp_char;
    int color_flag;
}CHAR_NODE;

typedef struct test_string
{
    struct test_string *prev;
    CHAR_NODE *data;
    struct test_string *next;
}TSTRING;

typedef struct stack_node
{
    char exp_char;
    int occurence;
}STK_NODE;

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
void free_dll();

void stk_push(char);
int stk_check(char);
void print_stk();
void free_stk();

void free_structures();
#endif
