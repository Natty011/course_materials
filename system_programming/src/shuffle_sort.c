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

enum
{
    CACHE_LINE_SIZE = 64,
    NUM_THREADS = 4
                 
};

typedef struct aligned_hist
{
    size_t section_len_sort[LEN_TO_SORT];
    char padding[CACHE_LINE_SIZE];

}aligned_hist_ty;


typedef struct thread_meta_data
{
    char *start_chunk_ptr;
    char *end_chunk_ptr;
    size_t *thread_sort_ptr;

}thread_meta_data_ty;

typedef void *(*th_func_ptr)(void* ); 

int main(int argc, char **argv)
{
    /* phase start- define variables */

    /* phase 0- Allocate Resources */
    /* AllocResources(...)*/
    

    /* phase 1 - read dict into file(copy) using mmap */
    /* mmap_dict_ptr = MmapDictFile(argv[1], &file_size)
        /* fd_dict = open(argv[1], O_RDONLY); */
        /* ret_fstat = fstat(fd_dict, &st_dict); */
        /* mmap_dict_ptr = mmap(NULL, st_dict.st_size,
                     PROT_READ, MAP_PRIVATE, fd_dict, 0);*/

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
    /* MergeSortedSections(arrs_10_of_ptrs, num_words * 10,
     threads_data, num_thread ) */

    /* phase 9 - Print and Measure result of time complexity */
    /* PrintAndMeasuresResults(...) */

        /* phase 10 - Free and clean all resources */
        /* FreeResources(...) */
    return 0;
}
