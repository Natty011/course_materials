/***************************************
* Author : Natty
* Reviewer :
* File : shuffle_sort.c
* Version : 0.1  
* Date : 09 / 04 / 2025
* Last update: 09 / 04 / 2025
*****************************************/
#include <stdio.h>
#include <sys/mman.h>   /* mmap, munmap */
#include <sys/stat.h>   /* fstat */
#include <fcntl.h>      /* open */
#include <unistd.h>     /* close */
#include <pthread.h>    /* pthread_create, join */

#include "utils.h"