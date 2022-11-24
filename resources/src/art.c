#include<stdio.h>
#include"../lib/tc.h"
#include"../lib/art.h"
#include<string.h>
void art_disp(char *filename)
{
    printf("\e[?25l");
    FILE *fp;
    fp=fopen(filename,"r");
    char ch[200];
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