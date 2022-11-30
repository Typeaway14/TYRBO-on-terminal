#include<stdio.h>
#include"../lib/tc.h"
#include"../lib/type_content.h"
#include <unistd.h>
#include <stdlib.h>
#if defined(__linux__) || defined(__APPLE__)
    #include <termios.h>
#endif

void termsize(int *rows,int *columns)
{
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #elif defined(__linux__) || defined(__APPLE__)
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

void clear_instream()
{
    #if defined(__linux__) || defined(__APPLE__)
        int stdin_copy = dup(STDIN_FILENO);
        /* remove garbage from stdin */
        tcdrain(stdin_copy);
        tcflush(stdin_copy, TCIFLUSH);
        close(stdin_copy);
    #elif _WIN32
        CLEAR_INSTREAM;
    #endif

}

void term_sleep(int duration)
{
    #ifdef _WIN32
        Sleep(duration);
    #elif defined(__linux__) || defined(__APPLE__)
        usleep(duration*1000);
    #endif
}
