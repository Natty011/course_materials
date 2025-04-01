#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>      /*perror, printf*/
#include <pthread.h>    /*pthread_t, */
#include <signal.h>     /*kill, SIGUSR1 , siaction*/
#include <stdlib.h>     /*atoi, exit*/
#include <sys/types.h>  /* pid_t */

#include <unistd.h>     /*fork*/
#include "scheduler.h"  /*Create, */
#include "watchdog.h"
#include "utils.h" /*RETURN_IF_BAD*/

volatile int should_stop = 0;
static volatile int g_missed_SOL = 0;
static pthread_t g_wd = 0;

static int InitInfo(wd_task_info_ty *info, int argc, char** argv);

int main(int argc, char** argv)
{
    wd_task_info_ty *info = NULL;
    struct sigaction sa_app = {0};
    char *new_argv[3] = {0};
    scheduler_t *sch = NULL;
    

    if(argc > 1 &&  (0 == strcmp(argv[1], "watchdog") ))
    {
        RunAsWatchdog();

        return 0;
    }

    RETURN_IF_BAD( InitInfo(info, argc, argv), 1, "InitInfo failed");
    sch = info->sch;

   /* Setup signal handler for SIGUSR1 (first signal) */
    sa_app.sa_handler = 


    /*prepare argv for execvp*/
    new_argv[0] = argv[0];      /* ./watchdog_app */
    new_argv[1] = "watchdog"; /* flag to identify WD */
    new_argv[2] = NULL;



    

    

    return 0;
}

static int InitInfo(wd_task_info_ty *info, int argc, char** argv)
{
    
    RETURN_IF_BAD(argc < 3, 1, "Use:./watchdog_app.out <#freq> <#misses>");

    info = (wd_task_info_ty*)malloc(sizeof(*info));
    RETURN_IF_BAD(info, 1, "malloc failed");

    info->sch = SchedulerCreate();
    if(NULL == info->sch)
    {
        free(info);
        info = NULL;
        RETURN_IF_BAD(FALSE, 1, "SchedulerCreate failed");

    }

    info->ping_frequency_seconds = (size_t)atoi(argv[1]);
    info->allowed_misses = (size_t)atoi(argv[2]);
    info->argv = argv;
    info->argc = argc;

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
