/***************************************
* Author : Natty
* Reviewer :
* File : shuffle_sort.c
* Version : 0.1  
* Date : 09 / 04 / 2025
* Last update: 09 / 04 / 2025
*****************************************/

#define _POSIX_C_SOURCE 200809L /* popen */
#define _GNU_SOURCE 1           /* pthread_tryjoin_np */

#include <stdio.h>      /* popen, pclose, FILE, sprintf, fscanf */
#include <stdlib.h>     /* rand, srand, qsort */
#include <sys/mman.h>   /* mmap, munmap */
#include <sys/stat.h>   /* fstat */
#include <fcntl.h>      /* open */
#include <unistd.h>     /* close */
#include <pthread.h>    /* pthread_create, join_try_np */
#include <string.h>     /* strcmp, memcpy */
#include <sys/wait.h>   /* WIFEXITED, WEXITSTATUS */
#include <time.h>       /* time */
#include "utils.h"

enum
{
    WORDS_LINE_SIZE = 104334,
    NUM_THREADS = 4,
    COPIES = 10,
    NULL_TERM_CH = '\0',
    NEW_LINE_CH = '\n'
                 
};

static size_t g_num_words = 0;
    /* תחילה – מגדירים גבולות עבודה סטטיים */
static unsigned char **g_start_of_result = NULL;
static unsigned char **g_end_of_dest_array = NULL;
static size_t g_current_result_len = 0;

typedef void *(*th_func_ptr)(void* ); 
typedef int (*cmp_func_ptr)(const void* p1, const void* p2); 



typedef struct thread_meta_data
{
    unsigned char **chunk_base;
    size_t chunk_size;
    cmp_func_ptr CmpStrings;
 
}thread_meta_data_ty;



static size_t CountLinesWithWC(const char *filename);

static int AllocResources(unsigned char ***arr_shuffled_word_ptrs,
        unsigned char ***arr_dest_sorted_ptrs, thread_meta_data_ty **th_data,
        pthread_t **arr_thread, int num_threads, size_t g_num_words);

static int FillWordsPointers(unsigned  char* mmap_dict,
        unsigned char **words_ptrs, size_t g_num_words);

static void FreeResources(unsigned char **word_ptrs, unsigned char **sorted_ptrs,
            thread_meta_data_ty *th_data, pthread_t *arr_thread);

static int RandomCmp(const void *a, const void *b);

void ShuffleArray(unsigned char **word_ptrs, size_t total_words); 

int CmpStrings(const void *p1, const void *p2);

static void InitThreadChunks(unsigned char **word_ptrs, thread_meta_data_ty *th_data,
            int num_threads, size_t total_words); 

void *SortChunk_TH(thread_meta_data_ty *thread_data);

int RunAndMergeThreads(unsigned char **dest_sorted_ptrs,
    thread_meta_data_ty *th_data,
    pthread_t *arr_thread,
    int num_threads);

int MergeSortedChunks(thread_meta_data_ty *th_data);

