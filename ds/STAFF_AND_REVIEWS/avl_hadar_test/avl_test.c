/******************************************************************************
*Author: hadar
*Reviewer: Reut
*Date: 
*Version 1
******************************************************************************/
#include <stdio.h>          /* printf        */
#include "avl.h" 


/* RED_FAIL, GREEN_SUCCESS */
#define RED_FAIL "\033[0;31m failed \033[0;37m"
#define GREEN_SUCCESS "\033[0;32m success \033[0;37m"

/* LETTER COLOR */
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define DEFAULT_COLOR "\x1b[0m"

/* BACKGROUND COLOR */
#define BACK_BLACK   "\x1b[40m"
#define BACK_RED     "\x1b[41m"
#define BACK_GREEN   "\x1b[42m"
#define BACK_YELLOW  "\x1b[43m"
#define BACK_BLUE  	 "\x1b[44m"
#define BACK_MAGENTA "\x1b[45m"
#define BACK_CYAN 	 "\x1b[46m"
#define BACK_WHITE   "\x1b[47m"


#define SIZE 5000

enum
{
	SUCCESS = 0,
	FAIL = 1
};

enum
{
	FALSE = 0,
	TRUE = 1
};

/******************************************************************************/
void TestAVLCreate();
void TestAVLInsert();
void PrintTree( avl_t* avl );
void TestAVLRemove();
void TestAVLForEach();
void TestAVLFind();
void TestAVLRemoveRotation();
/******************************************************************************/
int cmp_func(void* check_data , void* new_data )
{
	return (*(int*)check_data - *(int*)new_data);
}
/******************************************************************************/
int main()
{
	char* mode = "release";
	char* color = BACK_YELLOW;
	
	#ifndef NDEBUG
		mode = "debug";
		color = BACK_CYAN;
	#endif	
	
	printf("%stest: %s mode" DEFAULT_COLOR "\n",color,mode);
	
	TestAVLCreate();
	TestAVLInsert();
	TestAVLForEach();
	TestAVLFind();
	TestAVLRemove();
	TestAVLRemoveRotation();
	
	return 0;
}

/****************************************************************************/
void TestAVLCreate()
{
	avl_t* avl = AVLCreate(cmp_func);
	int fail_count_create = 0;
	
	if(NULL == avl)
	{
		fail_count_create++;
		printf("line: %d\n" , __LINE__ );
	}

	printf("Test AvlCreate  %s \n", fail_count_create ? RED_FAIL : GREEN_SUCCESS);
	
	AVLDestroy(avl);
}

