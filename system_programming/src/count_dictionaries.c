/***************************************
* Author : Natty
* Reviewer :
* File : count_dictionaries.c  
* Date : 08 / 04 / 2025
* Last update: 08 / 04 / 2025
*****************************************/
#include <stdio.h>
#include <sys/mman.h>   /* mmap, munmap */
#include <sys/stat.h>   /* fstat */
#include <fcntl.h>      /* open */

#include "utils.h"
#include <cstdint>  /* uint8_8*/

enum
{
    NUM_ASCII_CHARS  = 256,
    NUM_THREADS = 4,
    CACHE_LINE_SIZE = 64,
    APOSTROPHE = '\'',
    CACHE_PADDED_HIST_SIZE = ((NUM_ASCII_CHARS + CACHE_LINE_SIZE - 1)
                                     / CACHE_LINE_SIZE) * CACHE_LINE_SIZE

};

typedef struct thread_meta_data
{
    uint8_t *start_word_ptr;
    uint8_t *end_word_ptr;
    uint8_t *thread_histogram_ptr;

}thread_meta_data_ty;

/* struct thread_data_t */
    /* start_word_ptr*/
    /* end_word_ptr */
    /*thread_histogram_ptr*/

/* enum*/
    /* NUM_LETTERS = 26*/

typedef void *(*th_func_ptr)(void* ); 

/*functions defenition*/
    /* CountNumOfWordsInDictFile(char *dict_ptr, size_t dict_size) */
    /* NumOfDictCopies(char *dict_ptr, size_t dict_size, num_word) */
    /* InitThreadMetaData(th_data, num_word, num_thread, start_ptr_dict) */
    /* CountCharInInterval_TH(thread_data_t *th_data[] )*/


int main(int argc, char **argv)
{

    char *dict_ptr = NULL;
    size_t file_size = 0;
    size_t num_threads = 0;
    thread_meta_data_ty **threads_data = NULL;

    /* if argc < 2 */
        /* return */

    /* main_hist[NUM_LETTERS] = {0} */
    /* path = argv[1] */
    /* main_hist[NUM_LETTERS] = {0}*/

    /* start_ptr_dict = mmap(path) */
    /* num_word = CountNumOfWordsInDictFile(char *dict_ptr, size_t dict_size) */
    /* num_thread = NumOfDictCopies(char *dict_ptr, size_t dict_size, num_word) */


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
        

    return 0;
}
/* Count the total words in the copy dictinory */
size_t CountNumOfWordsInDictFile(char *dict_ptr, size_t dict_size)
{


}

void InitThreadMetaData(thread_meta_data_ty *th_data, size_t num_threads,
    char *dict_ptr, size_t file_size)
{


}

void *CountCharInInterval_TH(thread_meta_data_ty *data)
{

}    