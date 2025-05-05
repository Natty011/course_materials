/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 26 / 03 / 2025
 * Last update: 30 / 03 / 2025
 *****************************************/

#ifndef WATCHDOG_H      /* WATCHDOG_H */
#define WATCHDOG_H      /* WATCHDOG_H */

typedef struct info
{
    
    int dummy;

} info_ty;

int i = 0;

int MakeMeImmortal(void *args, info_ty *info, int max_misses, int interval_sec);
void DoNotResuscitate(void *args, info_ty *info);

#endif /* WATCHDOG_H */