/****************************************************************************/
void TestAVLInsert()
{
	avl_t* avl = AVLCreate(cmp_func);
	int arr[] = {20, 10, 5, 25, 24, 30, 1};
	int fail_count_Insert = 0;
	int fail_count_isempty = 0;
	int fail_count_height = 0;
	int fail_count_rotation = 0;
	
	/*should be empty*/
	if(AVLIsEmpty(avl) == FALSE)
	{
		fail_count_isempty++;
		printf("line: %d\n" , __LINE__ );
	}
	
	/*insert 20*/
	AVLInsert(avl, arr);
	
	if (0 != AVLHeight(avl))
	{
		fail_count_height++;
		printf("line: %d\n" , __LINE__ );
	}
	/*
	PrintTree(avl);
	printf("~~~~~~~~~~~~~~~`\n");
	*/
	
	/*insert 10*/
	AVLInsert(avl, arr+1);
	if (1 != AVLHeight(avl))
	{
		fail_count_height++;
		printf("line: %d\n" , __LINE__ );
	}
	/*
	PrintTree(avl);
	printf("~~~~~~~~~~~~~~~`\n");
	*/
	/*insert 5*/
	AVLInsert(avl, arr+2);
	
	/*insert 1*/
	AVLInsert(avl, arr+6);
	/*should do LL rotation*/
	/*should be heigt 1 and not 2*/
	if (2 != AVLHeight(avl))
	{
		fail_count_rotation++;
		fail_count_height++;
		printf("line: %d\n" , __LINE__ );
	}
	/*
	PrintTree(avl);
	printf("~~~~~~~~~~~~~~~`\n");
	*/
	/*insert 25*/
	AVLInsert(avl, arr+3);
	if (2 != AVLHeight(avl))
	{
		fail_count_height++;
		printf("line: %d\n" , __LINE__ );
	}
	/*
	PrintTree(avl);
	printf("~~~~~~~~~~~~~~~`\n");
	*/
	/*insert 24*/
	/*should do RL rotation*/
	AVLInsert(avl, arr+4);
	if (2 != AVLHeight(avl))
	{
		fail_count_rotation++;
		fail_count_height++;
		printf("line: %d\n" , __LINE__ );
	}
	/*
	PrintTree(avl);
	printf("~~~~~~~~~~~~~~~`\n");
	*/
	/*insert 30*/
	/*should do LL rotation*/
	AVLInsert(avl, arr+5);
	if (3 != AVLHeight(avl))
	{
		fail_count_rotation++;
		fail_count_height++;
		printf("line: %d\n" , __LINE__ );
	}
	/*
	PrintTree(avl);
	printf("~~~~~~~~~~~~~~~`\n");
	*/	
	
	/*should be not empty*/
	if(AVLIsEmpty(avl) == TRUE)
	{
		fail_count_Insert++;
		fail_count_isempty++;
		printf("line: %d\n" , __LINE__ );
	}
	
	printf("Test AVLIsEmpty %s \n", fail_count_isempty ? RED_FAIL : GREEN_SUCCESS);
	printf("Test AVLInsert  %s \n", fail_count_Insert ? RED_FAIL : GREEN_SUCCESS);
	printf("Test AVLHeight  %s \n", fail_count_height ? RED_FAIL : GREEN_SUCCESS);
	printf("Test InsertRotation  %s \n", fail_count_rotation ? RED_FAIL : GREEN_SUCCESS);
	
	AVLDestroy(avl);
}


/*******************************************************************************/
int op_func (void* data, void* user_param)
{
	*(int*)data = *(int*)data + *(int*) user_param;
	return SUCCESS;
}

