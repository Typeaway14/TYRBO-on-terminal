//This file contains the definitions of the functions defined in type_content.h
//Typing related functions can be found here
//For further details about a particular function, refer to documentation in respective header files.
#include<stdio.h>
#ifdef _WIN32
    #include<windows.h>//includes windows.h that contains functions like Sleep()
    #include<conio.h>//includes conio.h that contains functions like getch()
#elif __linux__
    #include<sys/ioctl.h>
    #include<unistd.h>//usleep()
    #include <termios.h>
#endif
#include<string.h> //includes string.h that contains string manipulation functions like strcmp() strlen()
#include<time.h>
#include<stdlib.h>
// #include"menu.h"
#include"type_content.h"//includes the user defined type_content.h header file
// #include"user_manage.h"//includes the user defined user_manage.h header file
#include"tc.h"
// SCORE scores[100];
int score_n;
FILE *score_fp;
char* rand_string(char* fname,int charno,char* sent)
{
    FILE *fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("failed");
    }
    FILE *fpcount=fopen(fname,"r");
    int lines=0;
    for(;fgets(sent,300,fpcount);)
    {
        lines++;
    }
    srand(time(NULL));
    int r=0;
    while(!(r>0))
    {
        r=rand() % lines;
    }
    for(int i=0;fp!=NULL && i<r;i++)
    {
        fgets(sent,charno,fp);
    }
    fclose(fp);
    return sent;
}
void type_launch(char* diff,char* sent,char gmode)
{
    strcpy(sent,rand_string(diff,300,sent));
    int size=strlen(sent)-1;
    type_disp(sent,size,gmode);
}
char rand_mode()
{
    srand(time(NULL));
    int r=0;
    while(!(r>0))
    {
        r=rand() % 3;
    }
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
int type_disp( char* p,int size, char gmode)
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
        printf("%c\xDB",*(p++));
        printf("\b \b");
    }
    TC_MOVE_CURSOR(x,y);
    return type_input(tmp,size,gmode);
}
int type_input(char* p,int size,char gmode)
{
    #ifdef _WIN32
        CLEAR_INSTREAM;
    #elif __linux__
        system("kendi.sh 0");
    #endif
    printf("\e[?25l");
    clock_t t;
    char ch='a';
    int BBscore=0;
    int tmp=1;
    int count=0;
    int streak=0;
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    FILE *fp;
    fp=fopen("resources/art/BB_Launch.txt","r");
    char bball=fgetc(fp);
    int b=1;
    for(;((*(p+1))!='\0')&&(ch=getch());)
    {
        #ifdef _WIN32
            caps_check();
        #elif __linux__
            system("kendi.sh 0");
        #endif
        if(tmp)
        {
            t=clock();
            tmp--;
        }
        if(ch==*p)
        {
            TC_MOVE_CURSOR(x,y);
            printf("%s\b",p+1);
            p+=1;
            count+=1;
            trimTrailing(p);
            streak++;
        }
        else
        {  
            if(gmode=='b')
                return 0;
            if(gmode=='s')
            {
                size=count;
                break;
            }
            handle_wrong_case(fp,&b,&streak,&count,p,x,y,0);
        }
        if((gmode=='b') && (streak>0) && (streak%5==0))
        { 
            TC_MOVE_CURSOR(0,b);
            for(;bball!='\n';)
            {
                printf("%c",bball);
                bball=fgetc(fp);
            }
            b++;
            bball=fgetc(fp);
            if(streak==65)
            {
                if(bball_dunk())
                {
                    #ifdef __linux__
                        system("kendi.sh 1");
                    #endif
                    art_disp("resources/art/BB_Dunk.txt");
                    BBscore+=25;
                }
                else
                {
                    #ifdef __linux__
                        system("kendi.sh 1");
                    #endif
                    art_disp("resources/art/OOF.txt");
                    BBscore+=5;
                }
                #ifdef _WIN32
                    Sleep(1000);
                #elif __linux__
                    usleep(1000000);
                #endif
                #ifdef _WIN32
                    CLEAR_INSTREAM;
                #elif __linux__
                    // clear_instream();
                #endif
                TC_CLRSCR();
                #ifdef _WIN32
                    caps_check();
                #endif
                ungetc('\n',stdin);
                ch=getc(stdin);
                count--;
                handle_wrong_case(fp,&b,&streak,&count,p,x,y,1);
                TC_CLRSCR();
                #ifdef _WIN32
                    caps_check();
                #endif
                TC_MOVE_CURSOR(x,y);
                printf("%s",p);
                #ifdef __linux__
                    system("kendi.sh 0");
                #endif
            }
        }
    }
    if(gmode!='b')
    {    
        TC_CLRSCR();
        t = clock() - t;
        float time_taken = ((float)t)/CLOCKS_PER_SEC; // calculate the elapsed time
        score(time_taken,count,size,gmode,BBscore);
    }
    return 1;
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
    if(gmode=='n')
    {
        // score_save(1,&wpm,&acc,&netwpm,-1);
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
        // score_save(2,&wpm,&acc,&netwpm,BBscore);
    }
    printf("\n%sPress any key to continue%s",TC_YEL,TC_NRM);
    #ifdef _WIN32
        Sleep(1500);
    #elif __linux__
        usleep(1500000);
    #endif
    getch();
}
void trimTrailing(char * str)
{
    printf("\e[?25l");
    int index, i;
    index = -1;//Set default index
    i = 0;//Find last index of non-white space character
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }
        i++;
    }
    str[index + 2] = '\0';//Mark next character to last non-white space character as NULL
}
int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,char* p,int x,int y,int color)
{
    TC_CLRSCR();
    #ifdef _WIN32
        caps_check();
    #endif
    fseek(fp,0,SEEK_SET);
    *b=0;
    TC_MOVE_CURSOR(x,y); 
    if(*p==' ')
    {
        printf("%s%c%s%s\b",TC_RED,'_',TC_NRM,p+1);
        *streak=0;
        *count+=1;
        return 1;
    }
    printf("%s%c%s%s\b",TC_RED,*(p),TC_NRM,p+1);
    if(color)
    {
        TC_MOVE_CURSOR(x,y);
        printf("%s\b",p);

    }
    *streak=0;
    *count+=1;
    return 1;
}
void art_disp(char *filename)
{
    printf("\e[?25l");
    FILE *fp;
    fp=fopen(filename,"r");
    char ch[200];
    //fscanf(fp,"%c",&ch);
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    while(fgets(ch,200,fp)!=NULL)
    {
        printf("%s%s%s",TC_GRN,ch,TC_NRM);
        #ifdef _WIN32
            Sleep(16);
        #elif __linux__
            usleep(16000);
        #endif

    }
    // while(ch!=EOF)
    // {
    //     ch=fgetc(fp);
    //    // Sleep(1);
    //     printf("%s%c%s",TC_GRN,ch,TC_NRM);
    // }
    fclose(fp);
}
int bball_dunk()
{
    #ifdef __linux__
        system("kendi.sh 1");
    #endif
    FILE *frand;
    frand=fopen("resources/Dunk_words.csv","r");
    srand(time(NULL));
    int r=0;
    while(!(r>0))
    {
        r=rand() % 213;
    }
    char ch[1500];
    char tmp[6];
    // char tmp2[6];
    if(fgets(ch,1500,frand)==NULL)
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        #ifdef _WIN32
            Sleep(200);
        #elif __linux__
            usleep(200000);
        #endif
    } 
    char* tmp2=strtok(ch,",");
    if(tmp2!=NULL)
    {
        strcpy(tmp,tmp2);
    }
    else
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        #ifdef _WIN32
            Sleep(200);
        #elif __linux__
            usleep(200000);
        #endif
    }
    for(int i=0;i<=r-1;i++)
    {
        tmp2=strtok(NULL,",");
        if(tmp2!=NULL)
        {
            strcpy(tmp,tmp2);
        }
        else
        {
            TC_CLRSCR();
            printf("Something went wrong..\nReturning back to home page..\n");
            #ifdef _WIN32
                Sleep(200);
            #elif __linux__
                usleep(200000);
            #endif
        }
    }
    TC_CLRSCR();
    art_disp("resources/art/BASKETBALL.txt");
    #ifdef _WIN32
        Sleep(750);
    #elif __linux__
        usleep(750000);
    #endif
    fclose(frand);
    return type_disp(tmp,5,'b');
}
#ifdef _WIN32
    void caps_check()
    {
        int rows=0,columns=0;
        termsize(&rows,&columns);
        if (GetKeyState(VK_CAPITAL) & 1)
        {
            TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
            printf("CAPS LOCK IN ON");
        }
        else
        {
            TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
            printf("               ");
        }
    }
#elif __linux__
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
        // printf("%c\n", buf);
        return buf;
    }
#endif
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