#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "watchdog.h"

static volatile sig_atomic_t g_should_stop = 0;

static void StopHandler(int sig)
{
    (void)sig;
    g_should_stop = 1;
}

int main(int argc, char *argv[])
{
    int status = 0;
    size_t ping_frequency = 0;
    size_t allowed_misses = 0;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <ping_frequency> <allowed_misses>\n", argv[0]);
        return 1;
    }

    /* פרסינג */
    ping_frequency = (size_t)atoi(argv[1]);
    allowed_misses = (size_t)atoi(argv[2]);

    /* סיגנלים */
    signal(SIGINT, StopHandler);
    signal(SIGTERM, StopHandler);

    /* חיבור ל-WD */
    status = MakeMeImmortal(allowed_misses, ping_frequency, argc, argv);
    if (0 != status)
    {
        fprintf(stderr, "MakeMeImmortal failed\n");
        return 1;
    }

    /* ריצה */
    while (!g_should_stop)
    {
        printf("wd_test is running...\n");
        sleep(1);
    }

    /* ניתוק מ-WD */
    status = DoNotResuscitate();
    if (0 != status)
    {
        fprintf(stderr, "DoNotResuscitate failed\n");
    }

    printf("wd_test is exiting gracefully.\n");
    return status;
}

