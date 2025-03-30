/***************************************
 * Author : Natty
 * Reviewer : 
 * Date : 26 / 03 / 2025
 * Last update: 30 / 03 / 2025
 *****************************************/

#ifndef WATCHDOG_H      /* WATCHDOG_H */
#define WATCHDOG_H      /* WATCHDOG_H */

/*client and watchdog save this instace struct to collet info/status on each other 
during their communication */


int MakeMeImmortal(void *argv, info_ty *info, int max_misses, int interval_sec);
void DoNotResuscitate(void *argv, info_ty *info);

#endif /* WATCHDOG_H */

