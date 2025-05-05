#include <stdio.h>      /* printf */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <unistd.h>     /* sleep */
#include "watchdog.h"   /* MakeMeImmortal, DoNotResuscitate */
/*./wd_test.out 3 5 */
int main(int argc, char *argv[])
{
    size_t ping_freq = 3;
    size_t allowed_misses = 5;
    size_t i = 0;

    /* אם רוצים להעביר פרמטרים מהפקודה */
    if (argc >= 3)
    {
        ping_freq = (size_t)atoi(argv[1]);
        allowed_misses = (size_t)atoi(argv[2]);
    }

    printf("==[wd_test.out]== Started. My PID: %d\n", getpid());

    if (0 != MakeMeImmortal(allowed_misses, ping_freq, argc, argv))
    {
        perror("MakeMeImmortal failed");
        return 1;
    }

    /* סימולציה של עבודה רגילה */
    for (i = 0; i < 20; ++i)
    {
        printf("==[wd_test.out]== Working... [%lu]\n", (unsigned long)i);
        sleep(1);
    }

    /* מבקש להפסיק את השמירה (DNR) */
    if (0 != DoNotResuscitate())
    {
        perror("DoNotResuscitate failed");
        return 1;
    }

    printf("==[wd_test.out]== Done.\n");
    return EXIT_SUCCESS;
}

