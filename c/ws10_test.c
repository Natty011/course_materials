/***************************************
* Author : Natty
* Reviewer : Idan
* Date : 28 / 11 / 2024
* Last update: 30 / 11 / 2024
*****************************************/

#include <stdio.h> /* puts */
#include <stdlib.h> /* size_t */
#include <string.h> /* memset, memcpy, memmove */

#define SIZEOF_VAR(object) (size_t)(&object+1) - (size_t)(&object)
#include "ws10.h" /* Memset, Memcpy, Memmove */
#define N 10


/***************************function declaration**************************/

static void TestMemset(void);
static int CompareIntArray(int arr1[], int arr2[], int n);

static void TestMemcpy1(void);
static void TestMemcpy2(void);
static int CompareCharArray(char arr1[], char arr2[], int n);


static void TestMemmove1(void);
static void TestMemmove2(void);

/***************************End of function declaration******************/

int main ()
{

  puts("=====================================================");
  puts("'TestMemset()'");
  TestMemset();
  puts("=====================================================");
  
  puts("'TestMemcpy()'");
  TestMemcpy1();
  TestMemcpy2();
  puts("=====================================================");
  
  puts("'TestMemmove()'");
  TestMemmove1();
  TestMemmove2();
  puts("=====================================================");
  
  


return 0;
}

/*** Test Memmove ***/
/* Compare  Memmove with the orginal memmove
   using align and non-align struct,
   and also with chars' and integers' arrays 
   with and w/o overlapping*/

static void TestMemmove1(void)
{
  char str1[100] = "Learningisfun"; 
  char str2[100] = "Learningisfun"; 
  char *first1, *second1, *first2, *second2;
  
  char myname[] = "Amlendra";   
   struct
   {
    	char name[40];
   		int age;
   } person1, person2, person3;
   
   
  first1 = str1; 
  second1 = str1;
  first2 = str2; 
  second2 = str2;
   
 /* There is an overlapping of 2 bytes --> "is" */
  memmove(second1 + 8, first1, 10); 
  Memmove(second2 + 8, first2, 10);
  
   if(CompareCharArray(str1, str2, sizeof(str1)))

   {
       puts("'Memmove()' Function failed in comparison of chars' arrays\
             with an ovarlapping of 2 bytes");
   }
   
   memmove ( person1.name, myname, strlen(myname)+1 );
   person1.age = 30;
   
   memmove ( &person2, &person1, sizeof(person1) );
   Memmove ( &person3, &person1, sizeof(person1) );
   
   if(CompareCharArray(person2.name, person3.name, sizeof(myname)) || 
     (person2.age != person3.age))
  {
      puts("'Memmove()' Function failed in comparison of an aligned struct");
  }
   
   puts("Test1: 'Memmove()' Function works great");
   return;
  
}

static void TestMemmove2(void)
{

    int arr1[N] = { 0 };
    int arr2[N] = { 1 };
    int arr3[N] = { 3, 10, -4, -8 , -2, 0, 0, 0, 0, 1 };

	#pragma pack(push, 1)
	typedef struct X
	{
    char c2;
    double d1; 
    char c; 
    int n;  
    float f;

	}X_t, *pX_t;
	
	typedef struct Y
	{
    char c2;
    double d1; 
    char c; 
    int n;  
    float f;

	}Y_t, *pY_t;
    Y_t y_dest1, y_dest2;
	pY_t p_dest1, p_dest2;
	X_t X1;
    pX_t pX1;
    X1.n = 4;
    X1.c = 'A';
    X1.d1 = 5.44;
    X1.c2 = 'b';
    X1.f = 2.25;
    pX1 = &X1;
    
    y_dest1.n = 4;
    y_dest1.c = 'A';
    y_dest1.d1 = 5.44;
    y_dest1.c2 = 'b';
    y_dest1.f = 2.25;
    p_dest1 = &y_dest1;
    
    y_dest2.n = 5;
    y_dest2.c = 'f';
    y_dest2.d1 = 2.74;
    y_dest2.c2 = 'q';
    y_dest2.f = 3.75;
    p_dest2 = &y_dest2;


   memmove(p_dest1, pX1, sizeof(*pX1));
   Memmove(p_dest2, pX1, sizeof(*pX1));

   if ( (p_dest1->n != p_dest2->n) || (p_dest1->c != p_dest2->c)
       || (p_dest1->d1 != p_dest2->d1) || (p_dest1->c2 != p_dest2->c2) 
       || (p_dest1->f != p_dest2->f))
   {
       puts("'Memmove()' Function failed in comparison of non-aligned struct");
   }  

   #pragma pack(pop)
   
    y_dest1.n = 4;
    y_dest1.c = 'A';
    y_dest1.d1 = 5.44;
    y_dest1.c2 = 'b';
    y_dest1.f = 2.25;
    p_dest1 = &y_dest1;
    
    y_dest2.n = 5;
    y_dest2.c = 'f';
    y_dest2.d1 = 2.74;
    y_dest2.c2 = 'q';
    y_dest2.f = 3.75;
    p_dest2 = &y_dest2;
   
    memmove(p_dest1, pX1, sizeof(*pX1));
    Memmove(p_dest2, pX1, sizeof(*pX1));
    
    if ( (p_dest1->n != p_dest2->n) || (p_dest1->c != p_dest2->c)
       || (p_dest1->d1 != p_dest2->d1) || (p_dest1->c2 != p_dest2->c2) 
       || (p_dest1->f != p_dest2->f))
    {
       puts("'Memmove()' Function failed in comparison of an aligned struct");
    }  
    
    memmove(arr1, arr3, sizeof(arr1));
    Memmove(arr2, arr3, sizeof(arr2));
    if(CompareIntArray(arr1, arr2, sizeof(arr1)/sizeof(arr1[0])))
    {
        puts("'Memmove()' Function failed in comparison of ints' arrays");
    }
    
    puts("Test2: 'Memmove()' Function works great");
    return;
}



