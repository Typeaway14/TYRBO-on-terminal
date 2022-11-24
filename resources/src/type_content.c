//This file contains the definitions of the functions defined in type_content.h
//Typing related functions can be found here
//For further details about a particular function, refer to documentation in respective header files.
#include<stdio.h>
#ifdef _WIN32
    #include<windows.h>//includes windows.h that contains functions like Sleep()
    #include<conio.h>//includes conio.h that contains functions like getch()
// #elif __linux__
//     #include<sys/ioctl.h>
//     #include<unistd.h>//usleep()
//     #include <termios.h>
#endif
#include<string.h> //includes string.h that contains string manipulation functions like strcmp() strlen()
#include<time.h>
#include<stdlib.h>
#include"../lib/type_structures.h"
#include"../lib/type_content.h"//includes the user defined type_content.h header file
#include"../lib/tc.h"
#include"../lib/art.h"
#include"../lib/misc.h"
// SCORE scores[100];

void caps_check();
int score_n;
FILE *score_fp;

//Function to return random strings from a file
//with the number of lines of the file as a parameter
char* rand_string(char* fname,int charno,char* sent)
{
    //Opening the file in read form
    FILE *fp=fopen(fname,"r");

    //Display that Openeing of the file failed if the file has NULL content
    if(fp==NULL)
    {
        printf("failed");
    }

    //Opening the file in read form to count the number of lines
    FILE *fpcount=fopen(fname,"r");

    //int variable to count number of lines 
    int lines=0;

    //Loop to count number of lines
    for(;fgets(sent,300,fpcount);)
    {
        //Incrementing number of lines
        lines++;
    }

    //seeds the random number generator used by the function rand with 
    //seed as time(NULL) returns the integer value to be used as seed
    srand(time(NULL));

    //int variable r to store random variable in an iteration
    int r=0;

    //Loop to iterate until r is greater than 0
    while(!(r>0))
    {
        //r is assigned to a random number from 0 to number of lines in fpcount 
        r=rand() % lines;
    }

    //Loop to iterate until fp's contents are not all read and
    //Iteration count is lesser than the random variable
    for(int i=0;fp!=NULL && i<r;i++)
    {
        fgets(sent,charno,fp);
    }

    //closing file fp
    fclose(fp);

    //Returning the random strings
    return sent;
}
//Function to return a character based on a random parameter
//ranging from 0 to 3
char rand_mode()
{
    //seeds the random number generator used by the function rand with 
    //seed as time(NULL) returns the integer value to be used as seed    
    srand(time(NULL));

    //int variable r to store random variable in an iteration
    int r=0;

    //Loop to iterate until r is greater than 0
    while(!(r>0))
    {
        //r is assigned to a random number from 0 to 3 of lines in fpcount 
        r=rand() % 3;
    }

    //Conditional statement to return character based on random number from 0-3
    switch(r)
    {
        case 1:
            return 'n';
        case 2:
            return 's';
        case 3:
            return 'b';
        default:
            return 'n';
    }
}

//Function to display type utilizing type_input function
int single_type_disp( char* p,int size, char gmode)
{
    TC_CLRSCR();
    char tmp[size];
    strcpy(tmp,p);
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    int ycopy=y;
    TC_CLRSCR();
    TC_MOVE_CURSOR(x,y);
    if(p==NULL)
        return -1;
    for(int i=1;*p;i++)
    {
        if(i==columns-1)
        {
            i=1;
            ycopy++;
            TC_MOVE_CURSOR(x,ycopy);
            strcat(tmp,"  ");
        }
        //
        printf("%c\xDB",*(p++));
        //
        printf("\b \b");
    }
    TC_MOVE_CURSOR(x,y);
    return single_type_input(tmp,size,gmode);
}

