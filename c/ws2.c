/***************************************
* Autor : Natty
* Reviewr : 
* Date : 04 / 11 / 2024
* Last update: 09 / 11 / 2024
*****************************************/

#include <stdio.h>  /* printf, puts */
#include <assert.h> /* assert */
#include <stdint.h> /*size_t , SIZE_MAX*/
#include <stdbool.h> /* bool type */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc */

/***************************function declaration**************************/

void Swap(int* a, int* b);
static void TestSwap(void);

void CopyArr(int* src, int *dest, int len_src);
static void TestCopyArr(void);
int ComprInt(int* src, int *dest, int len_src);

void SwapSizeT(size_t* a, size_t* b);
static void TestSwapSizeT();

void SwapSizeTPointer1(size_t** a, size_t** b);
static void TestSwapSizeTPointer1();

void SwapSizeTPointer2(size_t** a, size_t** b);
static void TestSwapSizeTPointer2();

bool CheckPalindrome(char* str);
static void TestCheckPalindrome(void);

char* SpaceReview(char* str);
static void TestSpaceReview(void);

/********************End of function declaration**************************/


int main(void)
{   

    puts("=====================================================");
    puts("'TestSwap()'");
    TestSwap();
    puts("=====================================================");
        
    puts("'TestCopyArr()'");
    TestCopyArr();
    puts("=====================================================");
        
    puts("'TestSwapSizeT()'");
    TestSwapSizeT();
    puts("=====================================================");
        
    puts("TestSwapSizeTPointer1()");
    TestSwapSizeTPointer1();
    puts("=====================================================");
        
    puts("TestSwapSizeTPointer2()");
    TestSwapSizeTPointer2();
    puts("=====================================================");
    
    puts("TestCheckPalindrome()");
    TestCheckPalindrome();
    puts("=====================================================");
    
    puts("TestSpaceReview()");
    TestSpaceReview();
    puts("=====================================================");
    
        
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
static void TestSwap(void)
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
static void TestCopyArr(void)
{
    int result = 0;
    int result1 = 0;
    int arr1[] = { 4, 8 ,-3, -9, 5, -10};
    int arr3[] = {0, 2, 3, -500, 6, 40};
    int arr2[100] ={0};

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
static void TestSwapSizeT(void)
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

void SwapSizeTPointer1(size_t** a, size_t** b)
{

    size_t* tmp = *a;
    assert(a);
    assert(b);
    
    *a = *b;
    *b = tmp;
    
    return;
}

/********** Test Swap Size_t* function*********/
/*- Test the swapSizeTPointer1() function*/
/* Arguments: none*/
/*- Return: return a massage according to the correctness */
static void TestSwapSizeTPointer1(void)
{
 /*SIZE_MAX == 18446744073709551615 */
  size_t a = 0;
  size_t b = SIZE_MAX; 
  size_t* ap = &a;
  size_t* bp = &b;
  size_t** app = &ap;
  size_t** bpp = &bp;

   SwapSizeTPointer1(&ap, &bp);
   if ((ap != &b) || (bp != &a))
    {
       puts("'SwapSizeTPointer1()' Function failed");
       puts("Pointers' swap failed");
    }
    else if( (a == SIZE_MAX) || (b == 0) )
    {
     puts("'SwapSizeTPointer1()' Function failed");
     puts("The values of the variables pointed by were changed");
    }
    else if( app != &ap || bpp != &bp)
    {
       puts("'SwapSizeTPointer1()' Function failed");
       puts("The adresses of the pointers were chacged");
    }
   else
    {
       puts("'SwapSizeTPointer1()' Function works great");
    }
    
    return;
}

/**********Swap Size_t* function*********/
/* Swaps 2 variables' adresses values of */
/* type size_t* in the memory  based on the 'SwapSizeT' function*/
/* Arguments: 2 pointers to pointers of Size_t*'s data type */
/* Return value: void  */

void SwapSizeTPointer2(size_t** a, size_t** b)
{
    assert(a);
    assert(b);
    
    SwapSizeT((size_t*)a, (size_t*)b);
    
    return;
}

/********** Test Swap Size_t* function*********/
/*- Test the SwapSizeTPointer2() function*/
/* Arguments: none*/
/*- Return: return a massage according to the correctness */
static void TestSwapSizeTPointer2(void)
{

/*SIZE_MAX == 18446744073709551615 */
  size_t a = 0;
  size_t b = SIZE_MAX; 
  size_t* ap = &a;
  size_t* bp = &b;
  size_t** app = &ap;
  size_t** bpp = &bp;

   SwapSizeTPointer2(&ap, &bp);
   if ((ap != &b) || (bp != &a))
    {
       puts("'SwapSizeTPointer2()' Function failed");
       puts("Pointers' swap failed");
    }
    else if( (a == SIZE_MAX) || (b == 0) )
    {
     puts("'SwapSizeTPointer2()' Function failed");
     puts("The values of the variables pointed by were changed");
    }
    else if( app != &ap || bpp != &bp)
    {
       puts("'SwapSizeTPointer2()' Function failed");
       puts("The adresses of the pointers were chacged");
    }
   else
    {
       puts("'SwapSizeTPointer2()' Function works great");
    }
    
    return;
}

/**********CheckPalindrome function*********/
   /* Checks if a word is a palindrome */
   /* Note: (1) the empty string is a palindrome.
           (2) A string constituted only by a single character is a palindrome.
          (3) A string c s d is a palindrome, if s is a palindrome and c is a
              character equal to d; There is a sensitivity to character letters.
          () Nothing else is a palindrome.
   
   */
   
bool CheckPalindrome(char* str)
{

    int low = 0;
    int high = strlen(str) - 1;
    
    assert(str);
  
    if ( high == -1) /* An empty string is a palindrome  */
    {
        return true;
    }
    
    /* compares elemnts of a string that are in a symmetrical
       in relation to the middle of it */
  
    while (high >= low)
    {
        if (str[low] != str[high]) /* Isn't a palindrome */ 
        {
            return false;
        }
      
        ++low;
        --high;
    }
 
    return true; /* Is a palindrome */ 
}

/********** Test CheckPalindrome function*********/
/*- Test the CheckPalindrome() function*/
/* Arguments: none */
/*- Return: return a massage according to the correctness */

static void TestCheckPalindrome(void)
{
    char s1[] = "h92!29h";      /*An odd palindrome */
    char s2[] = "h92!!29h";   /* An even palindrome */
    char s3[] = "h92!?29h";  /* Isn't a palindrome */ 
    char s4[] = "";         /* An empty string - Even palindrome */
    char s5[] = "H92!29h"; /* Isn't a palindrome */
    char s6[] = "A";      /* Odd palindrome */


   if ( !CheckPalindrome(s1) )
    {
       puts("'CheckPalindrome()' failed in an odd palindrome");
    }
    
    else if (!CheckPalindrome(s2))
    {
       puts("'CheckPalindrome()' failed in an even palindrome");
    }
    
    else if (CheckPalindrome(s3))
    {
       puts("'CheckPalindrome()' failed if it isn't a palindrome");
    }
    
    else if (!CheckPalindrome(s4))
    {
       puts("'CheckPalindrome()' failed in an empty string palindrome");
    }
    
    else if (CheckPalindrome(s5))
    {
       puts("'CheckPalindrome()' failed if it isn't a palindrome");
    }
    
    else if (!CheckPalindrome(s6))
    {
       puts("'CheckPalindrome()' failed in a single odd palindrome");
    }
    
    else
    {
        puts("'CheckPalindrome()' Function works great");
    }

    return;
}

/********** SpaceReview function*********/
/* The function removing tab('\t') and space(' ') characthers from start
       and end of a string. If each chracthers are showing in the middle of the
       string in a sequence duplication than the function removing all of the
       duplication except of one characther.*/
   
/*Return Value: The same string with the above constrains*/ 
/* Note: (1) Double Backslash before white case cancelled the escape sequence.
   	     a.k.a: '\\t' is a reguler string of '\' and 't'.  	      	
           (2) '\ ' is an illegal escape sequence so it should be '\\ ';   */

char* SpaceReview(char* str)
{
    size_t str_len = strlen(str);
    char* p = NULL;
    size_t low = 0, high = str_len -1, i = 0, j=0 ;
    int flag = 0;
    
    
    assert(str);
    
    if ( str_len == 0 ) /* An empty string */
    {
        return str;
    }
    /* Find the First and End of a non white space indices*/
    while ( low <= high ) 
    {
        if( (*(str + low) == ' ') || (*(str + low) == '\t') )
        {
            ++low;
            flag = 1;
        }
        
        if( (*(str + high) == ' ') || (*(str + high) == '\t') )
        {
            --high;
            flag = 1;
        }
        
        if( flag != 0 )
        {
            flag = 0; 
        }
        
        else
        {
            break;
        }        
    }
    
    if ( low > high ) /* The entire string is a white space */
    {
        *str = '\0'; /* Return an empty string */
        return str;
    }
    
    p = (char*)malloc( sizeof(char) * (str_len+1) );
    
    if (NULL == p)
    {
        puts("Failed in an allocation memory");
        return NULL;
    }
    
    while ( low <= high ) /* There is at least one non white space character */
    {
        if ( low == high )
        {
            *( p +i ) = *( str + high );
            *( p + i +1) = '\0'; /* Termination of the string */
            
            break; 
        }
        
        if ( ((*(str + low) == *(str + low +1)) && (*(str + low +1) == ' ')) ||
             ((*(str + low) == *(str + low +1)) && (*(str + low +1) == '\t')) )
          
            {
                ++low;
            }
        else
            {
                *( p +i ) = *( str + low );
                ++low;
                ++i;
            } 
       
    }
    
    while ( *( p + j) != '\0' ) /* Copy the new string to str */
    {
        *( str + j ) = *( p + j); 
        ++j;
    }
    
     *( str + j ) = '\0';
     
     free(p);
    
    return str;
}

/********** Test SpaceReview function*********/
/*- Test the SpaceReview() function*/
/* Arguments: none */
/*- Return: return a massage according to the correctness */

static void TestSpaceReview(void)
{
    /* Checks strings with different 'start', 'end' and 'middle' white space*/
    /*Checks ('\\t') and ('\\ ') as regulars characthers and not 
      as an escape sequence */
    
    char s1[] = " \t \t   a    \\  b  \\t   \t  \t\t  c\t\td 3\t4 5T \t  ";
    char s2[] = "  \t \t a \\   b  \\t \t  \t\t   c\t\t\td  3\t\t4  5T\t\t \t  ";
    
    /* Checks one characther inside the string */
    char s3[] = " \t  \ta   \t\t\t  "; 
    char s4[] = " \t\ta \t \t \t\t\t \t  ";
    
    
    /* Checks strings with only white space characters*/
    char s5[] = " \t  \t    \t\t\t  "; 
    char s6[] = " \t\t\t \t \t \t\t\t \t  ";
    
    
    /* Checks strings with only white space characters or an empty string*/
 
    char s7[] = ""; 
    char s8[] = " \t\t\t \t \t \t\t\t \t  ";
    
    if (strcmp(SpaceReview(s1), SpaceReview(s2)))
    {
       puts("'SpaceReview()' failed to remove start, end or middle white space ");
    }
    
    else if (strcmp(SpaceReview(s3), SpaceReview(s4)))
    {
       puts("'SpaceReview()' failed to remove start, end or middle white space ");
       puts(" in a string with a single non white space ");
    }
    
    else if (strcmp(SpaceReview(s5), SpaceReview(s6)))
    {
       puts("'SpaceReview()' failed to remove start, end or middle white space ");
       puts(" in a string with an only white space characters ");
    }
    
    else if (strcmp(SpaceReview(s7), SpaceReview(s8)))
    {
       puts("'SpaceReview()' failed in an empty string ");
    }
    
    else
    {
        puts("'SpaceReview()' Function works great");
    }
    
    return;
} 
    

