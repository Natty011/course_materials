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
#include <semaphore.h>  /* sem_wait, post, init, destroy  */
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
static unsigned char **g_start_of_result = NULL;
/*static unsigned char **g_end_of_dest_array = NULL;*/
static size_t g_current_result_len = 0;
static sem_t g_merge_semaphore;

typedef void *(*th_func_ptr)(void* ); 
typedef int (*cmp_func_ptr)(const void* p1, const void* p2); 

int CmpStrings(const void *p1, const void *p2);


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


static void InitThreadChunks(unsigned char **word_ptrs, thread_meta_data_ty *th_data,
            int num_threads, size_t total_words); 

void *SortChunk_TH(thread_meta_data_ty *thread_data);

int RunAndMergeThreads(unsigned char **dest_sorted_ptrs,
    thread_meta_data_ty *th_data,
    pthread_t *arr_thread,
    int num_threads);

int MergeSortedChunks(thread_meta_data_ty *th_data, unsigned char **dest_sorted_ptrs);


static int ValidateSortedOutput(unsigned char **sorted_ptrs, size_t total_words, size_t copies);

void PrintFirstWordsPerDict(unsigned char **word_ptrs, size_t num_words, size_t num_copies);
void PrintLastWordsPerDict(unsigned char **word_ptrs, size_t num_words, size_t num_copies);

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

    RETURN_IF_BAD(SUCCESS == sem_init(&g_merge_semaphore, 0, 0), FAIL, "sem_init failed" );   

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
    
    puts("Reached after all merges");
    if(FAIL == result)
    {
        FreeResources(words_ptrs, sorted_ptrs, threads_data, arr_thread);
        RETURN_IF_BAD (FALSE, FAIL, "RunAndMergeThreads failed" );   
    }

    end_time = clock();
    elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken for sorting and merging with %d threads: %.6f seconds\n", num_threads, elapsed);


    puts("===========after RunAndMergeThreads================================");

    PrintFirstWordsPerDict(sorted_ptrs, g_num_words, COPIES);
    PrintLastWordsPerDict(sorted_ptrs, g_num_words, COPIES);

    result = ValidateSortedOutput(sorted_ptrs , g_num_words * COPIES, COPIES);
    if(FAIL == result)
    {
        FreeResources(words_ptrs, sorted_ptrs, threads_data, arr_thread);
        RETURN_IF_BAD (FALSE, FAIL, "Validation of sorted output failed" );   
    }

   

    RETURN_IF_BAD(SUCCESS == sem_destroy(&g_merge_semaphore), FAIL, "sem_destroy failed" );   

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
    return (rand() % 3 ) - 1; /* returns -1, 0, or 1 randomly */
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

  
    if (SUCCESS != sem_post(&g_merge_semaphore))
    {
        perror("sem_post failed");
        exit(1);
    }

    puts("Thread finished sorting, posting to semaphore");

    return (void*)thread_data;
}


int RunAndMergeThreads(unsigned char **dest_sorted_ptrs,
                       thread_meta_data_ty *th_data,
                       pthread_t *arr_thread,
                       int num_threads)
{
    int merged_count = 0;
    int i = 0;
    int result = 0;
    void* ret_val = NULL;
    int joined_flags[NUM_THREADS] = {0};
    pthread_t *thread_runner = NULL;
    thread_meta_data_ty *meta_runner = NULL;

    g_current_result_len = 0;
    g_start_of_result = dest_sorted_ptrs;

    for(i = 0; i < num_threads; ++i)
    {
        result = pthread_create(arr_thread + i, NULL,
                                (th_func_ptr)SortChunk_TH, th_data + i);
        if(0 != result)
        {
            perror("pthread_create failed");
            return FAIL;
        }
    }

    while(merged_count < num_threads )
    {
        while(sem_wait(&g_merge_semaphore))
        {
            if(EINTR == errno)
            {
                puts("if(EINTR == errno)");
                continue;
            }

            perror("sem_wait failed");
            return FAIL;
        }

        thread_runner = arr_thread;
        meta_runner = th_data;

        while(thread_runner < arr_thread + num_threads)
        {
            int index = thread_runner - arr_thread;

            if(!joined_flags[index])
            {
                result = pthread_tryjoin_np(*thread_runner, &ret_val);

                if(0 == result)
                {
                    thread_meta_data_ty *meta = (thread_meta_data_ty *)ret_val;

                    if(NULL == meta)
                    {
                        fprintf(stderr, "meta is NULL!\n");
                        return FAIL;
                    }
                    printf("Merging chunk at %p with %lu items\n", (void*)(meta->chunk_base), meta->chunk_size);

                    puts("before MergeSortedChunks");
                    result = MergeSortedChunks(meta, dest_sorted_ptrs);
                    puts("after MergeSortedChunks");

                    if(SUCCESS != result)
                    {
                        return FAIL;
                    }

                    PRINT_IF_DEBUG("Joining thread %d\n", index);

                    joined_flags[index] = 1;
                    ++merged_count;
            
                    continue;  
                              
                }

                else if(EBUSY == errno)
                {
                    puts("else if(EBUSY == errno)");

                    ++thread_runner;
                    ++meta_runner;
                    continue;
                }
                else
                {
                    ++thread_runner;
                    ++meta_runner;
                    continue;
                }
            }

            ++thread_runner;
            ++meta_runner;
        }

        PRINT_IF_DEBUG("merged_count = %d\n", merged_count);

    }
    assert(merged_count == num_threads);
    return SUCCESS;
}

