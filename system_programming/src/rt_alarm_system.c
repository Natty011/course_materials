/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 25 / 03 / 2025
 * Last update: 25 / 03 / 2025
 *****************************************/

#include <stdio.h>      /* printf, getchar */     
#include <stdint.h>     /* uint8_t, uint16_t, uint32_t*/
#include <stdlib.h>     /* rand */
#include <sys/time.h>   /*gettimeofday, timval*/
#include <sys/select.h> /*select, FD_ZERO, FD_SET, fd_set */
#include <signal.h>     /* signal*/
#include "utils.h"      /* ExitIfBad*/

#define MAX_TASKS (3) 

enum
{
    SMOKE_INTERVAL = 100, /* Time interval to check the trigger */
    EMERGENCY_INTERVAL = 1000,

    /* timer - every TICK_MS the app wake up and checks
         triggers/pending/pressing*/
    TICK_MS = 10,   
    MAX_PENDING = 10 
    
};

enum
{
    PRIORITY_SMOKE1 = 2,
    PRIORITY_SMOKE2 = 2,
    PRIORITY_EMERGENCY = 3
};

typedef int (*is_trigger_t)(void);
typedef void (*handler_t)(int chosen_tesk);

static void InitTasks(void);
static int TriggerSmoke(void);
static int TriggerEmergency(void);

static void HandlerSmoke(int chosen_tesk);
static void HandlerEmergecy(int chosen_tesk);
static int FindHighestPriority(int num_tasks);
static size_t GetTimeInMs(void);
static void HandleSignal(int sig);
static char GetKeyIfPressed(void);
static void TaskRun(void);
static void RunScheduler(void);


typedef struct task
{
    char name[20];          /*name of the task */
   
    uint16_t interval;      /*The interval of each trigger checking  */
    uint8_t priority;       /*priority of the task */

    is_trigger_t IsTrigger; /* return if trigger occered */
    handler_t Handler;      /*Handle the task if it triggered */

    size_t trigger_time;    /*when the task requested/triggered */
    size_t deadline_time;   /*Maximum time the task should be complete*/
    size_t next_check;      /*The next time to check if task gets a trigger */
    int pending_count;  /* How much requests in the qeueue  */

    uint32_t executions;    /*How many times the task execute */
    uint32_t deadline_misses; /*counts the fails in deadlines */


}task_t;

task_t g_tasks[MAX_TASKS] = {0};
int g_running = 1; /* can be exit in grace from the while loop */

int main()
{
    
    InitTasks();

    signal(SIGINT, HandleSignal);
    RunScheduler();

    return 0;
}

static void RunScheduler(void)
{
    char keyboard_press = 0;
    size_t curr_time = 0;

    printf("Press A + ENTER for Emergency\n");
    printf("Press S + ENTER for Smoke1 or D + ENTER for Smoke2\n");
    printf("Press CTRL+C to exit and view statistics.\n");
    
    size_t curr_time = GetTimeInMs();

}

static void TaskRun(void)
{
    int chosen = FindHighestPriority(MAX_TASKS);
    size_t curr_time = GetTimeInMs();

    if(-1 != chosen)
    {
        /*size_t response_time = curr_time - g_tasks[chosen].trigger_time;*/
        if(curr_time > g_tasks[chosen].deadline_time)
        {
            ++g_tasks[chosen].deadline_misses;
            printf("%s Task missed deadline. Pending: %d\n", g_tasks[chosen].name, g_tasks[chosen].pending_count);
        }

        g_tasks[chosen].Handler(chosen);

       --g_tasks[chosen].pending_count;
       ++g_tasks[chosen].executions;

       if(g_tasks[chosen].pending_count > 0)
       {
            g_tasks[chosen].trigger_time = curr_time;
            g_tasks[chosen].deadline_time = curr_time + g_tasks[chosen].interval; 
       }
       
    }
}


static void InitTasks(void)
{
    g_tasks[0] = (task_t){"Smoke1", SMOKE_INTERVAL, PRIORITY_SMOKE1, TriggerSmoke,
         HandlerSmoke, 0, 0, 0, 0, 0, 0};

    g_tasks[1] = (task_t){"Smoke2", SMOKE_INTERVAL, PRIORITY_SMOKE2, TriggerSmoke,
        HandlerSmoke, 0, 0, 0, 0, 0, 0};
        
    g_tasks[2] = (task_t){"Emergency", EMERGENCY_INTERVAL, PRIORITY_EMERGENCY,
        TriggerEmergency, HandlerEmergecy, 0, 0, 0, 0, 0, 0};    
}




static int TriggerSmoke(void)
{
    return rand() % 50 == 0;
}

static int TriggerEmergency(void)
{
    return rand() % 50 == 0;
}


static void HandlerSmoke(int chosen_tesk)
{
    printf("%s Detected!\n", g_tasks[chosen_tesk]);

}

static void HandlerEmergecy(int chosen_tesk)
{
    printf("%s buttom PRESSED!\n", g_tasks[chosen_tesk]);
}

static int FindHighestPriority(int num_tasks)
{
    int highest = -1;
    int i = 0;

    for(i = 0; i<num_tasks; ++i)
    {
        if(-1 == highest || 
            g_tasks[i].priority < g_tasks[highest].priority)
        {
            highest = i;
        }
    }

    return highest;

}

static size_t GetTimeInMs(void)
{
    struct timeval tv = {0};
    ExitIfBad(0 == gettimeofday(&tv, NULL)  , "gettimeofday failed\n");

    return (size_t)(tv.tv_sec * 1000 + tv.tv_usec/1000);

}

static void HandleSignal(int sig)
{
    g_running = 0;
}

static char GetKeyIfPressed(void)
{
    struct timeval tv =  {0L, 0L}; /* check if there input, don't wait*/
    fd_set file_desc = {0};
    int res = -1;

    int ch = 0;
    int c = 0;

    FD_ZERO(&file_desc);    /* reset */
    FD_SET(0, &file_desc); /* 0 == stdin */

    res = select(1, &file_desc, NULL, NULL, &tv);
    ExitIfBad(-1 != res, "select failed\n");

    if(res > 0)
    {
        ch =  getchar();

        while ( '\n' != (c = getchar()) && EOF !=  c)
        {}

        return ch;

    }

    return 0;

}



