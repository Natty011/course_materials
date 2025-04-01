#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "watchdog.h"

volatile int g_stop_app = 0;
/*signal handler to allow gracefull terminaion */
StopApp_HAND(int sig)
{
    /*change g_stop_app to true*/
    /*return*/
}

int main(argc, argv)
{
     /*assert*/
     /*Register signal handler for SIGINT/SIGTERM via StopApp_HAND*/
    /*allow_misses = 5*/
    /*ping_frequency = 2 sec*/

    /*if MMI(Arguments...) failed */
        /*perror msg and exit */


    /*while(!g_stop_app)*/
        /*do your job...*/

     /*DNR()*/
     
     
    return 0;
}

