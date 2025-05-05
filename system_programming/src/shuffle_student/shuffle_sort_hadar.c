/****************************************
date 9.4.25
topic: shuffle and sort dictionary file
****************************************/
#define _GNU_SOURCE
#include <string.h> /*strtok, strcmp */
#include <stdlib.h> /*rand , malloc, qsort*/
#include <fcntl.h> /*open, O_RDONLY*/
#include <sys/stat.h> /*fstat*/
#include <pthread.h> /*pthread_t*/
#include <sys/mman.h> /*mmap*/
#include <assert.h>
#include <errno.h>

#include "utils.h"

enum
{
    NUM_THREADS = 8,
    NUM_OF_WORDS = 104334, /*wc -w*/
    CASH_LINE_SIZE = 64,
    NUM_OF_DUPS = 10,
    RANGE = ((NUM_OF_WORDS * NUM_OF_DUPS) / NUM_THREADS),
    REMAINDER =((NUM_OF_WORDS * NUM_OF_DUPS) % NUM_THREADS)
};

typedef void*(*routin_fun_ty)(void*);



int RandCompareFunc(const void* x,const void* y);
int StrcmpCompareFunc(const void* x,const void* y);
void* ThreadRoutine (unsigned char** words_buffer);
void* ThreadRoutineLastThread (unsigned char** words_buffer);
static void SplitToWords(unsigned char *mmap, char* tokens[] , size_t size);
static void* MergeBuffers(unsigned char** start_dest_buffer,
    unsigned char** end_dest_buffer,
    unsigned char** start_sort_thread_buffer,
    int last_thead_flag);

int main()
{
    int fd = 0;
    unsigned char* mmap_addr = NULL;
    struct stat st;
    pthread_t threads[NUM_THREADS];
    pthread_t* ptr_threads;
    size_t size = 0;
    size_t i = 0;
    unsigned char** words_buffer = NULL;
    unsigned char** words_buffer_runner = NULL;
    unsigned char** merged_words_buffer = NULL;
    unsigned char** end_merged_buffer = NULL;
    int stat;
    int thread_to_join;
    int last_thread_flag;

    /*open: open file and get fd*/
    fd = open("/usr/share/dict/words", O_RDONLY);
    RETURN_IF_BAD((-1 != fd), -1, "open fail");

    /*fstat: get the file size*/
    RETURN_IF_BAD ((0 == fstat(fd, &st)),-1,"fstat fail"); /*give size of file*/
    size =st.st_size;

    /*mmap:read the linux English dictionary into the memory buffer*/
    mmap_addr = (unsigned char*)mmap(NULL, size, PROT_READ | PROT_WRITE,
                                     MAP_PRIVATE, fd ,0);

    /*words_buffer: malloc1 (unsighn char**) for size num_words * 10
                           buffer of pointers to the start of words */
    words_buffer = (unsigned char**)malloc(NUM_OF_WORDS*10*sizeof(unsigned char*));
    RETURN_IF_BAD((NULL != words_buffer), -1 ,"malloc fail");

    /*merged_words_buffer: malloc2 (unsighn char**) for size num_words * 10
                            buffer of pointers to the start of words */
    merged_words_buffer = (unsigned char**)malloc(NUM_OF_WORDS*10*sizeof(unsigned char*));
    RETURN_IF_BAD((MAP_FAILED != mmap_addr), -1 ,"mmap fail");

    /*strtok: loop strtok and zero the new line characters (\n)*/
    SplitToWords(mmap_addr, (char**)words_buffer , NUM_OF_WORDS);

    /*duplicated every pointer in word_buffer: 10 times overall*/
    for(i = 0 ; i < NUM_OF_DUPS -1 ; ++i)
    {
        memcpy((words_buffer + NUM_OF_WORDS * i),words_buffer ,
                                           NUM_OF_WORDS*sizeof(unsigned char*));
    }

    /*shuffle: qsort buffer(word_buffer) with random compre function*/
    /*random compre function : with (rand() % 3 -1) */
    qsort(words_buffer,NUM_OF_WORDS*10, sizeof(unsigned char*), RandCompareFunc);


    ptr_threads = threads;
    words_buffer_runner = words_buffer;

    for(i = 0; i < NUM_THREADS -1 ; ++i , ++ptr_threads, ++words_buffer_runner)
    {
        stat = pthread_create(ptr_threads, NULL,
                    (routin_fun_ty)ThreadRoutine, words_buffer_runner);
        RETURN_IF_BAD((0 == stat), -1, "pthread_create fail");

        words_buffer_runner += RANGE;
    }

    stat = pthread_create(ptr_threads, NULL,
                            (routin_fun_ty)ThreadRoutineLastThread, words_buffer_runner);
    RETURN_IF_BAD((0 == stat), -1, "pthread_create fail");


    /*pthread join*/
    thread_to_join = NUM_THREADS;
    while(thread_to_join)
    {
        ptr_threads = threads;
        for(i = 0; i < NUM_THREADS; ++i, ++ptr_threads)
        {
            if(*ptr_threads == 0)
            {
                continue;
            }

            stat = pthread_tryjoin_np(*ptr_threads, NULL);

            if(0 == stat)
            {
                if (NUM_THREADS-1 == i)
                {
                    last_thread_flag = 1;
                }
                /* merge the sorted parts into one with insertion techniqe */
                end_merged_buffer =  MergeBuffers(merged_words_buffer,
                                                    end_merged_buffer,
                                                    words_buffer + RANGE*i,
                                                    last_thread_flag);

                    --thread_to_join;
                    *ptr_threads = 0;
                    last_thread_flag = 0;
            }
            else
            {
                if(EBUSY == errno)
                {
                    continue;
                }
            }
        }
    }

    return 0;
}

