#ifndef __STACK_TEST_DATA_H__   
#define __STACK_TEST_DATA_H__

#include <stddef.h> 

static char chars[] = { 'I' , 'd' , 'A' , 'N' , '\n' , '\0' , 'h' , 'D' };
static size_t lenC = sizeof chars / sizeof(char);

static  int ints[] = { 2 , -8 , 10 , 26 , -15 , 156 , 78 , -99 };
static size_t lenI = sizeof ints / sizeof(int);

static double doubles[] = {2.5 ,-8 ,10.3 ,26.9 ,-15.4 ,156 ,78.45 ,-99.99};
static size_t lenD = sizeof doubles / sizeof( double );

typedef struct 
{
	char name[16];
	int age;
	double avg;
	
} test_t;

static test_t structs[3]= 
{ 
	{"idan hadad" , 37 , 100} ,
	{"gogo yoyo" , 40 , 75.5} ,
  	{"blabla" , 20 , 88.9}
};
	 
static size_t lenS = 3;

#endif /* __STACK_TEST_DATA_H__ */   
