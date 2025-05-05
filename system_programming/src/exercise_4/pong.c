/***************************************
 * Author : Natty
 * Reviewer : ???
 * Date : 05 / 03 / 2025
 * Last update: 12 / 03 / 2025
 ***************************************/

 #define _POSIX_C_SOURCE 199309L /*struct sigaction*/

 #include <stdio.h>      /* printf */
 #include <stdlib.h>     /* exit, atoi */
 #include <unistd.h>     /* sleep, kill */
 #include <sys/types.h>  /* pid_t */
 #include <signal.h>     /* sigaction */
 
 volatile sig_atomic_t is_on_pong = 0;
 int cycle_count = 0;
 pid_t ping_pid;
 
 static void handle_signal(int sig)
 {
     if (sig == SIGUSR2)
     {
         is_on_pong = 1;
     }
 }
 
 int main(int argc, char *argv[])
 {
     if (argc != 2)
     {
         fprintf(stderr, "Usage: %s <ping_pid>\n", argv[0]);
         exit(1);
     }
 
     ping_pid = atoi(argv[1]);
 
     struct sigaction sa = {0};
     sa.sa_handler = handle_signal;
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
     sigaction(SIGUSR2, &sa, NULL);
 
     printf("Pong process started with PID: %d, communicating with Ping PID: %d\n", getpid(), ping_pid);
 
     sleep(1); // מחכה שה-Ping יהיה מוכן
 
     printf("Pong: Sending SIGUSR1 to Ping\n");
     kill(ping_pid, SIGUSR1);
 
     while (cycle_count < 3)
     {
         while (!is_on_pong)
         {
             sleep(1);
         }
 
         printf("Pong: Received SIGUSR2 from Ping, sending SIGUSR1\n");
         kill(ping_pid, SIGUSR1);
         is_on_pong = 0; // איפוס הדגל
         cycle_count++;
     }
 
     printf("Pong: Reached 3 cycles, terminating Ping...\n");
     kill(ping_pid, SIGTERM);
     printf("Pong: Exiting...\n");
     return 0;
 }
 