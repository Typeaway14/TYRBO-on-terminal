//The client code that contains the main function
#include<stdio.h>
#include"type_content.h"//includes the user defined type_content.h header file
#include"tc.h"
#include<string.h>
void help();
int main(int argc,char** argv)
{
    char sent[300];
    char gmode;
    char diff[50]="easy.txt";
    if(argc==1)
    {
        help();
        return 0;
    }
    if(argc==3)
    {
        if(!(strcmp(argv[2],"e")))
        {
            strcpy(diff,"easy.txt");
        }
        else if(!(strcmp(argv[2],"h")))
        {
            // strcpy(diff,"hard.txt");
            strcpy(diff,"easy.txt");
        }
        else
        {
            // strcpy(diff,"moderate.txt");
            strcpy(diff,"easy.txt");
        }
    }
    if(argc==2)
    {
        #ifdef _WIN32
            if(!(strcmp(argv[1],"init")))//initialising the terminal on windows
            {
                system("init_terminal.bat");
            }
        #elif __linux__
            if(!(strcmp(argv[1],"init")))//initialising the terminal on windows
            {
                printf("Operation successful! You can use TYRBO normally now");
            }
        #endif
        art_disp("resources/art/TYRBO.txt");
        gmode=rand_mode();
        if(argv[1][0]=='s' || argv[1][0]=='n' || argv[1][0]=='b')
            gmode=argv[1][0];
    }
    type_launch(diff,sent,gmode);
    TC_CLRSCR();
    art_disp("resources/art/TYRBO.txt");
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    return 0;
}
void help()
{
    printf("TYRBO-on-terminal Help:\n");
    printf("\nCommand:\ntyrbo MODE_FLAG DIFFICULTY_FLAG\n");
    printf("\nFLAGs:\n");
    printf("empty -> Help Menu(current page)\n");
    printf("MODE FLAGS:\n");
    printf("n -> Normal Mode\n");
    printf("s -> Sudden Death Mode\n");
    printf("b -> Basketball Mode\n");
    printf("r -> Random Mode\n");
    printf("DIFFICULTY_FLAGS(Optional):\n");
    printf("e -> Easy\n");
    printf("m -> Normal\n");
    printf("h -> Heroic\n");
    printf("\nNOTE: IF THIS IS YOUR FIRST TIME RUNNING TYRBO, USE \"tyrbo init\" AND RESTART THE TERMINAL BEFORE USING TYRBO!\n");
}