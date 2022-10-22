#include<stdio.h>
#include"tc.h" //includes user defined header functions
#include"type_content.h"

int termsize(int *rows,int *columns)
{
    #ifdef _WIN32 //execute if on windows
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        //GetConsoleScreenBufferInfo retrieves information about the specified console screen buffer
        //GetStdHandle retrieves a handle to standard output (here)
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #elif __linux__ //execute if on linux
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        *columns = (int)(w.ws_col);
        *rows = (int)(w.ws_row);
    #endif
}

void coord_details(int *rows, int* columns, int *x, int *y, int size)
{
    termsize(rows,columns);
    *x=(size>*columns)?0:((*columns-size)/2); //usage of ternary operator
    *y=((*rows/2)>16)?(*rows/2):16;
}
#ifdef __linux__
void clear_instream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
#endif