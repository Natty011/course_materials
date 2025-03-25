/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 25 / 03 / 2025
 * Last update: 25 / 03 / 2025
 *****************************************/

#include <stdio.h>  /* printf */     
#include <stdint.h> /* uint8_t, uint16_t, uint32_t*/
#include <stdlib.h> /* rand */

enum
{
    MAX_TASKS = 3,
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
typedef void (*handler_t)(size_t time_detaction, const char* name);

static void InitTasks(void);
static int TriggerSmoke(void);
static int TriggerEmergency(void);

static void HandlerSmoke(int chosen_tesk);
static void HandlerEmergecy(int chosen_tesk);


typedef struct task
{
    char name[20];          /*name of the task */
   
    uint16_t interval;      /*The interval of each trigger checking  */
    uint8_t priority;       /*priority of the task */

    is_trigger_t IsTrigger; /* return if trigger occered */
    handler_t Handler;      /*Handle the task if it triggered */

    size_t trigger_time;    /*when the task requested/triggered */
    size_t deadline_time;   /*Maximum time the task should be complete*/
    size_t response_time;   /*How long pass from the trigger */
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
    
    return 0;
}

static void InitTasks(void)
{
    g_tasks[0] = (task_t){"Smoke1", SMOKE_INTERVAL, PRIORITY_SMOKE1, TriggerSmoke,
         HandlerSmoke, 0, 0, 0, 0, 0, 0, 0};

    g_tasks[1] = (task_t){"Smoke2", SMOKE_INTERVAL, PRIORITY_SMOKE2, TriggerSmoke,
        HandlerSmoke, 0, 0, 0, 0, 0, 0, 0};
        
    g_tasks[2] = (task_t){"Emergency", EMERGENCY_INTERVAL, PRIORITY_EMERGENCY,
        TriggerEmergency, HandlerEmergecy, 0, 0, 0, 0, 0, 0, 0};    
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
    --g_tasks[chosen_tesk].pending_count;
    
}

static void HandlerEmergecy(int chosen_tesk)
{
    --g_tasks[chosen_tesk].pending_count;
}
