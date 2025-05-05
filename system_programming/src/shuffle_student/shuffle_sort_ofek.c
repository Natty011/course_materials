/*
Programer : Ofek.
Date : 10.04.2025
Version : First version
Approved by : Gilad   
Date of approval : Not sending yet  
*/

#define _GNU_SOURCE

#define unlikely(expr) __builtin_expect(!!(expr), 0)

#include <string.h>		/* strtok, strcmp		*/
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>

#include "utils.h"

/* Use the shell command wc -l /usr/share/dict/words to get the number of words,
got 10 dictionaries */
enum 
{
	NUM_OF_THREADS = 6,
	NUM_OF_WORDS = 1043340
};

typedef enum
{
	SUCCESS = 0,
	FAIL = 1
}status_ty;

typedef void* (*thread_func)(void*);

typedef struct
{
	char** from;
	size_t num_of_elements;
	
}thread_info_ty;

sem_t g_semphore;

static char* BeginOfDictionary(void);
static void InitArraysOfPointers(char*** original, char*** for_merge);
static void SplitWords(char* dictionary, char** original);
static void Shuffle(char** original);
static int comp_shuffle(const void* a, const void* b);

static void StartingThreads(char** original,pthread_t* threads);
static void* SortRoutine_TH(thread_info_ty* thread_info);
static int CompareStr(const void* a, const void* b, void* arg);

static void MergeResults(char** for_merge, thread_info_ty* retval); 

int main()
{
	clock_t time = 0;
	/*size_t i = 0;*/
	/* mapped the memory of  dictionary to the process
	and return a pointer and the number of words 
	NOTE : use private mode */
	int status = 0;
	size_t thread_number = 0;
	size_t threads_finished = 0;
	char* dictionary = NULL;
	char** original = NULL;
	char** for_merge = NULL;
	/* retval is the return value from the threads, which
	is the thread_info of each thread */
	thread_info_ty* retval = NULL;
	
	/* Create local array of threads */
	pthread_t threads[NUM_OF_THREADS];

	dictionary = BeginOfDictionary();
	
	/* Initialize 'original' and 'for_merge', each have NUM_OF_WORDS pointers
	to string */
	InitArraysOfPointers(&original, &for_merge);
	
	/* call function SplitWords so each pointer point to a word and
	change the last char of each words from \n to \0 */
	SplitWords(dictionary, original);
	
	/* Use qsort with Random (compare function that generate randomly -1 or 0 or 1)
	the purpose is to shuffle the pointers */
	Shuffle(original);
	
	AbortIfBad(SUCCESS == sem_init(&g_semphore, 0, 0), "sem_init fail");
	
	/*************************************************************************
	start time */
	
	time = clock();
	
	/* Create threads and start their routines */
	StartingThreads(original, threads);
	
	/* Join and merge */
	for (thread_number = 0, threads_finished = 0; NUM_OF_THREADS > threads_finished; ++threads_finished)
	{
		
		while (sem_wait(&g_semphore))
		{
			AbortIfBad(EINTR == errno , "sem_wait fail");
		}
		
		while ((status = pthread_tryjoin_np(threads[thread_number], (void**)&retval)))
		{
			
			AbortIfBad(EBUSY == status || EINVAL == errno , "pthread_tryjoin_np fail");
		
			thread_number = (thread_number + 1) % (NUM_OF_THREADS);
		}
		
		MergeResults(for_merge, retval);
		free(retval);
	} 
	
	
	/* copy to the original array */
	memcpy(original, for_merge, NUM_OF_WORDS * sizeof(char*)); 
	
	time = clock() - time;
	
	printf("The time took with %d threads is %f\n", NUM_OF_THREADS, (float)time/ CLOCKS_PER_SEC); 
	
	/* free allocated memory */
	free(original);
	free(for_merge); 	
	
	return 0;
}


static char* BeginOfDictionary(void)
{
	size_t page_size = 0;
	size_t length;
	struct stat stat;
	
	void* start_dictionary = NULL;
	
	int dictionary;
	
	AbortIfBad(0 < (dictionary = open("/home/ofek/NotForGit/bigdict.txt", O_RDONLY)), "open fail");
	
	AbortIfBad(SUCCESS == fstat(dictionary, &stat), "fstat fail");
	
	page_size = (size_t)sysconf(_SC_PAGESIZE);
	
	length = stat.st_size;
	
	/* Align length to page_table size */
	if (stat.st_size % page_size)
	{
		length += page_size - (stat.st_size % page_size);
	}
	
	start_dictionary = mmap(NULL, length , PROT_READ | PROT_WRITE , MAP_PRIVATE, dictionary, 0);
	
	AbortIfBad(((void*)-1) != start_dictionary, "mmap fail");
	
	return (char*)start_dictionary;
}


