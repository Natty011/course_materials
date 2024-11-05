#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*function declaration*/
void Swap(int* a, int* b);
/*function definition*/
/*- swap 2 variables in the memory */
/*- Return:  */
void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

/*function declaration*/
void TestSwap();
/*function definition*/
/*- Test the Swap() function*/
/*- Return: return a massage according to correctness  */
void TestSwap()
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

int main()
{

    TestSwap();

    return 0;
}
