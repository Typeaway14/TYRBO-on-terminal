#include<stdio.h>
#include"tc.h"
#include"type_content.h"
int termsize(int *rows,int *columns)
{
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        // receives buffer information from the stdoutput ie console
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        // retrieving terminal dimensions
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    // retrieving terminal in linux
    #elif __linux__
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        *columns = (int)(w.ws_col);
        *rows = (int)(w.ws_row);
    #endif
}
// function to fetch coordinates of mouse pointer
void coord_details(int *rows, int* columns, int *x, int *y, int size)
{
    termsize(rows,columns);
    *x=(size>*columns)?0:((*columns-size)/2);
    *y=((*rows/2)>16)?(*rows/2):16;
}
// clearing of instream data in linux
#ifdef __linux__
void clear_instream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
#endif