#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


/*function declaration*/
char* PrintHello();
/*function definition*/
/*- Converting hexa caracther to char and prints them */
/*- Return: allocation of a char pointer to "Hello World" string */
char* PrintHello()
{
    int i =0;
    char hello_hex[15] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20,
	                 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22, 0x00};
    char* strings;
    assert(!strings);
    strings = malloc(15*sizeof(char));
    if(strings == NULL)
      {
	   puts("Failed to allocate memory");
           exit(EXIT_FAILURE);
      }
	
    for (i =0; i < 15; ++i)
      {
           strings[i] = hello_hex[i];
      }
	
   puts(hello_hex);
   return strings;
}


/*function declaration*/
void TestPrintHello();
/*function definition*/
/*Check PrintHello function using return pointer*/
/*of PrintHello function, and compars it to an expected string */
void TestPrintHello()
{
    int result = 0;
    char* p1;
    char *str2= {"\"Hello World!\""};
    assert(!p1);
    p1 =PrintHello();
    result = strcmp(p1, str2);
    if (result == 0)
    {
	puts("'PrintHello()' Function works great");
    }
    else
    {
	puts("'PrintHello()' Function failed");
    }
    free(p1);
    p1 = NULL;
    return;
}

/*  PowTen */
/*function declaration*/
double PowTen(int power);

/*function definition*/
/*Compute 10^power and return the result */
double PowTen(int power)
{
    int index = 1;
    double ten = 10.0;
    double result = 1.0;

    if (power <= 0)
    {
        if(power == 0)
        {
	      printf("%f\n", result);
	      return result;

        }
            
        ten = 1.0/ten;
        power= -power;
    }
    
    result = ten;
    for ( ;index < power; index++)
    {
        result = result * ten;
    }
    printf("%f\n", result);
    
    return result;
}

/*function declaration*/
void TestPowTen();

/*function definition*/
/*Test the PowTen function the massage according to correctntess */

void TestPowTen()
{
    
    int result = 0;
    result = ((pow(10,-1) == PowTen(-1)) && (pow(10,0) == PowTen(0))
              && (pow(10,1) == PowTen(1))&&(pow(10,20) == PowTen(20)));

    if (result == 1)
    {
       puts("'PowTeno()' Function works great");
    }
    else
    {
	   puts("'PowTen()' Function failed");
    }
	        
             
        
}

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
 	puts("'TestPrintHello()'");
    	TestPrintHello();
    	puts("'TestPowTen()'");
	TestPowTen();
	puts("'TestFlipInt()'");
	TestFlipInt();
	return 0;
}

