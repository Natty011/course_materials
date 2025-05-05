#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "watchdog.h"

/* Dummy implementation of MakeMeImmortal */
int MakeMeImmortal(size_t allowed_misses, size_t ping_frequency, char **argv)
{
    (void)allowed_misses;
    (void)ping_frequency;
    (void)argv;

    printf("[MakeMeImmortal] Dummy: initializing watchdog mechanism...\n");
    return 0; /* success */
}

/* Dummy implementation of DoNotResuscitate */
int DoNotResuscitate(void)
{
    printf("[DoNotResuscitate] Dummy: cleaning up and stopping watchdog...\n");
    return 0; /* success */
}

/* Already in your app.c, but place it here if you move to final location */
void RunAsWatchdog(void)
{
    printf("[RunAsWatchdog] Dummy: this is the watchdog process\n");
    exit(0);
}