int MergeSortedChunks(thread_meta_data_ty *th_data, unsigned char **dest_sorted_ptrs)
{
    unsigned char **a = th_data->chunk_base;
    size_t a_len = th_data->chunk_size;

    unsigned char **a_ptr = NULL;
    unsigned char **b_ptr = NULL;
    size_t a_remain = 0;
    size_t b_remain = 0;
    size_t i = 0;
    unsigned char **merged = NULL;
    
    #ifndef NDEBUG
        size_t old_result_len = g_current_result_len;
    #endif

    puts("=== MergeSortedChunks() ===");
    PRINT_IF_DEBUG("a_len = %lu\n", a_len);
    PRINT_IF_DEBUG("g_current_result_len = %lu\n", g_current_result_len);

    /* copy the first that finished */

    if (0 == g_current_result_len)
    {
        memcpy(dest_sorted_ptrs, a, a_len * sizeof(unsigned char *));
        g_start_of_result = dest_sorted_ptrs;
        g_current_result_len = a_len;

        puts("first merge copied directly");
        return SUCCESS;
    }

    /* merge with the previous result*/
    merged = (unsigned char **)malloc((a_len + g_current_result_len) * sizeof(unsigned char *));
    if (NULL == merged)
    {
        perror("malloc failed in MergeSortedChunks");
        return FAIL;
    }

    a_ptr = a;
    b_ptr = g_start_of_result;
    a_remain = a_len;
    b_remain = g_current_result_len;
    i = 0;

    PRINT_IF_DEBUG("Initial pointers:%s\n", "");
    PRINT_IF_DEBUG("a_ptr = %p\n", (void *)a_ptr);
    PRINT_IF_DEBUG("b_ptr = %p\n", (void *)b_ptr);
    PRINT_IF_DEBUG("dest_sorted_ptrs = %p\n", (void *)dest_sorted_ptrs);

    /* sort and merge with the previous result*/
    while (a_remain && b_remain)
    {
        if (th_data->CmpStrings(a_ptr, b_ptr) < 0)
        {
            merged[i++] = *a_ptr++;
            --a_remain;
        }
        else
        {
            merged[i++] = *b_ptr++;
            --b_remain;
        }
    }

    /* copy remainnig A */
    while (a_remain--)
    {
        merged[i++] = *a_ptr++;
    }

    /* copy remainnig B */
    while (b_remain--)
    {
        merged[i++] = *b_ptr++;
    }

    PRINT_IF_DEBUG("Merged i = %lu elements\n", i);
    PRINT_IF_DEBUG("Copying merged array back to dest_sorted_ptrs (size = %lu)\n", a_len + g_current_result_len);

    /* copy to dest_sorted_ptrs */
    assert(i == a_len + old_result_len);

    memcpy(dest_sorted_ptrs, merged, (a_len + g_current_result_len) * sizeof(unsigned char *));
    g_start_of_result = dest_sorted_ptrs;
    g_current_result_len += a_len;

    puts("merge completed\n");

    free(merged);
    return SUCCESS;
}


static int ValidateSortedOutput(unsigned char **sorted_ptrs, size_t total_words, size_t copies)
{
    size_t i = 0;
    
    
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

    PRINT_IF_DEBUG("ValidateSortedOutput pass in success. i = %lu elements\n", i);


    return SUCCESS;
}


void PrintFirstWordsPerDict(unsigned char **word_ptrs, size_t num_words, size_t num_copies)
{
    size_t copy_idx = 0;
    size_t i = 0;

    puts("=========== First 10 words of each dictionary ===========");

    for (copy_idx = 0; copy_idx < num_copies; ++copy_idx)
    {
        printf(">>> Dictionary #%lu:\n", copy_idx);

        for (i = 0; i < 10 && i < num_words; ++i)
        {
            puts((char *)word_ptrs[copy_idx * num_words + i]);
        }

        puts("---------------------------------------------------------");
    }
}


void PrintLastWordsPerDict(unsigned char **word_ptrs, size_t num_words, size_t num_copies)
{
    size_t copy_idx = 0;
    size_t i = 0;

    puts("=========== Last 10 words of each dictionary ===========");

    for (copy_idx = 0; copy_idx < num_copies; ++copy_idx)
    {
        printf(">>> Dictionary #%lu:\n", copy_idx);

        for (i = num_words - 10; i < num_words; ++i)
        {
            puts((char *)word_ptrs[copy_idx * num_words + i]);
        }

        puts("--------------------------------------------------------");
    }
}
