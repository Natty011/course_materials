/*******************************************************************************
*
*	Auther:		rawan Nabwany
*	Reviewer:	
*	Date:		12/02/25
*	worksheet:  C::Binary Tree Recursive
*
*******************************************************************************/
#include <stdio.h> 	/*	printf	*/
#include "avl.h"


enum
{
	SUCCESS = 0 ,
	FAIL = 1
};

/*****************************************************************************/
/*************			 DECLARATIONS                               **********/
/*****************************************************************************/
int TestInsertRemove( void );
int TestInsertRemove2( void );
int TestFind( void );
int TestForEach( void );


/*****************************************************************************/
/*************			 STATIC FUNCTIONS                           **********/
/*****************************************************************************/
static int PrintForEach( void *check_data , void *user_param )
{	
	(void)user_param;
	 printf("%d\t" , *(int*)check_data );
	 
	 return SUCCESS;
}


static int CompareFunc( void* check_data , void* user_param )
{
	return ( *(int*)check_data - *(int*)user_param ) ; 

}

static int AddTen( void* check_data , void* user_param  )
{
	*(int*)check_data += *(int*)user_param;
	
	return SUCCESS ;

}


/*****************************************************************************/
/*************			          MAIN                              **********/
/*****************************************************************************/
int main()
{
	int res = SUCCESS;
	
	res += TestInsertRemove();
	res += TestInsertRemove2();
	res += TestFind();
	res += TestForEach();
	
	if ( res )
	{
		printf("At Least One Function Failed\n");
	
	}
	
	else
	{
		printf("All Functions Succeeded\n");
	
	}
	
	return 0;
}



int TestInsertRemove()
{
	size_t i = 0;
	int res = SUCCESS;
	
	int data[] = { 100 , 20 , 200 , 10 , 30 , 150 , 300 } ; 
	size_t size = sizeof( data ) / sizeof( data[ 0 ] );
	
	avl_t *avl = AVLCreate( (cmp_func_t)CompareFunc );
	
	if( !avl )
	{
		printf("Creation Failed\n");
	}
	
	if( !AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	for ( i = 0 ; i < size ; ++i  )
	{
		res = AVLInsert( avl , &data[i] );
		if( res )
		{
			return FAIL;
		}
	}
	
	PrintTree( avl );
	
	if( AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	if( size != AVLSize( avl ) )
	{
		return FAIL;
	}

	for ( i = 0 ; i < size ; ++i  )
	{
		AVLRemove( avl , &data[i] );
	}
	
	if( !AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	if( 0 != AVLSize( avl ) )
	{
		return FAIL;
	}

	
	AVLDestroy(avl);
	avl = NULL;
	
	return SUCCESS;

}


int TestInsertRemove2()
{
	size_t i = 0;
	int res = SUCCESS;
	
	int data[] = { 25 , 50 , 40 , 30 , 20 ,10 } ; 
	size_t size = sizeof( data ) / sizeof( data[ 0 ] );
	
	avl_t *avl = AVLCreate( (cmp_func_t)CompareFunc );
	
	if( !avl )
	{
		printf("Creation Failed\n");
	}
	
	if( !AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	for ( i = 0 ; i < size ; ++i  )
	{
		res = AVLInsert( avl , &data[i] );
		if( res )
		{
			return FAIL;
		}
	}
	
	printf("\n\n\n\n");
	PrintTree( avl );
	
	if( AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	if( size != AVLSize( avl ) )
	{
		return FAIL;
	}

	for ( i = 0 ; i < size - 1 ; ++i  )
	{
		AVLRemove( avl , &data[i] );
		printf("\n\n\n\n");
		PrintTree( avl );
	}
	
	AVLRemove( avl , &data[size - 1] );
	
	if( !AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	if( 0 != AVLSize( avl ) )
	{
		return FAIL;
	}

	
	AVLDestroy(avl);
	avl = NULL;
	
	return SUCCESS;

}


int TestFind()
{
	size_t i = 0;
	int res = SUCCESS;
	int data1 = 8 , data2 = 12 , data3 = 17 , data4 = 9;
	
	int data[] = { 10 , 8 , 12 , 20 , 17 } ; 
	size_t size = sizeof( data ) / sizeof( data[ 0 ] );
	
	avl_t *avl = AVLCreate( (cmp_func_t)CompareFunc );
	
	if( !avl )
	{
		printf("Creation Failed\n");
	}
	
	for ( i = 0 ; i < size ; ++i  )
	{
		res = AVLInsert( avl , &data[i] );
		if( res )
		{
			return FAIL;
		}
	}
	
	printf("\n\n\n\n");
	PrintTree( avl );
	
	if( AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	if( size != AVLSize( avl ) )
	{
		return FAIL;
	}
	
	res = *(int*)AVLFind( avl , &data1 );
	
	if( res != data1)
	{
		return FAIL;
	}
	
	res = *(int*)AVLFind( avl , &data2 );
	
	if( res != data2)
	{
		return FAIL;
	}
	
	res = *(int*)AVLFind( avl , &data3 );
	
	if( res != data3)
	{
		return FAIL;
	}
	
	if( NULL != AVLFind( avl , &data4 ) ) 
	{
		return FAIL;
	}
		
	for ( i = 0 ; i < size - 1 ; ++i  )
	{
		AVLRemove( avl , &data[i] );
		printf("\n\n\n\n");
		PrintTree( avl );
	}
	
	AVLRemove( avl , &data[size - 1] );
	
	AVLDestroy(avl);
	avl = NULL;
	
	return SUCCESS;


}

int TestForEach()
{
	size_t i = 0;
	int res = SUCCESS;
	int ten = 10 ;
	
	int data[] = { 10 ,12 , 8 , 20 , 17 , 30 , 42 , 50}; 
	size_t size = sizeof( data ) / sizeof( data[ 0 ] );
	
	avl_t *avl = AVLCreate( (cmp_func_t)CompareFunc );
	
	if( !avl )
	{
		printf("Creation Failed\n");
	}
	
	for ( i = 0 ; i < size ; ++i  )
	{
		res = AVLInsert( avl , &data[i] );
		if( res )
		{
			return FAIL;
		}
	}
	
	printf("\n\n\n\n");
	PrintTree( avl );
	
	if( AVLIsEmpty( avl ) )
	{
		return FAIL;
	
	}
	
	if( size != AVLSize( avl ) )
	{
		return FAIL;
	}
	
	
	printf("\nFor Each In Order\n");
	AVLForEach( avl , PrintForEach , NULL , IN_ORDER );
	
	printf("\nFor Each Pre Order\n");
	AVLForEach( avl , PrintForEach , NULL , PRE_ORDER );
	
	printf("\nFor Each Post Order\n");
	AVLForEach( avl , PrintForEach , NULL , POST_ORDER );
	
	
	printf("\nFor Each After Adding Ten\n");
	AVLForEach( avl , AddTen , &ten , IN_ORDER );
	AVLForEach( avl , PrintForEach , NULL , IN_ORDER );

	AVLDestroy(avl);
	avl = NULL;
	
	return SUCCESS;

}