int RandCompareFunc(const void* x,const void* y)
{
    (void)x;
    (void)y;

    assert(x);
    assert(y);

    return rand() % 3 - 1;
}


int StrcmpCompareFunc(const void* x,const void* y)
{
    assert(x);
    assert(y);

    return strcmp(*(char**)x , *(char**)y);
}


void* ThreadRoutine (unsigned char** words_buffer)
{
    assert(words_buffer);
    /*thread_routine*/
    /*each thread sort part of the words_buffer with qsort with fun of strcmp*/
    qsort(words_buffer,RANGE, sizeof(unsigned char*), StrcmpCompareFunc);

    return NULL;

}

void* ThreadRoutineLastThread (unsigned char** words_buffer)
{
    assert(words_buffer);
    /*thread_routine*/
    /*each thread sort part of the words_buffer with qsort with fun of strcmp*/
    qsort(words_buffer,RANGE+REMAINDER, sizeof(unsigned char*), StrcmpCompareFunc);

    return NULL;

}


static void SplitToWords(unsigned char *mmap, char** tokens , size_t size)
{
    char* word = NULL;
    size_t i = 0;
    (void)size;

    assert(tokens);
    assert(mmap);

    word = strtok((char*)mmap, "\n");
    ExitIfBad(NULL != word, "strtok fail");

    while(word)
    {
        tokens[i++] = word;
        word = strtok(NULL, "\n");
        /*if num of chars is biggger then MAX_WORDS, exit*/
        ExitIfBad((i <= size) , "too many arguments");
    }

}

/*put the first src in the merge_words_buffer*/

static void* MergeBuffers(unsigned char** start_dest_buffer,
                          unsigned char** end_dest_buffer,
                          unsigned char** start_sort_thread_buffer,
                          int last_thread_flag)
{
    unsigned char** write_ptr = NULL;
    unsigned char** lest_merged_buffer = NULL;
    unsigned char** end_sort_thread_buffer = NULL;
    int range = 0;

    assert(start_dest_buffer);
    assert(end_dest_buffer);
    assert(start_sort_thread_buffer);

    range = (last_thread_flag) ? RANGE+REMAINDER : RANGE;

    write_ptr = end_dest_buffer + range;
    lest_merged_buffer = write_ptr;
    end_sort_thread_buffer = start_sort_thread_buffer + range;

    while(start_dest_buffer <= end_dest_buffer ||
          start_sort_thread_buffer <= end_sort_thread_buffer)
    {
        if(strcmp(*(char**)end_dest_buffer, *(char**)end_sort_thread_buffer) > 0)
        {
            *write_ptr = *end_dest_buffer;
            --end_dest_buffer;
        }
        else
        {
            *write_ptr = *end_sort_thread_buffer;
            --end_sort_thread_buffer;
        }
        --write_ptr;
    }

    while(start_dest_buffer <= end_dest_buffer)
    {
        *write_ptr = *end_dest_buffer;
        --end_dest_buffer;
    }

    while(start_sort_thread_buffer <= end_sort_thread_buffer)
    {
        *write_ptr = *end_sort_thread_buffer;
        --end_sort_thread_buffer;
    }

    return lest_merged_buffer;
}