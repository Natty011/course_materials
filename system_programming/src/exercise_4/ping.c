#define _POSIX_C_SOURCE 199309L /*struct sigaction*/

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, atoi */
#include <unistd.h>     /* sleep, kill */
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* waitpid */
#include <signal.h>     /* sigaction */
#include <errno.h>      /* errno */

volatile sig_atomic_t is_on_ping = 0;
int cycle_count = 0;
pid_t pong_pid;

static void handle_signal(int sig)
{
    if (sig == SIGUSR1)
    {
        is_on_ping = 1;
    }
    else if (sig == SIGTERM || sig == SIGCHLD) // אם pong נסגר, ping יוצא
    {
        printf("Ping: Detected Pong process termination (SIGTERM/SIGCHLD), exiting...\n");
        waitpid(-1, NULL, WNOHANG);  // מנקה זומבי אם קיים
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <pong_pid>\n", argv[0]);
        exit(1);
    }

    pong_pid = atoi(argv[1]);

    struct sigaction sa = {0};
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGCHLD, &sa, NULL);  // מעקב אחרי סיום תהליכים

    printf("Ping process started with PID: %d, communicating with Pong PID: %d\n", getpid(), pong_pid);

    while (cycle_count < 3)
    {
        // בדיקה אם pong עדיין חי
        if (kill(pong_pid, 0) == -1 && errno == ESRCH)  // ESRCH -> no such process
        {
            printf("Ping: Pong process (PID: %d) is gone (kill check), exiting...\n", pong_pid);
            exit(0);
        }

        while (!is_on_ping)
        {
            sleep(1);
        }

        printf("Ping: Received SIGUSR1 from Pong, sending SIGUSR2\n");
        kill(pong_pid, SIGUSR2);
        is_on_ping = 0; // איפוס הדגל
        cycle_count++;
    }

    printf("Ping: Reached 3 cycles, exiting...\n");
    return 0;
}

