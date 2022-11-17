//The client code that contains the main function
#include<stdio.h>
#include"../lib/tc.h"
#include"../lib/type_content.h"
#include<string.h>
#include<stdlib.h>
void help();
void color_help();
int main(int argc,char** argv)
{
    char sent[300];
    char gmode;
    char diff[100]="resources/test_strings/easy.txt";
    if(argc==1)
    {
        help();
        return 0;
    }
    if(argc==3)
    {
        if(!(strcmp(argv[2],"e")))
        {
            strcpy(diff,"resources/test_strings/easy.txt");
        }
        else if(!(strcmp(argv[2],"h")))
        {
            strcpy(diff,"resources/test_strings/heroic.txt");
        }
        else
        {
            strcpy(diff,"resources/test_strings/moderate.txt");    
        }
    }
    if(argc>=2)
    {
        #ifdef _WIN32
            if(!(strcmp(argv[1],"init")))//initialising the terminal on windows
            {
                system("init_terminal.bat");
            }
        #elif __linux__
            if(!(strcmp(argv[1],"init")))//initialising the terminal on windows
            {
                printf("Operation successful! You can use TYRBO normally now\n");
                exit(0);
            }
        #endif
        if(argv[1][0]=='-')
        {
            switch(argv[1][1])
            {
                case 'c':
                if(argc==3)
                {
                    change_color_code(argv[2][0]);
                }
                else
                {
                    color_help();
                }
                break;
            }
            exit(0);
        }
        art_disp("resources/art/TYRBO.txt");
        gmode=rand_mode();
        if(argv[1][0]=='s' || argv[1][0]=='n' || argv[1][0]=='b')
            gmode=argv[1][0];
    }
    type_launch(diff,sent,gmode);
    TC_CLRSCR();
    art_disp("resources/art/TYRBO.txt");
    printf("\e[?25h");
    // print_stk();
    // getch();
    free_structures();
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
    printf("-----------------------------------------------\n");
    printf("To change Art Color, run the folloring command:\n");
    printf("tyrbo -c\n");
    printf("-----------------------------------------------\n");
    printf("\nNOTE: IF THIS IS YOUR FIRST TIME RUNNING TYRBO, USE \"tyrbo init\" AND RESTART THE TERMINAL BEFORE USING TYRBO!\n");
}
void color_help()
{
    printf("Color Help:\n");
    printf("\nCommand:\ntyrbo -c COLOR_FLAG\n");
    printf("\nFLAGs:\n");
    printf("empty -> Color Help Menu(current page)\n");
    printf("COLOR FLAGS:\n");
    printf("w -> White\n");
    printf("r -> Red\n");
    printf("g -> Green\n");
    printf("y -> Yellow\n");
    printf("b -> Blue\n");
    printf("m -> Magenta\n");
    printf("c -> Cyan\n");
    printf("\nNOTE: IF THIS IS YOUR FIRST TIME RUNNING TYRBO, USE \"tyrbo init\" AND RESTART THE TERMINAL BEFORE USING TYRBO!\n");
}