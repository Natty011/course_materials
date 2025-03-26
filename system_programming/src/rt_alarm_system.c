/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 25 / 03 / 2025
 * Last update: 26 / 03 / 2025
 *****************************************/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>      /* printf, getchar */     
#include <stdint.h>     /* uint8_t, uint16_t, uint32_t*/
#include <stdlib.h>     /* rand */
#include <time.h>       /*nanosleep */

#include <sys/time.h>   /*gettimeofday, timval*/
#include <sys/select.h> /*select, FD_ZERO, FD_SET, fd_set */
#include <signal.h>     /* signal*/
#include <string.h>     /*memcpy*/
#include "utils.h"      /* ExitIfBad*/

#define MAX_TASKS (3) 
#define BACK_RED     "\x1b[41m"
#define RESET        "\x1b[0m"


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
    PRIORITY_EMERGENCY = 1
};

enum
{
    TRIGGER_PROBABILITY_SMOKE = 50,
    TRIGGER_PROBABILITY_EMERGENCY = 50
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
void PrintStatistics(void);
static void SleepMs(size_t ms);

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
    char ch = 0;
    size_t curr_time = 0;
    int i = 0;

    printf("Press A + ENTER for Emergency\n");
    printf("Press S + ENTER for Smoke1 or D + ENTER for Smoke2\n");
    printf("Press CTRL+C to exit and view statistics.\n");
    
    while(g_running)
    {
        curr_time = GetTimeInMs();

        for(i = 0; i < MAX_TASKS; ++i)
        {
            
            if(curr_time > g_tasks[i].next_check && 
              g_tasks[i].pending_count < MAX_PENDING &&
              g_tasks[i].IsTrigger() )
            {
                if(0 == g_tasks[i].pending_count)
                {
                    g_tasks[i].trigger_time = curr_time;
                    g_tasks[i].deadline_time = curr_time + g_tasks[i].interval;
                }

                ++g_tasks[i].pending_count;

                /*the next time that allowed to check the trigger result of
                the task i--> not less then the time interval of the task*/
                g_tasks[i].next_check = curr_time + g_tasks[i].interval;
            }

            ch = GetKeyIfPressed();

            if('A' == ch)
            {
                if(g_tasks[2].pending_count < MAX_PENDING)
                {
                    ++g_tasks[2].pending_count;
                    g_tasks[2].trigger_time = curr_time;
                    g_tasks[2].deadline_time = curr_time + g_tasks[i].interval;

                }
            }

            else if('S' == ch)
            {
                if(g_tasks[0].pending_count < MAX_PENDING)
                {
                    ++g_tasks[0].pending_count;
                    g_tasks[0].trigger_time = curr_time;
                    g_tasks[0].deadline_time = curr_time + g_tasks[i].interval;

                }
            }

            else if('D' == ch)
            {
                if(g_tasks[1].pending_count < MAX_PENDING)
                {
                    ++g_tasks[1].pending_count;
                    g_tasks[1].trigger_time = curr_time;
                    g_tasks[1].deadline_time = curr_time + g_tasks[i].interval;

                }
            }

            TaskRun();
            SleepMs(TICK_MS);
        }

    }

    PrintStatistics();

}

static void TaskRun(void)
{
    int chosen = FindHighestPriority(MAX_TASKS);
    size_t curr_time = GetTimeInMs();

    if(-1 != chosen)
    {
        size_t response_time = curr_time - g_tasks[chosen].trigger_time;
        printf("[%lums] Executing %s (response time = %lums) [Pending=%d]\n\n",
            curr_time, g_tasks[chosen].name, response_time, g_tasks[chosen].pending_count);
            ח

        if(curr_time > g_tasks[chosen].deadline_time)
        {
            ++g_tasks[chosen].deadline_misses;
            printf(""BACK_RED"%s Task missed deadline. Pending: %d"RESET"\n", g_tasks[chosen].name, g_tasks[chosen].pending_count);
        
        }

        g_tasks[chosen].Handler(chosen);

       ++g_tasks[chosen].executions;

       if(g_tasks[chosen].pending_count > 0)
       {
            --g_tasks[chosen].pending_count;
            g_tasks[chosen].trigger_time = curr_time;
            g_tasks[chosen].deadline_time = curr_time + g_tasks[chosen].interval; 
       }
    }
}

static void InitTasks(void)
{
    
    static const task_t init_tasks[MAX_TASKS] = 
    {
        {"Smoke1", SMOKE_INTERVAL, PRIORITY_SMOKE1, TriggerSmoke,
            HandlerSmoke, 0, 0, 0, 0, 0, 0}, 

        {"Smoke2", SMOKE_INTERVAL, PRIORITY_SMOKE2, TriggerSmoke,
            HandlerSmoke, 0, 0, 0, 0, 0, 0},
        
        {"Emergency", EMERGENCY_INTERVAL, PRIORITY_EMERGENCY,
            TriggerEmergency, HandlerEmergecy, 0, 0, 0, 0, 0, 0}
   };   
   
   memcpy(g_tasks, init_tasks, sizeof(init_tasks));

}

static int TriggerSmoke(void)
{
    return rand() % TRIGGER_PROBABILITY_SMOKE == 0;
}

static int TriggerEmergency(void)
{
    return rand() % TRIGGER_PROBABILITY_EMERGENCY == 0;
}

static void HandlerSmoke(int chosen_tesk)
{
    printf("%s Detected!\n", g_tasks[chosen_tesk].name);
}

static void HandlerEmergecy(int chosen_tesk)
{
    printf("%s buttom PRESSED!\n", g_tasks[chosen_tesk].name);
}

static int FindHighestPriority(int num_tasks)
{
    int highest = -1;
    int i = 0;

    
        for(i = 0; i<num_tasks; ++i)
        {
            if(g_tasks[i].pending_count > 0)
            {

                if(-1 == highest || 
                    g_tasks[i].priority < g_tasks[highest].priority)
                {
                    highest = i;
                }
            }
        }    
        return highest;
}

static void SleepMs(size_t ms)
{
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);

}
static size_t GetTimeInMs(void)
{
    struct timeval tv = {0};
    ExitIfBad(0 == gettimeofday(&tv, NULL)  , "gettimeofday failed\n");

    return (size_t)(tv.tv_sec * 1000 + tv.tv_usec/1000);
}

static void HandleSignal(int sig)
{
    (void)sig;
    g_running = 0;
}

static char GetKeyIfPressed(void)
{
    struct timeval tv =  {0L, 0L}; /* check if there input, don't wait*/
    fd_set file_desc;
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

void PrintStatistics(void)
{
    int i = 0;
    int total_exec = 0;
    int total_miss = 0;
    float success = 0.0;
    float system_success = 0.0;

    printf("\n\n=== System Summary ===\n");
    for (i = 0; i < MAX_TASKS; ++i)
    {
        total_exec += g_tasks[i].executions;
        total_miss += g_tasks[i].deadline_misses;
        
        success = g_tasks[i].executions > 0 ?
            100.0f * (g_tasks[i].executions - g_tasks[i].deadline_misses) / g_tasks[i].executions : 0.0f;

        printf("Task: %-10s | Executions: %3d | Deadline Misses: %3d | Success: %5.1f%%\n",
               g_tasks[i].name, g_tasks[i].executions, g_tasks[i].deadline_misses, success);
    }
    printf("=======================\n");

    system_success = total_exec > 0 ?
    100.0f * (total_exec - total_miss) / total_exec : 0.0f;

    printf("Overall Success Rate: %.1f%%\n", system_success);
    printf("=======================\n");
    
}



