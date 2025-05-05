#include <stdio.h>
#include "watchdog.h"

int MakeMeImmortal(void *args, info_ty *info, int max_misses, int interval_sec)
{
    (void)args;
    (void)info;
    (void)max_misses;
    (void)interval_sec;
	puts("hell");
    printf("[WD LIB] MakeMeImmortal stub called.\n");
    return 0;
}

void DoNotResuscitate(void *args, info_ty *info)
{
    (void)args;
    (void)info;

    printf("[WD LIB] DoNotResuscitate stub called.\n");
}
