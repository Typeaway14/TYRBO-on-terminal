//The client code that contains the main function
#include<stdio.h>
#include"type_content.h"//includes the user defined type_content.h header file
#include"tc.h"
#include<string.h>
void help();
int main(int argc,char** argv)
{
    if(argc==1)
    {
        help();
        return 0;
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
                printf("Operation successful! You can turn TYRBO normally now");
            }
        #endif
        art_disp("resources/art/TYRBO.txt");
        if(!(strcmp(argv[1],"n")))//normal mode. actually pass 'n'
        {
            type_disp("This is the normal mode ",24,'n');
        }
        else if(!(strcmp(argv[1],"s")))//sudden death mode. actually pass 'd'
        {
            type_disp("This is the sudden death mode  ",30,'d');
        }
        else if(!(strcmp(argv[1],"b")))//basketball mode. actually pass 's'
        {
            type_disp("This is the basketball mode aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ",101,'s');
        }
        else
        {
            type_disp("This is the default mode selected due to incorrect input ",57,'n');
        }
    }
    TC_CLRSCR();
    art_disp("resources/art/TYRBO.txt");
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    return 0;
}
void help()
{
    printf("TYRBO-on-terminal Help:\n");
    printf("\nCommand:\ntyrbo FLAG\n");
    printf("\nFLAGs:\n");
    printf("empty -> Help Menu(current page)\n");
    printf("n -> Normal Mode\n");
    printf("s -> Sudden Death Mode\n");
    printf("b -> Basketball Mode\n");
    printf("\nNOTE: IF THIS IS YOUR FIRST TIME RUNNING TYRBO, USE \"tyrbo init\" AND RESTART THE TERMINAL BEFORE USING TYRBO!\n");
}