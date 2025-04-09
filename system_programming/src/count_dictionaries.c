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
    CACHE_PADDED_HIST_SIZE = NUM_ASCII_CHARS + CACHE_LINE_SIZE,
    NUM_THREADS = 4
                 
};

typedef struct aligned_hist
{
    size_t hist[NUM_ASCII_CHARS];
    char padding[CACHE_LINE_SIZE];

}aligned_hist_ty;


typedef struct thread_meta_data
{
    char *start_chunk_ptr;
    char *end_chunk_ptr;
    size_t *thread_histogram_ptr;

}thread_meta_data_ty;

typedef void *(*th_func_ptr)(void* ); 

static int AllocResources(size_t **main_hist, size_t **local_hists,
            thread_meta_data_ty **th_data, int num_threads);

static void InitThreadMetaData(thread_meta_data_ty *th_data, char *mmap_dict_ptr,
    size_t *local_hists, int num_threads, size_t file_size);


/*functions defenition*/
    /* CountNumOfWordsInDictFile(char *dict_ptr, size_t dict_size) */
    /* NumOfDictCopies(char *dict_ptr, size_t dict_size, num_word) */
    /* InitThreadMetaData(th_data, num_word, num_thread, start_ptr_dict) */
    /* CountCharInInterval_TH(thread_data_t *th_data[] )*/


int main(int argc, char **argv)
{
    char *mmap_dict_ptr = MAP_FAILED;
    int fd_dict = -1;
    int ret_fstat = -1;
    int init_ret = FAIL;
    int alloc_ret = FAIL;
    int num_threads = NUM_THREADS;

    thread_meta_data_ty *threads_data = NULL;
    size_t *main_histogram = NULL;
    size_t *local_histograms = NULL;

    struct stat st_dict= {0};

    RETURN_IF_BAD(argc >= 2, FAIL, "argv[1] missing");

    fd_dict = open(argv[1], O_RDONLY);
    RETURN_IF_BAD(-1 != fd_dict, FAIL, "open failed");

    ret_fstat = fstat(fd_dict, &st_dict);
    RETURN_IF_BAD(-1 != ret_fstat, FAIL, "fstat failed");

    mmap_dict_ptr = mmap(NULL, st_dict.st_size, PROT_READ, MAP_PRIVATE, fd_dict, 0);
    RETURN_IF_BAD(MAP_FAILED != mmap_dict_ptr, FAIL, "mmap failed");

    alloc_ret = AllocResources(&main_histogram, &local_histograms,
                 &threads_data, num_threads);
    RETURN_IF_BAD (FAIL != alloc_ret, FAIL, "AllocResources failed" );

    InitThreadMetaData(threads_data, mmap_dict_ptr, 
            local_histograms, num_threads, st_dict.st_size);

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
        
    RETURN_IF_BAD(-1 != munmap(mmap_dict_ptr, st_dict.st_size), FAIL, "munmap failed")
    RETURN_IF_BAD(-1 != close(fd_dict), FAIL, "close failed")

    return 0;
}

static int AllocResources(size_t **main_hist, size_t **local_hists,
    thread_meta_data_ty **th_data, int num_threads)
{
    *local_hists = (size_t*)calloc(num_threads, sizeof(aligned_hist_ty));

    if(!(*local_hists))
    {
        RETURN_IF_BAD(FALSE, FAIL, "calloc local_hists failed");
    }

    *main_hist = (size_t*)calloc(1, NUM_ASCII_CHARS);

    if(!(*main_hist))
    {
        free(*local_hists);
        RETURN_IF_BAD(NULL != main_hist,FAIL , "calloc main_hist failed");
    }

    *th_data = (thread_meta_data_ty*)calloc(num_threads, sizeof(thread_meta_data_ty));

    if(!(*th_data))
    {
        free(*local_hists);
        free(*main_hist);

        RETURN_IF_BAD(FALSE, FAIL, "calloc th_data failed");
    }

    return SUCCESS;
}    
    
static void InitThreadMetaData(thread_meta_data_ty *th_data, char *mmap_dict_ptr,
             size_t *local_hists, int num_threads, size_t file_size)
{
    size_t chunk_size_block = file_size / num_threads;
    int idx = 0;

    for(idx = 0; idx < num_threads; ++idx)
    {
        (th_data + idx)->start_chunk_ptr = mmap_dict_ptr + idx * chunk_size_block;

        if(idx == num_threads-1)
        {
            (th_data + idx)->end_chunk_ptr = mmap_dict_ptr + file_size;
        }
        
        else
        {
            (th_data + idx)->end_chunk_ptr = 
            (th_data + idx)->start_chunk_ptr + chunk_size_block;
        }

        (th_data + idx)->thread_histogram_ptr = 
            local_hists + idx * CACHE_PADDED_HIST_SIZE;   
        
    }

}

void *CountCharInInterval_TH(thread_meta_data_ty *data)
{

}    