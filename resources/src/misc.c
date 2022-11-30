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
    #include<windows.h>//includes windows.h that contains functions like Sleep()
    #include<conio.h>//includes conio.h that contains functions like getch()
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
        // printf("%c\n", buf);
        return buf;
    }
#endif

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

//Function to find whether 
int bball_dunk()
{
   //Opening file resources/Dunk_words.csv in read mode
    FILE *frand;
    frand=fopen("resources/Dunk_words.csv","r");

    srand(time(NULL));
    int r=0;

    //Loop to iterate until r is not greater than zero
    do
    {
        //r is assigned to a random number from 0 to 3 of lines in fpcount
        r=rand() % 213;
    } while (!r);
    char ch[1500];
    //Conditional statement to check if resources file is not equal to NULL
    if(fgets(ch,1500,frand)==NULL)
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        term_sleep(200);
        clean_and_exit();
    } 

    //Converting string to token
    char* tmp=strtok(ch,",");

    //If token is not null printing message that something went wrong and delaying
    if(!tmp)
    {
        TC_CLRSCR();
        printf("Something went wrong..\nReturning back to home page..\n");
        term_sleep(200);
        clean_and_exit();
    }

    //Loop to iterate from 0 to random value - 1
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
<<<<<<< HEAD
}

void clean_and_exit()
{
    free_structures();
    exit(0);
}
||||||| parent of 65e0555 (Allow running on macos)
}
=======
}
>>>>>>> 65e0555 (Allow running on macos)