/*******************************************************************************/
int InsertToArray (void* data, void* arr)
{
	static int i = 0;
	if (3 == i)
	{
		i=0;
	}
	
	*((int*)arr+i) = *(int*)data;
	++i;
	
	return SUCCESS;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*static int printforeach(void* data, void* user_param)
{
	(void)user_param;
	
	printf("%3d" , *(int*)data );
	
	return 0;
}*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TestAVLForEach()
{
	avl_t* avl = AVLCreate(cmp_func);
	avl_t* avl_to_check_order = AVLCreate(cmp_func);
	int arr_origin_val[] = {20, 10, 5, 25, 24, 30, 1};
	int arr[] = {20, 10, 5, 25, 24, 30, 1};
	int arr_check_order[] = {5, 5, 5};
	int arr_check[] = {1, 2, 3};
	int post_order[] = {1, 3, 2};
	int pre_order[] = {2, 1, 3};
	int in_order[] = {1, 2, 3};
	size_t size = sizeof(arr)/sizeof(int);
	int add = 1;
	int fail_count_ForEach = 0;
	int fail_count_Size = 0;
	size_t i = 0;
	
	/*should be empty*/
	if (0 != AVLSize(avl))
	{
		++fail_count_Size;
		printf("line: %d\n" , __LINE__ );
	}

	AVLInsert(avl, arr);
	AVLInsert(avl, arr+1);
	AVLInsert(avl, arr+2);
	AVLInsert(avl, arr+3);
	AVLInsert(avl, arr+4);
	AVLInsert(avl, arr+5);
	AVLInsert(avl, arr+6);
	
	/*size should be 7*/
	if (7 != AVLSize(avl))
	{
		++fail_count_Size;
		printf("line: %d\n" , __LINE__ );
	}
	
	AVLForEach(avl, op_func, &add, IN_ORDER);
	
	for (i=0 ; i<size ;++i)
	{
		if(arr[i] != arr_origin_val[i] + 1)
		{
			++fail_count_ForEach;
		}
	}
	
	AVLForEach(avl, op_func, &add, PRE_ORDER);
	
	for (i=0 ; i<size ;++i)
	{
		if(arr[i] != arr_origin_val[i] + 2)
		{
			++fail_count_ForEach;
		}
	}
	
	AVLForEach(avl, op_func, &add, POST_ORDER);
	
	for (i=0 ; i<size ;++i)
	{
		if(arr[i] != arr_origin_val[i] + 3)
		{
			++fail_count_ForEach;
		}
	}	
		AVLDestroy(avl);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~check_order~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AVLInsert(avl_to_check_order ,  arr_check);
	AVLInsert(avl_to_check_order ,  arr_check+1);
	AVLInsert(avl_to_check_order ,  arr_check+2);
	
	AVLForEach(avl_to_check_order, InsertToArray, arr_check_order, IN_ORDER);
	
	for (i=0 ; i<3 ;++i)
	{
		if(arr_check_order[i] != in_order[i])
		{
			++fail_count_ForEach;
			printf("line: %d\n" , __LINE__ );
			printf(" %d\n" ,arr_check_order[i]);
		}
	}
	
	AVLForEach(avl_to_check_order, InsertToArray, arr_check_order, PRE_ORDER);
	
	for (i=0 ; i<3 ;++i)
	{
		if(arr_check_order[i] != pre_order[i])
		{
			++fail_count_ForEach;
			printf("line: %d\n" , __LINE__ );
			printf(" %d\n" ,arr_check_order[i]);
		}
	}
	
	AVLForEach(avl_to_check_order,InsertToArray, arr_check_order, POST_ORDER);
	
	for (i=0 ; i<3 ;++i)
	{
		if(arr_check_order[i] != post_order[i])
		{
			++fail_count_ForEach;
			printf("line: %d\n" , __LINE__ );
			printf(" %d\n" ,arr_check_order[i]);
		}
	}
	
	printf("Test AVLSize  %s \n", fail_count_Size ? RED_FAIL : GREEN_SUCCESS);
	printf("Test AVLForEach  %s \n", fail_count_ForEach ? RED_FAIL : GREEN_SUCCESS);
	
	AVLDestroy(avl);
}

/*******************************************************************************/
void TestAVLFind()
{
	avl_t* avl = AVLCreate(cmp_func);
	int arr[] = {20, 10, 5, 25, 24, 30, 1};
	size_t size = sizeof(arr)/sizeof(int);
	int fail_count_Find = 0;
	int num_not_in_arr = 0;
	size_t i = 0;

	AVLInsert(avl, arr);
	AVLInsert(avl, arr+1);
	AVLInsert(avl, arr+2);
	AVLInsert(avl, arr+3);
	AVLInsert(avl, arr+4);
	AVLInsert(avl, arr+5);
	AVLInsert(avl, arr+6);
	
	for (i=0 ; i<size ;++i)
	{
		if(*(arr+i) != *(int*)AVLFind(avl, arr+i))
		{
			++fail_count_Find;
			printf("line: %d\n" , __LINE__ );
		}
	}	
	
	if(NULL != AVLFind(avl, &num_not_in_arr))
	{
		++fail_count_Find;
		printf("line: %d\n" , __LINE__ );
	}
	
	printf("Test AVLFind  %s \n", fail_count_Find ? RED_FAIL : GREEN_SUCCESS);
	
	AVLDestroy(avl);
}

/*******************************************************************************/
void TestAVLRemove()
{
	avl_t* avl = AVLCreate(cmp_func);
	int arr[] = {50, 20, 70, 10, 40, 5, 15, 30, 45, 25, 35, 22, 60, 55, 52, 12, 46};
	size_t size = sizeof(arr)/sizeof(int);
	size_t i = 0;
	int fail_count_remove = 0;
	
	/*insert all elements*/
	for (i=0 ; i<size ;++i)
	{
		AVLInsert(avl, arr+i);
	}
	puts("********************start_insert*****************************"); 	
		Aux_Pre_Print_Tree_Avl(avl, 0);	
	puts("********************end_insert*****************************"); 		
	/*remove leaf: data=5*/
	AVLRemove(avl, arr + 5);
	--size;
	
	if (size != AVLSize(avl))
	{
		++fail_count_remove;
		printf("line: %d\n" , __LINE__ );
	}
	
	/*remove node with left child: data=60*/
	AVLRemove(avl, arr + 12);
	--size;
	
	if (size != AVLSize(avl))
	{
		++fail_count_remove;
		printf("line: %d\n" , __LINE__ );
	}
	
	/*remove node with right child: data=10*/
	AVLRemove(avl, arr + 3);
	--size;
	
	if (size != AVLSize(avl))
	{
		++fail_count_remove;
		printf("line: %d\n" , __LINE__ );
	}
	
	/*remove node with two children: data=20*/
	/*If the node's right child has left child*/
	AVLRemove(avl, arr + 1);
	--size;
	
	if (size != AVLSize(avl))
	{
		++fail_count_remove;
		printf("line: %d\n" , __LINE__ );
	} 
	puts("********************start_ 40*****************************"); 
	Aux_Pre_Print_Tree_Avl(avl, 0);
	/*remove node with two children: data=40*/
	/*If the node's right child has no left child*/
	AVLRemove(avl, arr + 4);
	--size;
	
	if (size != AVLSize(avl))
	{
		++fail_count_remove;
		printf("line: %d\n" , __LINE__ );
	}
			Aux_Pre_Print_Tree_Avl(avl, 0);
			
	puts("********************end 40*****************************"); 		
	printf("Test AVLRemove  %s \n", fail_count_remove ? RED_FAIL : GREEN_SUCCESS);
	AVLDestroy(avl);
}

/****************************************************************************/
void TestAVLRemoveRotation()
{
	avl_t* avl = AVLCreate(cmp_func);
	int arr[] = {20, 10, 24, 5, 4, 15, 16};
	int fail_count_rotation = 0;
	
	
	/*insert 20, 10, 24, 5*/
	AVLInsert(avl, arr);
	AVLInsert(avl, arr+1);
	AVLInsert(avl, arr+2);
	AVLInsert(avl, arr+3);
	
	if (2 != AVLHeight(avl))
	{
		fail_count_rotation++;
		printf("line: %d\n" , __LINE__ );
	}
	
	/*remove 24*/
	/*rotation LL*/
	AVLRemove(avl, arr + 2);
	if (1 != AVLHeight(avl))
	{
		fail_count_rotation++;
		printf("line: %d\n" , __LINE__ );
	}
		Aux_Pre_Print_Tree_Avl(avl, 0);	
	/*insert 4,15*/
	AVLInsert(avl, arr+4);
	AVLInsert(avl, arr+5);
		Aux_Pre_Print_Tree_Avl(avl, 0);	
	/*rotation LR*/
	AVLInsert(avl, arr+6);
	if (2 != AVLHeight(avl))
	{
		fail_count_rotation++;
		printf("line: %d\n" , __LINE__);
	}
		Aux_Pre_Print_Tree_Avl(avl, 0);	
	/*remove 4*/
	AVLRemove(avl, arr + 4);
	if (2 != AVLHeight(avl))
	{
		fail_count_rotation++;
		printf("line: %d\n" , __LINE__ );
	}
	
	/*rotation RR*/
	/*remove 5*/
	AVLRemove(avl, arr + 3);
	if (2 != AVLHeight(avl))
	{
		fail_count_rotation++;
		printf("line: %d\n" , __LINE__ );
	}
			Aux_Pre_Print_Tree_Avl(avl, 0);
	/*remove 15*/
	AVLRemove(avl, arr + 5);
	if (1 != AVLHeight(avl))
	{
		fail_count_rotation++;
		Aux_Pre_Print_Tree_Avl(avl, 0);
		printf("line: %d\n" , __LINE__ );
	}
	
	printf("Test AVLRemoveRotation  %s \n", fail_count_rotation ? RED_FAIL : GREEN_SUCCESS);
	AVLDestroy(avl);
}



