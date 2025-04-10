/***************************************
* Author : Natty
* Reviewer :
* File : shuffle_sort.c
* Version : 0.1  
* Date : 09 / 04 / 2025
* Last update: 09 / 04 / 2025
*****************************************/

#define _POSIX_C_SOURCE 200809L /* popen */

#include <stdio.h>      /* popen, pclose, FILE, sprintf, fscanf */
#include <sys/mman.h>   /* mmap, munmap */
#include <sys/stat.h>   /* fstat */
#include <fcntl.h>      /* open */
#include <unistd.h>     /* close */
#include <pthread.h>    /* pthread_create, join */
#include <string.h>     /* strcmp */
#include <sys/wait.h>   /* WIFEXITED, WEXITSTATUS */

#include "utils.h"

enum
{
    WORDS_LINE_SIZE = 104334,
    NUM_THREADS = 4,
    COPIES = 10,
    NULL_TERM_CH = '\0',
    NEW_LINE_CH = '\n'
                 
};

typedef void *(*th_func_ptr)(void* ); 
typedef int (*cmp_func_ptr)(const void* p1, const void* p2); 



typedef struct thread_meta_data
{
    unsigned char **chunk_base;
    size_t chunk_size;
    cmp_func_ptr CmpStrings;
 
}thread_meta_data_ty;

int CmpStrings(const void *p1, const void *p2)
{
    return strcmp(*(const unsigned char **)p1, *(const unsigned char **)p2);
}

static size_t CountLinesWithWC(const char *filename);

static int AllocResources(unsigned char ***arr_shuffled_word_ptrs,
    unsigned char ***arr_dest_sorted_ptrs, thread_meta_data_ty **th_data,
    pthread_t **arr_thread, int num_threads, size_t num_words);

int main(int argc, char **argv)
{
    /* phase start- define variables */
    int fd_dict = -1;
    int ret_fstat = -1;
    int init_ret = FAIL;
    int alloc_ret = FAIL;
    int num_threads = NUM_THREADS;
    int idx = 0;
    int cnt_merged_occure = 0;
    unsigned int result = 0;

    size_t num_words = 0;
    size_t total_words = 0;

    unsigned char *mmap_dict_ptr = MAP_FAILED;

    unsigned char **shuffled_word_ptrs = NULL;
    unsigned char **dest_sorted_ptrs = NULL;

    thread_meta_data_ty *threads_data = NULL;
    pthread_t *arr_thread = NULL; 


    struct stat st_dict= {0};
    RETURN_IF_BAD(argc >= 2, FAIL, "argv[1] missing");

    /* phase 0 - read dict into file(copy) using mmap */
    num_words = CountLinesWithWC(argv[1]);

    RETURN_IF_BAD(FAIL != num_words, FAIL, "CountLinesWithWC failed");

    fd_dict = open(argv[1], O_RDONLY);
    RETURN_IF_BAD(-1 != fd_dict, FAIL, "open failed");

    ret_fstat = fstat(fd_dict, &st_dict);
    RETURN_IF_BAD(-1 != ret_fstat, FAIL, "fstat failed");

    mmap_dict_ptr = (unsigned char*)mmap(NULL, st_dict.st_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE, fd_dict, 0);
    RETURN_IF_BAD(MAP_FAILED != mmap_dict_ptr, FAIL, "mmap failed");

    alloc_ret = AllocResources(&shuffled_word_ptrs, &dest_sorted_ptrs,
                 &threads_data, &arr_thread,  num_threads, num_words);

    RETURN_IF_BAD (FAIL != alloc_ret, FAIL, "AllocResources failed" );   
    
  
    

    return 0;
}

static size_t CountLinesWithWC(const char *filename)
{
    char cmd[50] = {0}; /* /usr/share/dict/words */
    FILE *fp = NULL;
    int status = 0;
    size_t num_lines = 0;

    sprintf(cmd, "wc -l %s", filename);
    fp = popen(cmd , "r");
    RETURN_IF_BAD(NULL != fp, FAIL, "popen failed");

    RETURN_IF_BAD(1 == fscanf(fp, "%lu", &num_lines), FAIL, "fscanf failed");

    status = pclose(fp);
    RETURN_IF_BAD(-1 != status, FAIL, "pclose failed");

    if (WIFEXITED(status))
    {
        int exit_code = WEXITSTATUS(status);
        RETURN_IF_BAD(0 == exit_code, FAIL, "wc command exited with failure");
    }

    else
    {
        RETURN_IF_BAD(0, FAIL, "wc command did not exit normally");
    }

    return num_lines;

}

