#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "watchdog.h"

int main(void)
{
    info_ty wd_info = {0};

    printf("[App] Starting MakeMeImmortal...\n");
    if (MakeMeImmortal(NULL, &wd_info, 3, 2) != 0)
    {
        perror("MakeMeImmortal failed");
        return 1;
    }
	puts("hii");
    printf("[App] Watchdog is alive. PID: %d\n", getpid());
    printf("[App] Simulating some work...\n");

    sleep(10);

    printf("[App] Calling DoNotResuscitate...\n");
    DoNotResuscitate(NULL, &wd_info);

    printf("[App] Exiting cleanly.\n");
    return 0;
}

