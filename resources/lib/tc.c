#include<stdio.h>
#include"tc.h"
#include"type_content.h"
#ifdef __linux__
    #include <termios.h>
    #include<unistd.h>
#endif
#include <unistd.h>
#include <stdlib.h>
int termsize(int *rows,int *columns)
{
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #elif __linux__
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        *columns = (int)(w.ws_col);
        *rows = (int)(w.ws_row);
    #endif
}

void coord_details(int *rows, int* columns, int *x, int *y, int size)
{
    termsize(rows,columns);
    *x=(size>*columns)?0:((*columns-size)/2);
    *y=((*rows/2)>16)?(*rows/2):16;
}

#ifdef __linux__
    void clear_instream()
    {
        int stdin_copy = dup(STDIN_FILENO);
        /* remove garbage from stdin */
        tcdrain(stdin_copy);
        tcflush(stdin_copy, TCIFLUSH);
        close(stdin_copy);
    }
#endif