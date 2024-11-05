/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*function declaration*/
int FlipInt(int n);
/*function definition*/
/*- Flip int in reverse */
/*- Return: return the number after the reverse */
int FlipInt(int n)
{
   
   int reverse = 0, remainder = 0, sign = 1;
   if( n < 0)
   {
       sign  = -1 * sign;
       n = -n;
   }   
   
   if (n > 2147483647 )
   {
        puts("The numbrer is larger than INT_MAX ");
        exit(EXIT_FAILURE);
   }
   
   if (n <= -2147483648)
   {
        puts("The numbrer is smaller than INT_MIN ");
        exit(EXIT_FAILURE);
   }
   

   while (n != 0)
    {
      remainder = n % 10;
      reverse = reverse * 10 + remainder;
       n /= 10;
    }
    
    return (reverse * sign) ;
}

/*function declaration*/
void TestFlipInt();
/*function definition*/
/*- Test the FliInt function*/
/*- Return: return a massage according to correctness  */
void TestFlipInt()
{
    int result = 0;
    
    result = ((FlipInt(12340) == 4321) && (FlipInt(-1234) == -4321)
              && (FlipInt(-21470) == -7412)&&(FlipInt(-2147) == -7412));
    
    if (result == 1)
    {
       puts("'FlipInt()' Function works great");
    }
	else
	{
	   puts("'FlipInt()' Function failed");
    }
}




int main()
{

    TestFlipInt();

    return 0;
}