static int ValidateSortedOutput(unsigned char **sorted_ptrs, size_t total_words, size_t copies);
int main(int argc, char **argv)
{
    /* phase start- define variables */
    int fd_dict = -1;
    int ret_fstat = -1;
    int ret = FAIL;
    int num_threads = NUM_THREADS;
    unsigned int result = 0;


    unsigned char *mmap_dict_ptr = MAP_FAILED;

    unsigned char **words_ptrs = NULL;
    unsigned char **sorted_ptrs = NULL;

    thread_meta_data_ty *threads_data = NULL;
    pthread_t *arr_thread = NULL; 

    struct stat st_dict= {0};
    clock_t start_time = clock();
    clock_t end_time = clock();
    double elapsed = 0.0;

    RETURN_IF_BAD(argc >= 2, FAIL, "argv[1] missing");

    srand(time(NULL));

    /* phase 0 - read dict into file(copy) using mmap */
    g_num_words = CountLinesWithWC(argv[1]);

    RETURN_IF_BAD(FAIL != g_num_words, FAIL, "CountLinesWithWC failed");

    fd_dict = open(argv[1], O_RDONLY);
    RETURN_IF_BAD(-1 != fd_dict, FAIL, "open failed");

    ret_fstat = fstat(fd_dict, &st_dict);
    RETURN_IF_BAD(-1 != ret_fstat, FAIL, "fstat failed");

    mmap_dict_ptr = (unsigned char*)mmap(NULL, st_dict.st_size, 
        PROT_READ | PROT_WRITE, MAP_PRIVATE, fd_dict, 0);
    RETURN_IF_BAD(MAP_FAILED != mmap_dict_ptr, FAIL, "mmap failed");

    ret = AllocResources(&words_ptrs, &sorted_ptrs,
                 &threads_data, &arr_thread,  num_threads, g_num_words);

    RETURN_IF_BAD (FAIL != ret, FAIL, "AllocResources failed" );   
    
    ret = FillWordsPointers(mmap_dict_ptr, words_ptrs, g_num_words);

    if(FAIL == ret)
    {
        FreeResources(words_ptrs, sorted_ptrs, threads_data, arr_thread);
        RETURN_IF_BAD (FALSE, FAIL, "FillWordsPointers failed" );   
    }

    ShuffleArray(words_ptrs, g_num_words*COPIES);

    InitThreadChunks(words_ptrs, threads_data, num_threads, g_num_words*COPIES);

    start_time = clock();
    result = RunAndMergeThreads(sorted_ptrs, threads_data, arr_thread, num_threads);
    
    if(FAIL == result)
    {
        FreeResources(words_ptrs, sorted_ptrs, threads_data, arr_thread);
        RETURN_IF_BAD (FALSE, FAIL, "RunAndMergeThreads failed" );   
    }

    end_time = clock();
    elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken for sorting and merging with %d threads: %.6f seconds\n", num_threads, elapsed);

    result = ValidateSortedOutput(sorted_ptrs, g_num_words * COPIES, COPIES);
    if(FAIL == result)
    {
        FreeResources(words_ptrs, sorted_ptrs, threads_data, arr_thread);
        RETURN_IF_BAD (FALSE, FAIL, "Validation of sorted output failed" );   
    }

    /*memmove(sorted_ptrs, g_start_of_result, 
        (g_end_of_dest_array - g_start_of_result) * sizeof(unsigned char *));*/

    /*qsort(sorted_ptrs, g_num_words * COPIES, sizeof(unsigned char *), CmpStrings);*/

    FreeResources(words_ptrs, sorted_ptrs, threads_data, arr_thread);
    RETURN_IF_BAD(-1 != munmap(mmap_dict_ptr, st_dict.st_size), FAIL, "munmap failed")
    RETURN_IF_BAD(-1 != close(fd_dict), FAIL, "close failed")

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
    pthread_t **arr_thread, int num_threads, size_t g_num_words)
 
