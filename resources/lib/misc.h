#ifndef MISC_H
#define MISC_H

#include"type_structures.h"

void trimTrailing(char * str);
void score(float,int,int,char,int);//function to calculate the user score.Parameters:(time_taken,total characters input by user,size of string)
int bball_dunk();
int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,CHAR_NODE **node,int x,int y,int size,int color);
void score_save(int gmode,float *wpm,float *acc,float *netwpm,int BBscore);
void caps_check();
void problem_keys_analysis();
void clean_and_exit();
#ifdef __linux__
    char getch(void);
#endif
#endif