static int AllocResources(unsigned char ***arr_shuffled_word_ptrs,
    unsigned char ***arr_dest_sorted_ptrs, thread_meta_data_ty **th_data,
    pthread_t **arr_thread, int num_threads, size_t num_words)
 
{
    *arr_shuffled_word_ptrs = 
        (unsigned char **)calloc(num_words * COPIES, sizeof(unsigned char *) );

    if(!(*arr_shuffled_word_ptrs))
    {
        RETURN_IF_BAD(FALSE, FAIL, "calloc word_ptrs failed");
    }

    *arr_dest_sorted_ptrs =
        (unsigned char **)calloc(num_words * COPIES, sizeof(unsigned char *));

    if(!(*arr_dest_sorted_ptrs))
    {
        free(*arr_shuffled_word_ptrs);
        RETURN_IF_BAD(FALSE, FAIL , "calloc arr_dest failed");
    }


    *th_data = (thread_meta_data_ty*)calloc(num_threads, sizeof(thread_meta_data_ty));

    if(!(*th_data))
    {
        free(*arr_shuffled_word_ptrs);
        free(*arr_dest_sorted_ptrs);

        RETURN_IF_BAD(FALSE, FAIL, "calloc th_data failed");
    }

    *arr_thread = (pthread_t*)calloc(num_threads, sizeof(pthread_t));

    if(!(*arr_thread))
    {
        free(*arr_shuffled_word_ptrs);
        free(*arr_dest_sorted_ptrs);
        free(*th_data);

        RETURN_IF_BAD(FALSE, FAIL, "calloc arr_thread failed");
    }

    return SUCCESS;
}


/* phase 1- Allocate Resources */
    /* AllocResources(...)*/
    
    /* phase 2 - counting the num_words and swappign '\n' to '\0' */
    /* num_words = CountWordsAndReplaceNewLine(mmap_dict_ptr, st_dict.st_size) */
        /* num_words= popen("wc -l") / system() */
        
        /* foreach idx from 0 to num_word */
            /* if '\n' == *(mmap_dict_ptr + idx ) */
                /* *(mmap_dict_ptr + idx ) = '\0' */

    /* phase 3 - Create arary of pointers to the words array 
                and assign the pointers in the array according to 
                the numbert of each word */
    /* arr_of_ptrs = CreateArrPtrsAndAssignedPtrWords(mmap_dict_ptr, num_words )*/

    /* phase 4 - Duplicate the arr_of_ptrs 10 times */
    /* arrs_10_of_ptrs = DuplicatePointersArr10Times(arr_of_ptrs, num_words, 10)*/
    
    /* phase 5 - Shuffle the arr_of_ptrs 10 times by using function that
        do randomizing to the full array. insert this function to quick sort
        in the argument of the comp_func */
    /* ShuffleDupllicateArray(arrs_10_of_ptrs, num_words, 10) */

    /* phase 6 -  Sorting the full array by using threads */
        /* InitThreadMetaData(thread_meta_data_ty *th_data, char *mmap_dict_ptr,
             arrs_10_of_ptrs, int num_threads, size_t file_size)*/

    /* phase 7 -  Sorting the full array by using threads */
    /* LaunchSortingThreads(arrs_10_of_ptrs, mmap_dict_ptr,
       num_words*10,  num_threads, threads_data , quicksort) */

    /* phase 8 - Merging the sorting results */
    /* MergeSortedSections(arr_sorted, arrs_10_of_ptrs, num_words * 10,
     threads_data, num_thread ) */

    /* phase 9 - Print and Measure result of time complexity */
    /* PrintAndMeasuresResults(...) */

        /* phase 10 - Free and clean all resources */
        /* FreeResources(...) */
