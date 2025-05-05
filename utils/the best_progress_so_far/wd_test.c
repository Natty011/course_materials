#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include "watchdog.h"

static volatile sig_atomic_t g_should_stop = 0;

int main(int argc, char *argv[])
{
    int i = 0;
    printf("[wd_test] argc= %d \n", argc);

    assert(argc >= 4);

    fprintf(stderr, "[CLIENT] (pid: %d)\n", getpid());

    for (i = 0; i < argc; ++i)
    {
        printf("[wd_test] argv[%d] = %s\n", i, argv[i]);
    }
    

    printf("[client] Calling MakeMeImmortal...\n");
    MakeMeImmortal((size_t)atoi(argv[1]), (size_t)atoi(argv[2]), argc, argv);

    printf("[client] Running main loop.\n");

    for (i = 0; i < 20; ++i)
    {
        
        fprintf(stderr, "[CLIENT] watchdog_app (pid: %d)\n", getpid());

        /*kill(getppid(), SIGKILL); *//* simulate crash of the WD_APP */

        printf("[client] Still alive! (%d)\n", i + 1);
        sleep(1);
    }

    printf("[client] Simulating crash with exit(1)...\n");
    exit(1); /* simulate crash */
}

