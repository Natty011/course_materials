#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "watchdog.h"


static volatile sig_atomic_t g_should_stop = 0;
/*
static void StopHandler(int sig)
{
    (void)sig;
    g_should_stop = 1;
}

static void PingHandler(int sig)
{
    (void)sig;
    printf("[client] Got SIGUSR1 from watchdog\n");
}
*/
int main(int argc, char *argv[])
{
    int status = 0;
    size_t ping_frequency = 0;
    size_t allowed_misses = 0;
    int i = 0;
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <ping_frequency> <allowed_misses>\n", argv[0]);
        return 1;
    }

    /* Parse command-line arguments */
    ping_frequency = (size_t)atoi(argv[1]);
    allowed_misses = (size_t)atoi(argv[2]);

    for (i = 0; argv[i] != NULL; ++i)
    {
        fprintf(stderr, "[wd_test] argv[%d] = %s\n", i, argv[i]);
    }

    /* Signal handlers */
    /*signal(SIGINT, StopHandler);
    signal(SIGTERM, StopHandler);
    signal(SIGUSR1, PingHandler);*/

    printf("[client] Calling MakeMeImmortal...\n");
    puts("[TEST] about to enter MMI");

    /* Connect to watchdog */
    status = MakeMeImmortal(allowed_misses, ping_frequency, argc, argv);
    if (0 != status)
    {
        fprintf(stderr, "MakeMeImmortal failed\n");
        return 1;
    }

    printf("[client] Running main loop.\n");

    while (!g_should_stop)
    {
        printf("[client] Still alive!\n");
        sleep(1);
    }

    printf("[client] Calling DoNotResuscitate...\n");
    status = DoNotResuscitate();
    if (0 != status)
    {
        fprintf(stderr, "DoNotResuscitate failed\n");
    }

    printf("[client] Exiting gracefully.\n");
    return status;
}
