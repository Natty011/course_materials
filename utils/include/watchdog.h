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


int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency,int argc, char** argv);
int DoNotResuscitate(void);
#endif /* WATCHDOG_H */
 
