#ifndef TC_M
#define TC_M
#ifdef _WIN32
    #include<windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include<sys/ioctl.h>
#endif
void termsize(int *rows,int *columns);
void coord_details(int *rows, int* columns,int *x,int *y,int size);
void term_sleep(int);
void clear_instream();

#define TC_NRM "\x1B[0m"
#define TC_RED "\x1B[1;31m"
#define TC_GRN "\x1B[1;32m"
#define TC_YEL "\x1B[1;33m"
#define TC_BLU "\x1B[1;34m"
#define TC_MAG "\x1B[1;35m"
#define TC_CYN "\x1B[1;36m"
#define TC_WHT "\x1B[1;37m"

#define TC_B_NRM "\x1B[0m"
#define TC_B_RED "\x1B[0;31m"
#define TC_B_GRN "\x1B[0;31m"
#define TC_B_YEL "\x1B[0;31m"
#define TC_B_BLU "\x1B[0;31m"
#define TC_B_MAG "\x1B[0;31m"
#define TC_B_CYN "\x1B[0;31m"

#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED "\x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1B[47m"

#define TC_CLRSCR() puts("\x1B[2J")
#define TC_MOVE_CURSOR(X,Y) printf("\033[%d;%dH",Y,X)
#ifdef _WIN32
    #define CLEAR_INSTREAM FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE))
#endif
#endif
