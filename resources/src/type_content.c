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
#include"../lib/type_structures.h"
#include"../lib/type_content.h"//includes the user defined type_content.h header file
#include"../lib/tc.h"
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

//Function to find score of typing speed test
void score(float time_taken,int count,int size,char gmode,int BBscore)
{
    //Displaying the text using escape sequence escape character
    printf("\e[?25l");

    //Moving cursor from 0 to 0
    TC_MOVE_CURSOR(0,0);

    //Increasing the count received through the argument
    count++;

    //Finding word per minute
    float wpm=((size/5)/(time_taken/60));

    //Finding accuracy of the typing
    float acc=((float)size/(float)count)*100;

    //Finding net word per minute
    float netwpm=wpm*(acc/100);

    if(gmode!='s')
    {   
        //Displaying details of time taken to type, words per minute 
        //and words per minute after checking accuracy
        printf("\nTime Taken: %s%.2fs%s\nCharacters: %s%d/%d%s",TC_GRN,time_taken,TC_NRM,TC_GRN,++count,size,TC_NRM);
        printf("\nYour WPM was: %s%.1f%s",TC_GRN,wpm,TC_NRM);
        printf("\nYour net WPM was: %s%.1f%s",TC_GRN,netwpm,TC_NRM);

        //conditional statement for 100% accuracy  
        if(acc==100.0)
        {
            printf("\nYour accuracy was: %s",TC_CYN);
        }

        //conditional statement for >=95.0% accuracy
        else if(acc>=95.0)
        {
            printf("\nYour accuracy was: %s",TC_MAG);
        }

        //conditional statement for >=90.0 && <95.0 accuracy
        else if(acc>=90.0 && acc<95.0)
        {
            printf("\nYour accuracy was: %s",TC_GRN);
        }

        //conditional statement for >=80.0 && acc<90.0 accuracy
        else if(acc>=80.0 && acc<90.0)
        {
            printf("\nYour accuracy was: %s",TC_YEL);
        }

        //conditional statement for <80 accuracy
        else
        {
            printf("\nYour accuracy was: %s",TC_RED);
        }
        printf("%.1f%c%s",acc,'%',TC_NRM);
    }

    //Conditional statements based on the random characters from function rand_mode
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
    problem_keys_analysis();
    //Delaying the script execution based on operating system being 
    //Windows or Linux
    term_sleep(1500);
    //To continue after results
    printf("\n%sPress any key to continue%s",TC_YEL,TC_NRM);
    clear_instream();
    getch();
}

//Function to encounter spaces, tabs and next lines
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
//Function to display the text chosen randomly from the database of files
void art_disp(char *filename)
{
    printf("\e[?25l");
    FILE *fp;
    fp=fopen(filename,"r");
    char ch[200];
    //fscanf(fp,"%c",&ch);
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    char color[11];
    strcpy(color,get_color_code());
    while(fgets(ch,200,fp)!=NULL)
    {
        printf("%s%s%s",color,ch,TC_NRM);
        term_sleep(16);

    }
    fclose(fp);
}

char* get_color_code()
{
    FILE *fp_color;
    fp_color=fopen("resources/art/TYRBO.txt","r");
    fseek(fp_color,-1,SEEK_END);
    char color_code=fgetc(fp_color);
    fclose(fp_color);
    switch(color_code)
    {
        case 'w':
            return TC_NRM;
        break;
        case 'r':
            return TC_RED;
        break;
        case 'g':
            return TC_GRN;
        break;
        case 'y':
            return TC_YEL;
        break;
        case 'b':
            return TC_B_BLU;
        break;
        case 'm':
            return TC_MAG;
        break;
        case 'c':
            return TC_CYN;
        break;
        default:
            printf("Invalid color code, defaulting to green..");
            return TC_GRN;
    }
}

void change_color_code(char color_code)
{
    FILE *fp_color;
    fp_color=fopen("resources/art/TYRBO.txt","r+");
    fseek(fp_color,-1,SEEK_END);
    fputc(color_code,fp_color);
    fclose(fp_color);
}
//Defing conditions for Windows OS to find Caps
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
        printf("SOMETHING WENT WRONG");
    }
    pclose(p);
    if (result[0] == 'o' && result[1] == 'n')
#endif
    {
        TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
        printf("CAPS LOCK IS ON");
    }

//Defining conditions for Linux OS to Caps

    else
    {
        TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
        printf("               ");
    }
}
#ifdef __linux__
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

//Function to find whether 
int bball_dunk()
{
   //Opening file resources/Dunk_words.csv in read mode
    FILE *frand;
    frand=fopen("resources/Dunk_words.csv","r");

    srand(time(NULL));
    int r=0;

    //Loop to iterate until r is not greater than zero
    while(!(r>0))
    {
        //r is assigned to a random number from 0 to 3 of lines in fpcount
        r=rand() % 213;
    }
    char ch[1500];
    char tmp[6];
    // char tmp2[6];

    //Conditional statement to check if resources file is not equal to NULL
    if(fgets(ch,1500,frand)==NULL)
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        term_sleep(200);
    } 

    //Converting string to token
    char* tmp2=strtok(ch,",");

    //Checking if token is NULL and copying value to tmp
    if(tmp2!=NULL)
    {
        strcpy(tmp,tmp2);
    }

    //If token is not null printing message that something went wrong and delaying
    else
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        term_sleep(200);
    }

    //Loop to iterate from 0 to random value - 1
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
            term_sleep(200);
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

//Stack implementation here, change later

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