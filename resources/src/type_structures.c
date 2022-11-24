#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../lib/type_structures.h"
#include"../lib/tc.h"

TSTRING *tstring_head=NULL;
CH_STK *stk_head=NULL;

void string_push(char* sent)
{
    for(int i=0;i<strlen(sent)-1;i++) // -1 ensures last whitespace not added to dll
    {
        TSTRING *tstring_tmp = (TSTRING*)malloc(sizeof(TSTRING));
        CHAR_NODE *node_tmp = (CHAR_NODE*)malloc(sizeof(CHAR_NODE));
        TSTRING *trav = tstring_head;
        tstring_tmp->next=NULL;
        tstring_tmp->prev=NULL;
        node_tmp->color_flag=1;
        node_tmp->exp_char=sent[i];
        tstring_tmp->data=node_tmp;
        if(tstring_head==NULL)
        {
            tstring_head=tstring_tmp;
        }
        else
        {
            while(trav->next)
            {
                trav=trav->next;
            }
            trav->next=tstring_tmp;
            tstring_tmp->prev=trav;
        }
    }
}

void string_pop(TSTRING** trav)
{
    if(*trav == tstring_head)// takes care if first node is to be deleted
    {
        tstring_head = tstring_head->next;
        if(tstring_head) //if tstring_head is still a node, change the prev to null as no node before the head exists
            tstring_head->prev = NULL;
    }
    else//takes care if last node is to be deleted
    {
        (*trav)->prev->next = (*trav)->next;
        if((*trav)->next) // takes care if middle node is to be deleted
            (*trav)->next->prev = (*trav)->prev;
    }
    free((*trav)->data);
    free(*trav);
    *trav=NULL;
}

void string_print(int size)
{
    TSTRING *trav = tstring_head;
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    TC_MOVE_CURSOR(x,y);
    if(!tstring_head)
    {
        return;
    }
    else
    {
        while(trav)
        {
            if(trav->data->color_flag == 1)
            {
                fprintf(stdout,"%c",trav->data->exp_char);
                fflush(stdout);
            }
            else
            {
                fprintf(stdout,"%s%c%s",TC_RED,trav->data->exp_char,TC_NRM);
                fflush(stdout);
            }
            trav=trav->next;
        }
        fprintf(stdout,"%c",' ');
        fprintf(stdout,"%c",' ');
        fflush(stdout);
    }
}

void stk_push(char err_char)
{
    STK_NODE *node_temp = (STK_NODE*)malloc(sizeof(STK_NODE));
    CH_STK *stk_temp = (CH_STK*)malloc(sizeof(CH_STK));
    node_temp->exp_char = err_char;
    // node_temp->inp_char = inp_char;
    node_temp->occurence=0;
    stk_temp->data = node_temp;
    stk_temp->next = NULL;
    if(!stk_head)
    {
        stk_temp->data->occurence++;
        stk_head = stk_temp;
    }
    else if(stk_check(err_char))//stk_check to return 1 if not in stack, 0 if already in stack
    {
        stk_temp->data->occurence++;
        stk_temp->next = stk_head;
        stk_head = stk_temp;
    }
    else
    {
        free(node_temp);
        free(stk_temp);
        node_temp=NULL;
        stk_temp=NULL;
    }
}

int stk_check(char err_char)
{
    CH_STK *trav = stk_head;
    while(trav)
    {
        if(trav->data->exp_char == err_char)
        {
            trav->data->occurence++;
            return 0;
        }
        trav = trav->next;
    }
    return 1;
}

void print_stk() // temp function to print stack to see if the thing works
{
    CH_STK *trav = stk_head;
    for(int i=1;trav;i++)
    {
        printf("%d) %c - %d\n",i,trav->data->exp_char,trav->data->occurence);

        trav = trav->next;
    }
}

void free_structures()
{
    free_dll();
    free(tstring_head);
    free_stk();
    free(stk_head);
}

void free_dll()
{
    TSTRING *trav = tstring_head;
    while(tstring_head)
    {
        tstring_head=tstring_head->next;
        free(trav->data);
        free(trav);
        trav = tstring_head;
    }
}

void free_stk()
{
    CH_STK *trav = stk_head;
    while(stk_head)
    {
        stk_head = stk_head->next;
        free(trav->data);
        free(trav);
        trav = stk_head;
    }
}
