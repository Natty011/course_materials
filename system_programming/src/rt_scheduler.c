/***************************************
 * Author : Natty
 * Exercise: real time intro #2
 * Reviewer : ?
 * Date : 25 / 03 / 2025
 * Last update: 26 / 03 / 2025
 *****************************************/

#define _POSIX_C_SOURCE 199309L /*nanosleep*/

#include <stdio.h>      /* printf */ 
#include <stdint.h>     /* uint8_t, uint16_t, uint32_t*/
#include <time.h>       /*nanosleep*/
#include <string.h>     /*memcpy*/
#include <sys/time.h>   /*gettimeofday, timval*/

#include "utils.h"      /*ExitIfBad*/

#define MAX_TASKS 2

enum
{
    TASK1_INTERVAL = 100, /* Time interval (in ms) to check the trigger */
    TASK2_INTERVAL = 1000,

    /* timer - every TICK_MS the app wake up and checks
            triggers/pending/pressing*/
    TICK_MS = 10,   
    MAX_PENDING = 10 

};

enum
{
    PRIORITY_TASK1 = 50,
    PRIORITY_TASK2 = 50
};

typedef void (*handler_t)(int);

typedef struct task
{
    char name[20];
    uint16_t interval;
    uint8_t priority;
    handler_t Handler;

    size_t trigger_time;
    size_t deadline_time;
    int pending_count;

    uint32_t executions;
    uint32_t deadline_misses;

}task_t;

static task_t g_tasks[MAX_TASKS];
static int g_running = 1;

static void RunScheduler(void);
static void SleepMs(size_t ms);
static size_t GetTimeInMs(void);
static int FindHighestPriority(void);
static void Task1Handler(int i);
static void Task2Handler(int i);
static void InitTasks(void);


int main(void)
{
    InitTasks();
    RunScheduler();
    return 0;
}

static void RunScheduler(void)
{
    size_t curr_time = 0;
    size_t last_trigger[MAX_TASKS] = {0};
    int i = 0;
    int chosen = -1;


    while (g_running)
    {
        curr_time = GetTimeInMs();

        for (i = 0; i < MAX_TASKS; ++i)
        {
            if (curr_time - last_trigger[i] >= g_tasks[i].interval &&
                     g_tasks[i].pending_count < MAX_PENDING)
            {
                g_tasks[i].pending_count++;
                g_tasks[i].trigger_time = curr_time;
                g_tasks[i].deadline_time = curr_time + g_tasks[i].interval;
                last_trigger[i] = curr_time;
            }
        }

        chosen = FindHighestPriority();

        if (chosen != -1)
        {
            size_t curr_time = GetTimeInMs();

            if (curr_time > g_tasks[chosen].deadline_time)
            {
                g_tasks[chosen].deadline_misses++;
            }

            g_tasks[chosen].Handler(chosen);
            g_tasks[chosen].executions++;
            g_tasks[chosen].pending_count--;
        }

        SleepMs(TICK_MS);
    }
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
    ExitIfBad(0 == gettimeofday(&tv, NULL), "gettimeofday failed\n");

    return (size_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static int FindHighestPriority(void)
{
    int highest = -1;
    int i = 0;

    for (i = 0; i < MAX_TASKS; ++i)
    {
        if (g_tasks[i].pending_count > 0)
        {
            if (highest == -1 || g_tasks[i].priority < g_tasks[highest].priority)
            {
                highest = i;
            }
        }
    }
    return highest;
}

static void Task1Handler(int i)
{
    printf("Task %s executed!\n", g_tasks[i].name);
}

static void Task2Handler(int i)
{
    printf("Task %s executed!\n", g_tasks[i].name);
}

static void InitTasks(void)
{
    static const task_t init_tasks[MAX_TASKS] = 
    {
        {"Task1", TASK1_INTERVAL, PRIORITY_TASK1, Task1Handler, 0, 0, 0, 0, 0},
        {"Task2", TASK2_INTERVAL, PRIORITY_TASK2, Task2Handler, 0, 0, 0, 0, 0}
    };

    memcpy(g_tasks, init_tasks, sizeof(init_tasks));
}



