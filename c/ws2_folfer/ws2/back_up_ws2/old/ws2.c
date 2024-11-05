/***************************************
* Autor : Natty
* Reviewr : Michael
* Date : 03 / 11 / 2024
* Last update: 
*****************************************/
#include <stdio.h>  /* printf */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <math.h>   /* pow */
#include <stddef.h>/*size_t*/
#include <stdint.h>/*size_t*/

/***************************function declaration**************************/
void Swap(int* a, int* b);
void CopyArr(int* src, int *dest, int len_src);
int ComprInt(int* src, int *dest, int len_src);
void CopyArr(int* src, int *dest, int len_src);
void SwapSizeT(size_t* a, size_t* b);
void swapSizeTPointer(size_t** a, size_t** b);


void TestSwap();
void TestCopyArr();
void TestSwapSizeT();
void TestswapSizeTPointer();

/********************End of function declaration**************************/


int main()
{   

    puts("'TestSwap()'");
    TestSwap();
    
    puts("'TestCopyArr()'");
    TestCopyArr();
    
    puts("'TestSwapSizeT()'");
    TestSwapSizeT();
    
    puts("TestswapSizeTPointer()");
    TestswapSizeTPointer();
    
    return 0;
}



/*********Swap function*********/
/* Swaps 2 variables' values in the memory */
/* Arguments: two integers */
/* Return value: void  */

void Swap(int* a, int* b)
{	
    
    int tmp = *a;
    assert(a);
    assert(b);
    *a = *b;
    *b = tmp;
    return;
}

/*********Test Swap function*********/
/* Test Swap function */
/* Arguments: void */
/* Return value: void. massages according to the correctness */
void TestSwap(void)
{
  int a = 2, b = 3;
  int c = a, d = b;
  
   Swap(&a, &b);
   
   if ((c == b) && (d == a))
    {
       puts("'Swap()' Function works great");
    }
    else
	{
      puts("'Swap()' Function failed");
    }
}

/*********compare Arrays *********/
/* Compare 2 arrays */
/* Arguments: 2 pointers' integers */
/*  and length of the source array */
/* Return value: 0 success, -1 failure  */

int ComprInt(int* src, int *dest, int len_src)
{
    int i = 0;
    assert(src);
    assert(dest);
	for (i = 0; i < len_src; i++)
	{
	    if( *(dest +i ) != *(src + i))
	        {
	            return -1;
	        }
	}
    return 0;
}


/*********Copy Array function*********/
/* Copy an int array to another */
/* Arguments: 2 pointers' integers */
/*  and length of thes ource array */
/* Return value: void  */

void CopyArr(int* src, int* dest, int len_src)
{
    int i = 0;
    assert(src);
    assert(dest);
	for (i = 0; i < len_src; i++)
	{
	    *(dest +i) = *(src + i);
	}
    return;
}

/*********TestCopyArray function*********/
/* Test the CopyArr() function by using*/
/*Several inputs*/
/* Arguments: void */
/* Return value: void, Messages accorrding to success/failure  */
void TestCopyArr()
{
    int result = 0;
    int result1 = 0;
	int arr1[] = { 4, 8 ,-3, -9, 5, -10};
	int arr3[] = {0, 2, 3, -500, 6, 40};
	int arr2[] ={0};

	CopyArr(arr1, arr2, sizeof(arr1) / sizeof(arr1[0]));
	result = ComprInt(arr1, arr2, sizeof(arr1) / sizeof(arr1[0]));
	CopyArr(arr3, arr2, sizeof(arr3) / sizeof(arr3[0]));
	result1 = ComprInt(arr3, arr2, sizeof(arr3) / sizeof(arr3[0]));
	if(!result && !result1)
	{
	   puts("'CopyArr()' Function works great");
	}
	else if(!result)
	{
	   puts("'CopyArr()' Function failed to copy { 4, 8 ,-3, -9, 5, -10}");
	}
	else if(!result1) 
	{ 
	   puts("'CopyArr()' Function failed to copy {0, 2, 3, -500, 6, 40}");
	}
	else
	{
	   puts("'CopyArr()' Function failed for some unknown reason");
	}
}


/**********Swap Size_t function*********/
/* Swaps 2 variables' values of */
/* type size_t in the memory */
/* Arguments: two pointers of Size_t's data type */
/* Return value: void  */

void SwapSizeT(size_t* a, size_t* b)
{

    size_t tmp = *a;
    assert(a);
    assert(b);
    *a = *b;
    *b = tmp;
    return;
}

/********** Test Swap Size_t function*********/
/*- Test the SwapSizeT() function*/
/* Arguments: none*/
/*- Return: return a massage according to the correctness */
void TestSwapSizeT()
{
 /*SIZE_MAX == 18446744073709551615 */
  size_t a = 0, b = SIZE_MAX; 
  size_t c = a, d = b;
   SwapSizeT(&a, &b);
   if ((c == b) && (d == a))
    {
       puts("'SwapSizeT()' Function works great");
    }
   else
    {
       puts("'SwapSizeT()' Function failed");
    }

}

/**********Swap Size_t* function*********/
/* Swaps 2 variables' adresses values of */
/* type size_t* in the memory */
/* Arguments: 2 pointers to pointers of Size_t*'s data type */
/* Return value: void  */

void swapSizeTPointer(size_t** a, size_t** b)
{

    size_t* tmp = *a;
    assert(a);
    assert(b);
    
    *a = *b;
    *b = tmp;
    
    return;
}

/********** Test Swap Size_t* function*********/
/*- Test the swapSizeTPointer() function*/
/* Arguments: none*/
/*- Return: return a massage according to the correctness */
void TestswapSizeTPointer()
{
 /*SIZE_MAX == 18446744073709551615 */
  size_t a = 0;
  size_t b = SIZE_MAX; 
  size_t* ap = &a;
  size_t* bp = &b;
  size_t** app = &ap;
  size_t** bpp = &bp;

   swapSizeTPointer(&ap, &bp);
   if ((ap != &b) || (bp != &a))
    {
       puts("'swapSizeTPointer()' Function failed");
       puts("Pointers' swap failed");
    }
    else if( (a == SIZE_MAX) || (b == 0) )
    {
     puts("'swapSizeTPointer()' Function failed");
     puts("The values of the variables pointed by were changed");
    }
    else if( app != &ap || bpp != &bp)
    {
       puts("'swapSizeTPointer()' Function failed");
       puts("The adresses of the pointers were chacged");
    }
   else
    {
       puts("'swapSizeTPointer()' Function works great");
    }
    
    return;
}


