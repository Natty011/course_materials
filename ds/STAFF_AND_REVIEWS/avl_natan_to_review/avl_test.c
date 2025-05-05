/******************************************************************************
*
*	Aouther:	Natan Yunger
*	Review:		Natty Levi
*	Date:		12/02/25
*
******************************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>

#include "avl.h"

#define RED_BKG		"\033[0;31m\033[7m"
#define GRN_BKG		"\033[0;92m\033[7m"
#define PRPL		"\033[0;95m"
#define ITLC		"\033[3m"
#define NRML		"\033[0m"

typedef struct
{
	int arr[3];
	size_t idx;
} tree_to_arr_t;

int TestCreate(void);
int TestInsert(void);
int TestRemoveAndSize(void);
int TestFind(void);
int TestForEach(void);

static int Compare(void* check_data , void* new_data);
static int InsertToArr(void* data, void* user_param);

int main()
{
	int failure = 0;
	
	char* mode = NRML;
	#ifndef NDEBUG
		mode = PRPL;
	#endif
	
	printf("%s", mode);
	
	failure += (TestCreate() && printf("Create "RED_BKG"failed!\n%s", mode));
	failure += (TestInsert() && printf("Insert "RED_BKG"failed!\n%s", mode));
	failure += (TestRemoveAndSize() &&
						 printf("Remove or Size "RED_BKG"failed!\n%s", mode));
	failure += (TestFind() && printf("Find "RED_BKG"failed!\n%s", mode));
	failure += (TestForEach() && printf("ForEach "RED_BKG"failed!\n%s", mode));
	
	if (!failure)
	{
		printf("all functions "GRN_BKG"succeeded!\n");
	}
	printf(NRML);
	
	return 0;
}

int TestCreate(void)
{
	int res = 0;
	avl_t* tree = AVLCreate(NULL);
	res += (NULL == tree);
	res += !AVLIsEmpty(tree);
	AVLDestroy(tree);	
	return res;
}

int TestInsert(void)
{
	int res = 0;
	size_t i = 0;
	int arr[32] = {0};
	
	avl_t* tree = AVLCreate(Compare);
	for (i = 0; i < 32; ++i)
	{
		*(arr + i) = (int)i;
		res += AVLInsert(tree, arr + i);
	}
	
	res += AVLIsEmpty(tree);
	#ifndef NDEBUG
		printf("************************ first test ************************\n");
		PrintTree(tree);
		printf("************************************************************\n");
	#endif
	res += (5 != AVLHeight(tree));
	
	AVLDestroy(tree);	
	return res;
}

int TestRemoveAndSize(void)
{
	int res = 0;
	size_t i = 0;
	int arr[32] = {0};
	int to_remove[6] = {31, 30, 29, 27, 23, 15};
	
	avl_t* tree = AVLCreate(Compare);
	for (i = 0; i < 32; ++i)
	{
		*(arr + i) = (int)i;
		res += AVLInsert(tree, arr + i);
		res += (i + 1 != AVLSize(tree));
	}
	
	res += AVLIsEmpty(tree);
	#ifndef NDEBUG
		printf("************************ second test ***********************\n");
		PrintTree(tree);
	#endif
	
	for (i = 0; i < 6; ++i)
	{
		AVLRemove(tree, to_remove + i);
		res += (31 - i != AVLSize(tree));
	}
	
	#ifndef NDEBUG
		printf("after removing right branch:\n");
		PrintTree(tree);
		printf("************************************************************\n");
	#endif
	
	AVLDestroy(tree);	
	return res;
}

int TestFind(void)
{
	int res = 0;
	size_t i = 0;
	int arr[10] = {0};
	
	avl_t* tree = AVLCreate(Compare);
	for (i = 0; i < 10; ++i)
	{
		*(arr + i) = (int)(i * 3);
		AVLInsert(tree, arr + i);
	}
	
	for (i = 0; i < 30; ++i)
	{
		if (i % 3)
		{
			res += (NULL != AVLFind(tree, &i));
		}
		
		else
		{
			res += ((int)i != *(int*)AVLFind(tree, &i));
		}
	}
	
	AVLDestroy(tree);	
	return res;
}

int TestForEach(void)
{
	int res = 0;
	int arr[3] = {3, 2, 1};
	size_t i = 0;
	
	int in_order[3] = {1, 2, 3};
	int pre_order[3] = {2, 1, 3};
	int post_order[3] = {1, 3, 2};
	
	avl_t* tree = AVLCreate(Compare);
	
	tree_to_arr_t my_struct;
	memset(&my_struct, 0, sizeof(tree_to_arr_t));
	
	for (i = 0; i < 3; ++i)
	{
		AVLInsert(tree, arr + i);
	}
	
	res += AVLForEach(tree, InsertToArr, &my_struct, IN_ORDER);
	for (i = 0; i < 3; ++i)
	{
		res += (*(my_struct.arr + i) != *(in_order + i));
	}
	
	res += AVLForEach(tree, InsertToArr, &my_struct, PRE_ORDER);
	for (i = 0; i < 3; ++i)
	{
		res += (*(my_struct.arr + i) != *(pre_order + i));
	}
	
	res += AVLForEach(tree, InsertToArr, &my_struct, POST_ORDER);
	for (i = 0; i < 3; ++i)
	{
		res += (*(my_struct.arr + i) != *(post_order + i));
	}
	
	AVLDestroy(tree);	
	return res;
}


/****************************** static functions ******************************/

static int Compare(void* check_data , void* new_data)
{
	return *(int*)check_data - *(int*)new_data;
}

static int InsertToArr(void* data, void* user_param)
{
	tree_to_arr_t* my_struct = (tree_to_arr_t*)user_param;
	*(my_struct->arr + my_struct->idx) = *(int*)data;
	my_struct->idx = (my_struct->idx + 1) % 3;
	return 0;
}






