{
    *arr_shuffled_word_ptrs = 
        (unsigned char **)calloc(g_num_words * COPIES, sizeof(unsigned char *) );

    if(!(*arr_shuffled_word_ptrs))
    {
        RETURN_IF_BAD(FALSE, FAIL, "calloc word_ptrs failed");
    }

    *arr_dest_sorted_ptrs =
        (unsigned char **)calloc(g_num_words * COPIES, sizeof(unsigned char *));

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

static int FillWordsPointers(unsigned  char* mmap_dict,
                            unsigned char **words_ptrs, size_t g_num_words)

{
    unsigned char* runner = mmap_dict;
    unsigned char* word_start = mmap_dict;
    size_t word_idx = 0;
    size_t copy_idx = 0;


    while((word_idx < g_num_words) )
    {
        if(NEW_LINE_CH == *runner)
        {
            *runner = NULL_TERM_CH;
            *(words_ptrs + word_idx) = word_start;
            
            ++word_idx;
            word_start = runner + 1;
        }

        ++runner;

    }
    /* copy the first array to the next 9 arraies*/
    RETURN_IF_BAD(word_idx == g_num_words, FAIL, "word count in FillWords: failed");

    for(copy_idx = 1; copy_idx < COPIES; ++copy_idx)
    {
        memcpy(words_ptrs + copy_idx*g_num_words, words_ptrs,
             g_num_words*sizeof(unsigned char*));
    }

    return SUCCESS;
}

static void FreeResources(unsigned char **word_ptrs, unsigned char **sorted_ptrs,
    thread_meta_data_ty *th_data, pthread_t *arr_thread)
{
 
    free(word_ptrs);
    free(sorted_ptrs);
    free(th_data);
    free(arr_thread);
}

/* Random comparator for qsort  */

static int RandomCmp(const void *a, const void *b)
{
    (void)a;
    (void)b;
    return rand() % 3 - 1; /* returns -1, 0, or 1 randomly */
}

/* Shuffle function using qsort and random comparator */

void ShuffleArray(unsigned char **word_ptrs, size_t total_words)
{
    qsort(word_ptrs, total_words, sizeof(unsigned char *), RandomCmp);
}


int CmpStrings(const void *p1, const void *p2)
{
    return strcmp(*(const char **)p1, *(const char **)p2);
}
  
static void InitThreadChunks(unsigned char **word_ptrs, thread_meta_data_ty *th_data,
                            int num_threads, size_t total_words)
{
    size_t chunk_size_block = total_words / num_threads;
    size_t remainder = total_words % num_threads;

    int idx = 0;

    for(idx = 0; idx < num_threads; ++idx)
    {
        (th_data + idx)->chunk_base = word_ptrs + idx * chunk_size_block;
        (th_data + idx)->CmpStrings = CmpStrings;

        if(idx == num_threads-1)
        {
            (th_data + idx)->chunk_size = chunk_size_block + remainder;
        }

        else
        {
            (th_data + idx)->chunk_size = chunk_size_block;
        }


        printf("Thread %d: base = %p, size = %lu\n", idx,
            (void *)(th_data + idx)->chunk_base, (th_data + idx)->chunk_size);

    }
}


void *SortChunk_TH(thread_meta_data_ty *thread_data)
{
    qsort(thread_data->chunk_base, thread_data->chunk_size,
             sizeof(unsigned char *), thread_data->CmpStrings);

    return NULL;
}


int RunAndMergeThreads(unsigned char **dest_sorted_ptrs,
                       thread_meta_data_ty *th_data,
                       pthread_t *arr_thread,
                       int num_threads)
{
    int i = 0;
    int joined_count = 0;
    int result = 0;
    int created[NUM_THREADS] = {0};
    int joined[NUM_THREADS] = {0};
    int total_words = g_num_words * COPIES;

    g_end_of_dest_array = dest_sorted_ptrs + total_words;
    g_start_of_result = g_end_of_dest_array; /* g_end_of_dest_array  */

    do
    {
        for (i = 0; i < num_threads; ++i)
        {
            if (!created[i])
            {
                result = pthread_create(arr_thread + i, NULL,
                                        (th_func_ptr)SortChunk_TH, th_data + i);
                RETURN_IF_BAD(0 == result, FAIL, "pthread_create failed");
                created[i] = 1;
            }

            else if (!joined[i])
            {
                result = pthread_join(*(arr_thread + i), NULL); /*pthread_tryjoin_np*/

                if (0 == result)
                {
                    joined[i] = 1;
                    ++joined_count;
                    
                    if (g_start_of_result - (th_data + i)->chunk_size < dest_sorted_ptrs)
                    {
                        fprintf(stderr, "ERROR: g_start_of_result underrun! Would go before start of array.\n");
                        exit(1);
                    }


                    printf("Merging thread %d into [%p - %p]\n",
                           i, (void *)g_start_of_result, (void *)g_end_of_dest_array);

                    assert(g_start_of_result >= dest_sorted_ptrs);
                    assert(g_end_of_dest_array <= dest_sorted_ptrs + g_num_words * COPIES);
                                  
                    result = MergeSortedChunks(th_data + i);
                    RETURN_IF_BAD(SUCCESS == result, FAIL, "MergeSortedChunks failed");
                }
            }
        }

    } while (joined_count < num_threads);

    /*memmove(dest_sorted_ptrs, g_start_of_result, 
        g_current_result_len * sizeof(unsigned char *));*/

    for (i = 0; i < 20; ++i)
    {
        printf("g_start_of_result[%u] = %s\n", i, g_start_of_result[i]);
    }



    return SUCCESS;
}                    

int MergeSortedChunks(thread_meta_data_ty *th_data)
{
    unsigned char **a = th_data->chunk_base;
    size_t a_len = th_data->chunk_size;

    static int is_first_merge = 1;
    size_t b_len = g_current_result_len;
    unsigned char **b = g_start_of_result;

    unsigned char **merge_dest = NULL;
    unsigned char **a_ptr = NULL;
    unsigned char **b_ptr = NULL;
    cmp_func_ptr CmpStr = th_data->CmpStrings;

    if (is_first_merge)
    {
        is_first_merge = 0;
        g_start_of_result = g_end_of_dest_array - a_len;

        memcpy(g_start_of_result, a, a_len * sizeof(unsigned char *));

        g_current_result_len = a_len;

        return SUCCESS;
    }

    if (a_len == 0 || b_len == 0)
    {
        fprintf(stderr, "[ERROR] MergeSortedChunks: empty chunk! a_len = %lu, b_len = %lu\n", a_len, b_len);
        return FAIL;
    }

    merge_dest = g_end_of_dest_array - 1;
    a_ptr = a + a_len - 1;
    b_ptr = b + b_len - 1;

    while (a_len && b_len)
    {
        if (CmpStr(a_ptr, b_ptr) > 0)
        {
            *merge_dest-- = *a_ptr--;
            --a_len;
        }
        else
        {
            *merge_dest-- = *b_ptr--;
            --b_len;
        }
    }

    while (a_len--)
    {
        if (a_ptr < a)
        {
            fprintf(stderr, "ERROR: a_ptr before a (%p < %p)\n", (void *)a_ptr, (void *)a);
            exit(1);
        }
        *merge_dest-- = *a_ptr--;
    }

    while (b_len--)
    {
        *merge_dest-- = *b_ptr--;
    }

    g_current_result_len += th_data->chunk_size;
    g_start_of_result = g_end_of_dest_array - g_current_result_len;

    return SUCCESS;
}


static int ValidateSortedOutput(unsigned char **sorted_ptrs, size_t total_words, size_t copies)
{
    size_t i = 0;
    
    /*for (i = 0; i < 20; ++i)
    {
        printf("sorted_ptrs[%lu] = %p\n", i, (void*)(sorted_ptrs + i));
    }*/


    for (i = 0; i < total_words; i += copies)
    {
        size_t j = 1;

        for (j = 1; j < copies; ++j)
        {
            if (0 != strcmp((const char *)sorted_ptrs[i], (const char *)sorted_ptrs[i + j]))
{
    fprintf(stderr, "Mismatch at group %lu: '%s' vs '%s'\n",
            i / copies, sorted_ptrs[i], sorted_ptrs[i + j]);
    return FAIL;
}
        }

        if (i + copies < total_words)
        {
            if (strcmp((const char *)sorted_ptrs[i + copies - 1], (const char *)sorted_ptrs[i + copies]) > 0)
            {
                fprintf(stderr, "Out-of-order at group %lu vs %lu: '%s' > '%s'\n",
                        i / copies, (i + copies) / copies,
                        sorted_ptrs[i + copies - 1], sorted_ptrs[i + copies]);
                return FAIL;
            }
        }
    }

    return SUCCESS;
}

