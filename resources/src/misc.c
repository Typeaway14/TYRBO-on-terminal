#include<stdio.h>
#include"../lib/tc.h"
#include"../lib/misc.h"
#include"../lib/type_content.h"
#include"../lib/type_structures.h"
#include"../lib/art.h"
#include<string.h>
#include<time.h>
#include<stdlib.h>
#ifdef _WIN32
    #include<windows.h>
    #include<conio.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include<unistd.h>
    #include <termios.h>

    char getch(void)
    {
        char buf = 0;
        struct termios old = {0};
        fflush(stdout);
        if(tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if(tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if(read(0, &buf, 1) < 0)
            perror("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if(tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");
        return buf;
    }
#endif

void trimTrailing(char * str)
{
    printf("\e[?25l");
    int index, i;
    index = -1;
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }
        i++;
    }
    str[index + 2] = '\0';
}


void caps_check()
{
    int rows=0,columns=0;
    termsize(&rows,&columns);
#ifdef _WIN32
    if (GetKeyState(VK_CAPITAL) & 1)
#endif
#ifdef __linux__
    FILE* p = popen("xset -q | grep \"Caps Lock\" | cut -d\" \" -f10", "r");
    if (!p) {
        printf("INSTALL xset");
    }
    char result[8];
    if (fgets(result, 8, p) == NULL) {
        printf("SOMETHING WENT WRONG. CHECK IF YOU HAVE XSET INSTALLED");
        pclose(p);
        clean_and_exit();
    }
    pclose(p);
    if (result[0] == 'o' && result[1] == 'n')
    {
        TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
        printf("CAPS LOCK IS ON");
    }

    else
    {
        TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
        printf("               ");
    }
#endif
}

int bball_dunk()
{
    FILE *frand;
    frand=fopen("resources/Dunk_words.csv","r");

    srand(time(NULL));
    int r=(rand() % 213)+1;

    char ch[1500];
    if(fgets(ch,1500,frand)==NULL)
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        term_sleep(200);
        clean_and_exit();
    } 

    char* tmp=strtok(ch,",");

    if(!tmp)
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        term_sleep(200);
        clean_and_exit();
    }

    for(int i=0;i<=r-1;i++)
    {
        tmp=strtok(NULL,",");
        if (!tmp)
        {
            TC_CLRSCR();
            printf("Something went wrong..\nReturning back to home page..\n");
            term_sleep(200);
            clean_and_exit();
        }
    }
    TC_CLRSCR();
    art_disp("resources/art/BASKETBALL.txt");
    term_sleep(750);
    fclose(frand);
    return single_type_disp(tmp,5,'z');
}

int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,CHAR_NODE **node,int x,int y,int size,int color)
{
    TC_CLRSCR();
    caps_check();
    fseek(fp,0,SEEK_SET);
    *b=0;
    TC_MOVE_CURSOR(x,y);
    (*node)->color_flag=0;
    if((*node)->exp_char==' ')
    {
        (*node)->exp_char='_';
    }
    string_print(size);
    *streak=0;
    *count+=1;
    return 1;
}

void problem_keys_analysis()
{
    printf("\nProblematic Keys:");
    CH_STK *trav = stk_head;
    while(trav)
    {
        printf(" %c(%d)",trav->data->exp_char,trav->data->occurence);
        trav = trav->next;
    }
}

void score(float time_taken,int count,int size,char gmode,int BBscore)
{
    printf("\e[?25l");
    TC_MOVE_CURSOR(0,0);
    count++;
    float wpm=((size/5)/(time_taken/60));
    float acc=((float)size/(float)count)*100;
    float netwpm=wpm*(acc/100);

    if(gmode!='s')
    {   
        printf("\nTime Taken: %s%.2fs%s\nCharacters: %s%d/%d%s",TC_GRN,time_taken,TC_NRM,TC_GRN,++count,size,TC_NRM);
        printf("\nYour WPM was: %s%.1f%s",TC_GRN,wpm,TC_NRM);
        printf("\nYour net WPM was: %s%.1f%s",TC_GRN,netwpm,TC_NRM);

        if(acc==100.0)
        {
            printf("\nYour accuracy was: %s",TC_CYN);
        }

        else if(acc>=95.0)
        {
            printf("\nYour accuracy was: %s",TC_MAG);
        }

        else if(acc>=90.0 && acc<95.0)
        {
            printf("\nYour accuracy was: %s",TC_GRN);
        }

        else if(acc>=80.0 && acc<90.0)
        {
            printf("\nYour accuracy was: %s",TC_YEL);
        }

        else
        {
            printf("\nYour accuracy was: %s",TC_RED);
        }
        printf("%.1f%c%s",acc,'%',TC_NRM);
    }


    if(gmode=='s')
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("\nTime Taken: %s%.2fs%s\nCharacters: %s%d%s",TC_GRN,time_taken,TC_NRM,TC_GRN,--count,TC_NRM);
    }
    else if(gmode=='b')
    { 
        printf("\nYour Score was: %s%d%s",TC_GRN,BBscore,TC_NRM);
    }
    problem_keys_analysis();
    term_sleep(1500);
    printf("\n%sPress any key to continue%s",TC_YEL,TC_NRM);
    clear_instream();
    getch();
}

void clean_and_exit()
{
    free_structures();
    exit(0);
}
