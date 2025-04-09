/***************************************
* Author : Natty
* Reviewer :
* File : count_dictionaries.c
* Version : 0.7  
* Date : 08 / 04 / 2025
* Last update: 09 / 04 / 2025
*****************************************/
#include <stdio.h>
#include <sys/mman.h>   /* mmap, munmap */
#include <sys/stat.h>   /* fstat */
#include <fcntl.h>      /* open */
#include <unistd.h>     /* close */

#include "utils.h"

enum
{
    NUM_ASCII_CHARS  = 256,
    CACHE_LINE_SIZE = 64,
    NUM_THREADS = 4
                 
};

typedef struct aligned_hist
{
    size_t hist[NUM_ASCII_CHARS];
    char padding[CACHE_LINE_SIZE];

}aligned_hist_ty;


typedef struct thread_meta_data
{
    char *start_word_ptr;
    char *end_word_ptr;
    size_t *thread_histogram_ptr;

}thread_meta_data_ty;

typedef void *(*th_func_ptr)(void* ); 

/*functions defenition*/
    /* CountNumOfWordsInDictFile(char *dict_ptr, size_t dict_size) */
    /* NumOfDictCopies(char *dict_ptr, size_t dict_size, num_word) */
    /* InitThreadMetaData(th_data, num_word, num_thread, start_ptr_dict) */
    /* CountCharInInterval_TH(thread_data_t *th_data[] )*/


int main(int argc, char **argv)
{
    char *mmap_dict_ptr = NULL;
    int fd_dict = -1;
    int ret_fstat = -1;
    int num_threads = NUM_THREADS;
    thread_meta_data_ty **threads_data = NULL;
    size_t *main_histogram = NULL;
    size_t *local_histograms = NULL;

    struct stat st_dict= {0};

    RETURN_IF_BAD(argc >= 2, FAIL, "argv[1] missing\n")

    fd_dict = open(argv[1], O_RDONLY);
    RETURN_IF_BAD(-1 != fd_dict, FAIL, "open failed\n")

    ret_fstat = fstat(fd_dict, &st_dict);
    RETURN_IF_BAD(-1 != ret_fstat, FAIL, "fstat failed\n")

    mmap_dict_ptr = mmap(NULL, st_dict.st_size, PROT_READ, MAP_PRIVATE, fd_dict, 0);
    RETURN_IF_BAD(MAP_FAILED != mmap_dict_ptr, FAIL, "mmap failed\n");

    local_histograms = (size_t*)calloc(num_threads, sizeof(aligned_hist_ty));
    RETURN_IF_BAD(NULL != local_histograms, FAIL, "calloc failed\n");

    main_histogram = (size_t*)calloc(1, NUM_ASCII_CHARS);
    RETURN_IF_BAD(NULL != main_histogram, FAIL, "calloc failed\n");

    /* local_hist[num_thread][NUM_LETTERS]*/
    /* thread_data_t th_data[num_thread] */
    /* pthread_t arr_thread[num_thread] */

    /* InitThreadMetaData(th_data, num_word, num_thread, start_ptr_dict) */

    
    /* for i from 0 to num_thread - 1*/
        /* pthread_t pthread_create(arr_thread[i], (th_func_ptr)CountCharInInterval_TH, th_data[i] )*/

    /* for i from 0 to num_thread - 1*/
        /* join_thread(arr_thread[i])*/

    /* for i from 0 to num_thread - 1*/
        /* for J from 0 to NUM_LETTERS*/
            /*main_hist[j] += local_hist[i][j] */
        
    RETURN_IF_BAD(-1 != munmap(mmap_dict_ptr, st_dict.st_size), FAIL, "munmap failed\n")
    RETURN_IF_BAD(-1 != close(fd_dict), FAIL, "close failed\n")

    return 0;
}

void InitThreadMetaData(thread_meta_data_ty *th_data, size_t num_threads,
    char *dict_ptr, size_t file_size)
{


}

void *CountCharInInterval_TH(thread_meta_data_ty *data)
{

}    