static void InitArraysOfPointers(char*** original, char*** for_merge)
{
	*original = (char**)malloc(NUM_OF_WORDS * sizeof(char*));
	
	*for_merge = (char**)calloc(1, (NUM_OF_WORDS * sizeof(char*)));
}


static void SplitWords(char* dictionary, char** original)
{
	char** end = original + NUM_OF_WORDS;
	
	*original = strtok(dictionary, "\n");
	++original;
	
	while (end > original)
	{
		*original = strtok(NULL, "\n");
		++original;
	}
}


/* Shuffle 5 times */
static void Shuffle(char** original)
{
	int shuffle = 5;
	
	while (shuffle)
	{
		qsort(original, NUM_OF_WORDS , sizeof(char*), comp_shuffle);
		--shuffle;
	}
}


/* return -1, 0 or 1. use to shuffle the array of pointers */
static int comp_shuffle(const void* a, const void* b)
{
	int rand_num = 0;
	srand(time(NULL));
	
	(void)a;
	(void)b;
	
	rand_num = rand() % 3;
	
	return rand_num - 1; /* return -1, 0 or 1 */
}

static char** ThreadStart(pthread_t* thread, char** from, size_t words_for_thread); 

static void StartingThreads(char** original ,pthread_t* threads)
{
	pthread_t* start_thread = threads;
	pthread_t* end = (threads + NUM_OF_THREADS);
	char** from = NULL;
	size_t words_for_thread = NUM_OF_WORDS / NUM_OF_THREADS;
	
	/* The first thread take little more pointers */
	from = ThreadStart(start_thread, original, words_for_thread + (NUM_OF_WORDS % NUM_OF_THREADS));
	
	/* Increment to the next thread */
	++start_thread;
	
	while (end > start_thread)
	{
		from = ThreadStart(start_thread, from, words_for_thread);
		++start_thread;
	}
}
		
	
/* return the start for the next thread */	
static char** ThreadStart(pthread_t* thread, char** from, size_t words_for_thread)
{
	thread_info_ty* thread_info = (thread_info_ty*)malloc(sizeof(thread_info_ty));
	AbortIfBad(NULL != thread_info, NULL);
	
	thread_info->from = from;
	thread_info->num_of_elements = words_for_thread;
	
	AbortIfBad(0 == pthread_create(thread, NULL, (thread_func)SortRoutine_TH, thread_info), NULL);
	
	return from + words_for_thread;
}


static void* SortRoutine_TH(thread_info_ty* thread_info)
{
	qsort_r(thread_info->from, thread_info->num_of_elements, sizeof(char*),
																	CompareStr, NULL);
																	
	/* The main thread wait for the threads to finish to join with them */															
	sem_post(&g_semphore);
	
	return thread_info;
}


static int CompareStr(const void* a, const void* b, void* arg)
{
	(void)arg;
	
	return strcmp(*(char**)a, *(char**)b);
}


static void MergeResults(char** for_merge, thread_info_ty* retval)
{
	static size_t write_to = 0;
	size_t num_of_elements = retval->num_of_elements;
	char** iter = NULL;
	char** new_data = NULL;
	char** old_data = NULL;
	char** from = retval->from;
	char* temp = NULL;
	
	if (0 == write_to)
	{
		write_to += num_of_elements;
		memcpy(for_merge, from , num_of_elements * sizeof(char*));
		
		return;
	}
	
	new_data = retval->from + num_of_elements - 1;
	old_data = for_merge + write_to - 1; 
																	
	write_to += num_of_elements;
	/* Write to the biggest element */
	iter = for_merge + write_to - 1;
	
	while (for_merge <= iter && for_merge <= old_data && from <= new_data)
	{
		if (strcmp(*new_data, *old_data) > 0)
		{
			temp = *new_data;
			*iter = temp;
			--new_data;
		}
		
		else 
		{
			temp = *new_data;
			*iter = temp;
			--old_data;
		}
		
		--iter;
		
	}	
}
			
