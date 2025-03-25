/***************************************
 * Author : Natty
 * Reviewer : ?
 * Date : 25 / 03 / 2025
 * Last update: 25 / 03 / 2025
 *****************************************/

#include <stdio.h>       
#include <stdint.h>

enum
{
    MAX_TASKS = 3,
    SMOKE_INTERVAL = 100, /* Time interval to check the trigger */
    EMERGENCY_INTERVAL = 1000,
    TICK_MS = 10,   /* timer - every TICK_MS the app wake up and do checks*/
    MAX_PENDING = 10 
    
};

typedef struct task
{
    char name[20];          /*name of the task/event */
    uint16_t interval;      /* The differece of each trigger checking */
    uint8_t priority;       /*priority of the task */
    size_t trigger_time;    /*when the event requesed */
    size_t deadline_time;   /* Maximum time the task should be complete*/
    uint8_t pending_count;  /* How much requests of the task/event */



}task_t;


int main()
{
    
    return 0;
}