// //Function to check typing input 
int single_type_input(char* p,int size,char gmode)
{
    clear_instream();
    printf("\e[?25l");
    char ch='a';
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    for(;((*(p+1))!='\0')&&(ch=getch());)
    {
        caps_check();
        if(ch==*p)
        {
            TC_MOVE_CURSOR(x,y);
            printf("%s\b",p+1);
            p+=1;
            trimTrailing(p);
        }
        else
        {  
            if(gmode=='z')
                return 0;
        }
    }
    return 1;
}
// void score_save(int mode, float *wpm, float *acc, float *netwpm, int BBscore)
// {
//     open_scorefile();
//     strcpy(scores[score_n].date,__DATE__);
//     strcpy(scores[score_n].time,__TIME__);
//     scores[score_n].gmode=mode;
//     scores[score_n].wpm=*wpm;
//     scores[score_n].accuracy=*acc;
//     scores[score_n].netwpm=*netwpm;
//     scores[score_n].BBscore=BBscore;
//     score_n++;
//     // open_scorefile();
//     write_score(mode,wpm,acc,netwpm,BBscore);
// }


//dll implementation code, will be moved to other file later
//Function to copy code from the file and copy it onto the
//place to be typed on
void type_launch(char* diff,char* sent,char gmode)
{
    strcpy(sent,rand_string(diff,300,sent));
    int size=strlen(sent)-1;
    trimTrailing(sent);
    string_push(sent);
    type_disp(size,gmode);
}


int type_disp(int size, char gmode)
{
    TC_CLRSCR();
    string_print(size);
    return type_input(size,gmode);
}



//Function to check typing input 
int type_input(int size,char gmode)
{
    clear_instream();
    printf("\e[?25l");
    TSTRING *trav=tstring_head;
    CHAR_NODE *current_node = NULL;
    clock_t t;
    char ch='a';
    int BBscore=0;
    int time_tmp=1;
    int count=0;
    int streak=0;
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    FILE *fp;
    fp=fopen("resources/art/BB_Launch.txt","r");
    // char bball=fgetc(fp);
    char bball[200];
    fgets(bball,200,fp);
    int b=1;
    for(;(trav) && (trav->data->exp_char!='\0') && (ch=getch());)
    {
        caps_check();
        current_node = trav->data;
        if(time_tmp)
        {
            t=clock();
            time_tmp--;
        }
        if(ch==trav->data->exp_char)
        {
            TC_MOVE_CURSOR(x,y);
            TSTRING* next_trav = trav->next;
            string_pop(&trav);
            trav = next_trav;
            string_print(size);
            count+=1;
            streak++;
        }
        else if(ch == 127 || ch == 8)
        {
            if(trav->prev)
            {
                trav=trav->prev;
                trav->data->color_flag=1;
                if(trav->data->exp_char == '_')
                    trav->data->exp_char = ' ';
                count--;
                string_print(size);
            }
            continue;
        }
        else
        {  
            if(gmode=='z')
                return 0;
            if(gmode=='s')
            {
                size=count;
                break;
            }
            stk_push(trav->data->exp_char);
            handle_wrong_case(fp,&b,&streak,&count,&(trav->data),x,y,size,0);
            trav=trav->next;
        }


        if((gmode=='b') && (streak>0) && (streak%5==0))
        { 
            TC_MOVE_CURSOR(0,b);
            // for(;bball!='\n';)
            // {
            //     printf("%c",bball);
            //     bball=fgetc(fp);
            // }
            // b++;
            // bball=fgetc(fp);
            printf("%s\n",bball);
            fgets(bball,200,fp);
            b++;

            if(streak==70)
            {
                if(bball_dunk())
                {
                    art_disp("resources/art/BB_Dunk.txt");
                    BBscore+=25;
                }
                else
                {
                    art_disp("resources/art/OOF.txt");
                    BBscore+=5;
                }
                fseek(fp,0,SEEK_SET);
                term_sleep(1000);
                clear_instream();
                TC_CLRSCR();
                caps_check();
                TC_MOVE_CURSOR(x,y);
                string_print(size);
                b=1;
            }
        }
    }
    if(gmode!='z')
    {    
        TC_CLRSCR();
        t = clock() - t;
        float time_taken = ((float)t)/CLOCKS_PER_SEC; // calculate the elapsed time
        #ifdef __linux__
            time_taken= ((time_taken)*1000)/2;
        #endif
        score(time_taken,count,size,gmode,BBscore);
    }

    return 1;
}