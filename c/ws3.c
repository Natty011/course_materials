/***************************************
* Autor : Natty
* Reviewr : 
* Date : 10 / 11 / 2024
* Last update: 10 / 11 / 2024
*****************************************/

#include <stdio.h>  /* printf, puts */
#include <assert.h> /* assert */
#include <stdint.h> /*size_t , SIZE_MAX*/
#include <stdbool.h> /* bool type */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc free, exit, EXIT_FAILURE */


/***************************function declaration**************************/

int* SumEachRow(int* mat, int* result, size_t row, size_t col);
static void TestSumEachRow(void);

size_t JoseProb(size_t* arr, size_t n);
static void TestJoseProb(void);

/********************End of function declaration**************************/


int main(void)
{   

    puts("=====================================================");
    puts("'TestSumEachRow()'");
    TestSumEachRow();
    puts("=====================================================");
    
    puts("'TestJoseProb()'");
    TestJoseProb();
    puts("=====================================================");
    
    
    return 0;
}

/********** SumEachRow function*********/
/* Summing the values of each row */
/* Return  Value: Result of each summing row into arrey pointer 'res'.*/ 
/* Note: (1) arrey pointer 'res' must be initialized to zeros. 
         (2) Must to casting 'mat' to int* for any matrix */ 
           
int* SumEachRow(int* mat, int* res, size_t row, size_t col)
{

    size_t r = 0;
    size_t c = 0;

    assert(mat);
    assert(res);
    
     for ( r = 0; r < row; ++r) /* runs on each rows*/
     {
         for (c = 0; c < col ; ++c) /* runs on each coll inside each rows*/
         {
              *(res+r) = (*((mat +(col)*r) + c)) + *(res+r);
         } 
     }
     
    return res;    
}

/*********TestSumEachRow function*********/
/* Test the SumEachRow() function by using
   Several inputs */
/* Arguments: void */
/* Return value: void, Messages accorrding to success/failure */

static void TestSumEachRow(void)
{
   size_t r = 0;
   size_t c = 0;
   int expect_res = 0;
   int* res = NULL;
   int result[4] = { 0 };
   int mat[4][2] = { {2, 5}, {-2, -6}, {-3, 6}, {9, -4 }};
                   
   res = SumEachRow((int*)mat, result, 4, 2); 
     
   for ( r = 0; r < 4; ++r) /* runs on rows*/
   {
       for (c = 0; c < 2 ; ++c) /* runs on col */ 
       {
            expect_res += mat[r][c];
       }
          
       if (expect_res != res[r])
       {
           puts("'SumEachRow()' Function failed");
       } 
          
       expect_res = 0;
   }
        
   puts("'SumEachRow()' Function works great");

   return;
}

/********** JoseProb function*********/
/* The last soldier that did not get kiss in a soldier circal standing */
/* Return  Value: the index of the soldier that left without kiss .*/ 
/* Note: (1) TBD arrey pointer 'arr' must be initialized to zeros. */

size_t JoseProb(size_t* arr, size_t n)
{
    size_t size = n;
    size_t i = 0;
    assert(arr);
    
    for (i = 0; i < n; ++i )
    {
        arr[i] = i + 1;
    }
 
    i = 0;
    
    while( size > 1 )
    {
        if( arr[ i % n] )
        {

                if ( arr[ (i+1)%n] ) /* Kiss imidiatlly after i */
                {
                    arr[ (i+1)%n] = 0; /* kiss the next one following */
                    --size; /* resize after kissing */
                    ++i;

                    while(!arr[i%n]) /* find the next one that alive */
                    {
                    ++i;
                    }

                }
                
                
                else if ( !arr[ (i+1)%n])  /* Not imidiatlly after i */
                {
                    while(!arr[ (i+1)%n]) /* find the next one that not dead and kiss him */
                    {
                    ++i;
                    }
                    arr[ (i+1)%n] = 0;
                    --size; /* resize after kissing */
                }
            
         }
                    
        else
        {
           ++i;
        }
    }
       
    for (i = 0; i < n; ++i )
    {
        if (arr[i])
         {
             return i;
         }
    }
     
   return i;  /* Won't get here */
}

/*********TestJoseProb function*********/
/* Test the JoseProb() function by using
   Several inputs */
/* Arguments: void */
/* Return value: void, Messages accorrding to success/failure */

static void TestJoseProb(void)
{
   size_t arr[100] = { 0 };
   size_t index =  SIZE_MAX;
   index = JoseProb(arr, 100);
   
   if ( index != 72 || arr[index] !=73)
   {
       puts("'JoseProb()' Function failed");
   }
   
   else
   {
       puts("'JoseProb()' Function works great");
   }
   
   return;
}



