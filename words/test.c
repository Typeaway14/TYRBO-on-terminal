#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
char* rand_string(char* fname,int charno,char*);
int main()
{
    char sent[300];
    strcpy(sent,rand_string("easyv.txt",300,sent));
    printf("%s",sent);
    return 0;
}
char* rand_string(char* fname,int charno,char* sent)
{
    FILE *fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("failed");
    }
    srand(time(NULL));
    int r=0;
    while(!(r>0))
    {
        r=rand() % 16;
    }
    for(int i=0;fp!=NULL && i<r;i++)
    {
        fgets(sent,charno,fp);
    }
    fclose(fp);
    return sent;
}