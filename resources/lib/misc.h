#ifndef MISC_H
#define MISC_H

#include"type_structures.h"

void trimTrailing(char * str);
int bball_dunk();
int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,CHAR_NODE **node,int x,int y,int size,int color);
void score_save(int gmode,float *wpm,float *acc,float *netwpm,int BBscore);
void score(float time_taken,int count,int size,char gmode,int BBscore);
void caps_check();
void problem_keys_analysis();
void clean_and_exit();
#if defined(__linux__) || defined(__APPLE__)
    char getch(void);
#endif
#endif
