#include<stdio.h>
#include<signal.h>
#include"../lib/signal_handlers.h"
#include"../lib/misc.h"


void signal_handler()
{
    signal(SIGINT,sigint_handler);
}

void sigint_handler(int sig)
{
    signal(SIGINT,SIG_DFL);
    printf("\nSIGINT Received\nFreeing allocated memory and terminating program..\n");
    clean_and_exit();
}