/*** Test Memcpy ***/
/* Compare  Memcpy with the orginal memcpy
   using align and non-align struct,
   and also with chars' and integers' arrays  */

static void TestMemcpy1(void)
{
   const char src[50] = "Tutorialspoint";
   char dest1[50];
   char dest2[50];
   
   char first_str1[] = "Tutorials";
   char first_str2[] = "Tutorials";
   char sec_str[] = "Point";
   
   char myname[] = "Amlendra";   
   struct
   {
    	char name[40];
   		int age;
   } person1, person2, person3;
 
   strcpy(dest1,"Heloooo!!");
   strcpy(dest2,"Heloooo!!"); 
 	
   memcpy(dest1, src, sizeof(src));
   Memcpy(dest2, src, sizeof(src));
	
   memcpy(first_str1, sec_str, sizeof(sec_str));
   Memcpy(first_str2, sec_str, sizeof(sec_str));
 
   if(CompareCharArray(dest1, dest2, strlen(src) + 1) ||
      CompareCharArray(first_str1, first_str2, sizeof(sec_str))  )
   {
       puts("'Memcpy()' Function failed in comparison of chars' arrays");
   }

   memcpy ( person1.name, myname, strlen(myname)+1 );
   person1.age = 30;
   
   memcpy ( &person2, &person1, sizeof(person1) );
   Memcpy ( &person3, &person1, sizeof(person1) );
   
   if(CompareCharArray(person2.name, person3.name, sizeof(myname)) || 
     (person2.age != person3.age))
  {
      puts("'Memcpy()' Function failed in comparison of an aligned struct");
  }
  
    puts("Test1: 'Memcpy()' Function works great");
    return;

}

static void TestMemcpy2(void)
{

    int arr1[N] = { 0 };
    int arr2[N] = { 1 };
    int arr3[N] = { 3, 10, -4, -8 , -2, 0, 0, 0, 0, 1 };

	#pragma pack(push, 1)
	typedef struct X
	{
    char c2;
    double d1; 
    char c; 
    int n;  
    float f;

	}X_t, *pX_t;
	
	typedef struct Y
	{
    char c2;
    double d1; 
    char c; 
    int n;  
    float f;

	}Y_t, *pY_t;
    Y_t y_dest1, y_dest2;
	pY_t p_dest1, p_dest2;
	X_t X1;
    pX_t pX1;
    X1.n = 4;
    X1.c = 'A';
    X1.d1 = 5.44;
    X1.c2 = 'b';
    X1.f = 2.25;
    pX1 = &X1;
    
    y_dest1.n = 4;
    y_dest1.c = 'A';
    y_dest1.d1 = 5.44;
    y_dest1.c2 = 'b';
    y_dest1.f = 2.25;
    p_dest1 = &y_dest1;
    
    y_dest2.n = 5;
    y_dest2.c = 'f';
    y_dest2.d1 = 2.74;
    y_dest2.c2 = 'q';
    y_dest2.f = 3.75;
    p_dest2 = &y_dest2;



   memcpy(p_dest1, pX1, sizeof(*pX1));
   Memcpy(p_dest2, pX1, sizeof(*pX1));

   if ( (p_dest1->n != p_dest2->n) || (p_dest1->c != p_dest2->c)
       || (p_dest1->d1 != p_dest2->d1) || (p_dest1->c2 != p_dest2->c2) 
       || (p_dest1->f != p_dest2->f))
   {
       puts("'Memcpy()' Function failed in comparison of non-aligned struct");
   }  

   #pragma pack(pop)
   
    y_dest1.n = 4;
    y_dest1.c = 'A';
    y_dest1.d1 = 5.44;
    y_dest1.c2 = 'b';
    y_dest1.f = 2.25;
    p_dest1 = &y_dest1;
    
    y_dest2.n = 5;
    y_dest2.c = 'f';
    y_dest2.d1 = 2.74;
    y_dest2.c2 = 'q';
    y_dest2.f = 3.75;
    p_dest2 = &y_dest2;
   
    memcpy(p_dest1, pX1, sizeof(*pX1));
    Memcpy(p_dest2, pX1, sizeof(*pX1));
    
    if ( (p_dest1->n != p_dest2->n) || (p_dest1->c != p_dest2->c)
       || (p_dest1->d1 != p_dest2->d1) || (p_dest1->c2 != p_dest2->c2) 
       || (p_dest1->f != p_dest2->f))
    {
       puts("'Memcpy()' Function failed in comparison of an aligned struct");
    }  
    
    memcpy(arr1, arr3, sizeof(arr1));
    Memcpy(arr2, arr3, sizeof(arr2));
    if(CompareIntArray(arr1, arr2, sizeof(arr1)/sizeof(arr1[0])))
    {
        puts("'Memcpy()' Function failed in comparison of ints' arrays");
    }
    
    puts("Test2: 'Memcpy()' Function works great");
    return;
}

