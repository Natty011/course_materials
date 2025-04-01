#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>
#include <pthread.h>    /*pthread_t, */
#include <signal.h>     /*kill, SIGUSR1 , siaction*/
#include <stdlib.h>     /*atoi*/
#include <unistd.h>
#include "scheduler.h"
#include "watchdog.h"
#include "utils.h"

volatile int g_stop_app = 0;
static volatile int g_missed_SOL = 0;
static pthread_t g_wd = 0;

static int InitInfo(wd_task_info_ty *info, int argc, char** argv);

int main(int argc, char** argv)
{
    wd_task_info_ty *info = NULL;
    struct sigaction sa_app = {0};
    char *new_argv[3] = {0};
    

    if()
    RETURN_IF_BAD( InitInfo(info, argc, argv), 1, "InitInfo failed");

   
    /*prepare argv for execvp*/
    new_argv[0] = argv[0];      /* ./watchdog_app */
    new_argv[1] = "watchdog"; /* flag to identify WD */
    new_argv[2] = NULL;



    /* Setup signal handler for SIGUSR1 (first signal) */
    sa_app.

    

    return 0;
}

static int InitInfo(wd_task_info_ty *info, int argc, char** argv)
{
    
    RETURN_IF_BAD(argc < 3, 1, "Use:./watchdog_app.out <#freq> <#misses>");

    info = (wd_task_info_ty*)malloc(sizeof(*info));
    RETURN_IF_BAD(info, 1, "malloc failed");

    info->ping_frequency_seconds = (size_t)atoi(argv[1]);
    info->allowed_misses = (size_t)atoi(argv[2]);
    info->argv = argv;
    info->argc = argc;
    info->sch = NULL;

    return 1;
}

  /*assert*/
     /*check that argv consists a string name that is
      identical with the executable file name */

     /*Register signal handler for SIGINT/SIGTERM via StopApp_HAND*/

    /*allow_misses = 5*/
    /*ping_frequency = 2 sec*/

    /*if MMI(Arguments...) failed */
        /*perror msg and exit */


    /*while(!g_stop_app)*/
        /*The job of the Application ...*/

     /*DNR()*/


/*signal handler to allow gracefull terminaion */

/*StopApp_HAND(int sig)*/

    /*change g_stop_app to true*/
    /*return*/
