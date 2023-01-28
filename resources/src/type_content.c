#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"../lib/type_structures.h"
#include"../lib/type_content.h"
#include"../lib/tc.h"
#include"../lib/art.h"
#include"../lib/misc.h"
#ifdef _WIN32
    #include<windows.h>
    #include<conio.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include<unistd.h>
    #include<sys/wait.h>
    #include<signal.h>
#endif

char* rand_string(char* fname,int charno,char* sent)
{
    FILE *fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("Something Went Wrong");
        clean_and_exit();
    }
    int lines=0;
    for(;fgets(sent,300,fp);)
    {
        lines++;
    }
    fseek(fp,0,SEEK_SET);
    srand(time(NULL));
    int r=(rand() % lines)+1;;

    for(int i=0;fp!=NULL && i<r;i++)
    {
        fgets(sent,charno,fp);
    }
    fclose(fp);
    return sent;
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

int single_type_disp( char* p,int size, char gmode)
{
    TC_CLRSCR();
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    TC_CLRSCR();
    TC_MOVE_CURSOR(x,y);
    if(p==NULL)
        return -1;
    printf("%s", p);
    TC_MOVE_CURSOR(x,y);
    return single_type_input(p,size,gmode);
}

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

void type_launch(char* diff,char* sent,char gmode)
{
    rand_string(diff,300,sent);
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
            if(trav->data->exp_char == ' ')
                trav->data->exp_char = '_';
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
            printf("%s\n",bball);
            fgets(bball,200,fp);
            b++;

            if(streak==70)
            {
                dunk_decide(&BBscore,&b,size,x,y,fp);
            }
        }
    }
    if(gmode!='z')
    {    
        TC_CLRSCR();
        t = clock() - t;
        float time_taken = ((float)t)/CLOCKS_PER_SEC;
        #if defined(__linux__) || defined(__APPLE__)
            time_taken= ((time_taken)*1000)/2;
        #endif
        score(time_taken,count,size,gmode,BBscore);
    }
    fclose(fp);
    return 1;
}

void dunk_decide(int* BBscore, int* b,int size , int x, int y,  FILE* fp)
{
    int survived = 0;
    #ifdef __WIN32
        survived = bball_dunk();
    #elif defined(__linux__) || defined(__APPLE__)
        int fd[2]; // 0 for reading 1 for writing
        if(pipe(fd) == -1)
        {
            printf("Pipe failed! Exiting safely...");
            exit(0);
        }
        pid_t proc_id = fork();
        if(proc_id == 0)
        {
            close(fd[0]);//close read stream coz not needed
            alarm(5);
            survived = bball_dunk();
            alarm(0);
            write(fd[1],&survived,sizeof(survived));
            close(fd[1]);//closing write stream coz done writing
            exit(0);
        }
        else if(proc_id > 0)
        {
            wait(NULL);
            close(fd[1]);//closing write stream coz not needed
            read(fd[0],&survived,sizeof(survived));
            close(fd[0]);//closing read stream coz done reading     
        }
        else
        {
            printf("Fork function failed\n");
        }
    #endif

    if(survived)
    {
        art_disp("resources/art/BB_Dunk.txt");
        (*BBscore)+=25;
    }
    else
    {
        art_disp("resources/art/OOF.txt");
        (*BBscore)+=5;
    }
    fseek(fp,0,SEEK_SET);
    term_sleep(1000);
    clear_instream();
    TC_CLRSCR();
    caps_check();
    TC_MOVE_CURSOR(x,y);
    string_print(size);
    *b=1;
}