/*  Compare 2 arrays of chars' type */
static int CompareCharArray(char arr1[], char arr2[], int n)
{
    int i = 0;
    int res = 0;
    
    for (i=0; i<n; i++)
    {
        if(arr1[i] != arr2[i])
        {
        	res = 1;
        	return res;
        }
    }
      
    return res;
} 


/*** Test Memset ***/
/* Compare  Memset with orginal memset
   using align and non-align struct,
   and also with integers' arrays  */
static void TestMemset(void)
{
	int arr1[N] = { 0 };
    int arr2[N] = { 1 };

    size_t *ptr_word1 = NULL;
    size_t *ptr_word2 = NULL;
    size_t word1 = 2 ;
    size_t word2 = -9 ;
    
	#pragma pack(push, 1)
	typedef struct X
	{
    char c2;
    char c1; 
    char c; 
    int n;  
    int n1;

	}X_t, *pX_t;


    X_t X1, X2;
    pX_t pX1, pX2;
    X1.n = 4;
    X1.c = 'A';
    X1.c1 = 'b';
    X1.c2 = 'b';
    X1.n1 = 4;
    pX1 = &X1;
    
    X2.n = 3;
    X2.c = 'T';
    X2.c1 = 'U';
    X2.c2 = 'F';
    X2.n1 = 9;
    pX2 = &X2;
    
    pX1 = memset(pX1, 1, SIZEOF_VAR(X1));    
    pX2 = Memset(pX2, 1, SIZEOF_VAR(X2));    
    
    if ((pX1->n != pX2->n) || (pX1->c != pX2->c) || (pX1->c1 != pX2->c1)
         || (pX1->c2 != pX2->c2) || (pX1->n1 != pX2->n1))
    {
        puts("'Memset()' Function failed in comparison of non-aligned struct");
    }
	#pragma pack(pop)

    memset(pX1, 2, SIZEOF_VAR(X1));    
    Memset(pX2, -2, SIZEOF_VAR(X2)); 
       
    X1.n = 4;
    X1.c = 'A';
    X1.c1 = 'b';
    X1.c2 = 'b';
    X1.n1 = 4;
    pX1 = &X1;
    
    X2.n = 3;
    X2.c = 'T';
    X2.c1 = 'U';
    X2.c2 = 'F';
    X2.n1 = 9;  
    pX2 = &X2;
    
    pX1 = memset(pX1, 1, SIZEOF_VAR(X1));    
    pX2 = Memset(pX2, 1, SIZEOF_VAR(X2));    
    
    if ((pX1->n != pX2->n) || (pX1->c != pX2->c) || (pX1->c1 != pX2->c1)
         || (pX1->c2 != pX2->c2) || (pX1->n1 != pX2->n1))
    {
        puts("'Memset()' Function failed in comparison of an aligned struct");
    }
    
    
    memset(arr1, -4, sizeof(arr1));
    Memset(arr2, -4, sizeof(arr2));
    
    if(CompareIntArray(arr1, arr2, sizeof(arr1)/sizeof(arr1[0])))
    {
        puts("'Memset()' Function failed in comparison of ints' arrays");
    }


    ptr_word1 = &word1; /* word1 = 2 */
    ptr_word2 = &word2; /* word2 = -9 */
    
    memset(ptr_word1, -27, 8);
    Memset(ptr_word2, -27, 8);

	if( word1 != word2 )
	{
	    puts("'Memset()' Function failed in comparison of size_t types");
	}
	
    puts("'Memset()' Function works great");
    return;
}
/*  Compare 2 arrays of integer type */
static int CompareIntArray(int arr1[], int arr2[], int n)
{
    int i = 0;
    int res = 0;
    
    for (i=0; i<n; i++)
    {
        if(arr1[i] != arr2[i])
        {
        	res = 1;
        	return res;
        }
    }
      
    return res;
} 

