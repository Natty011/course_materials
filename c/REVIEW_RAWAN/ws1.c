#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ws1.h"  /* Great!!*/

/*
Expain before the definition of each funtion the purpose of th function 
and the input parameters and the return values if they exist
*/

int main() /* Great!!*/
{
	HelloWorld();
	TestPow();
	test_flip_integer();
	TestSwap();
	return 0;
}

/* EX3 */
void HelloWorld()
{
    char hexa_array[]={0x22,0x48,0x65,0x6c,0x6c,0x6f,0x20,0x57,0x6f,0x72,0x6c,0x64,0x21,0x22};
	printf("%s\n",hexa_array);
}

/* ------------------------------------------------------------- */
/* EX4 */
double power_of_ten(int n) /* Great!!*/
{
   	int i;
   	double result=1;  /* Prefer explicit initialization to double such as 1.0 to avoid implicit casting*/
   	double x=10; /*comment as above --> 10.0 */
   	if (0 > n)
   	{
      	x= 1/x;
      	n=n*(-1);
   	}
   	for (i=0; i<n; i++)
   	{
      	result*=x;
   	}
   	return result;
}

/* Test power_of_ten */

int TestPow()  /* Great!!*/
{	
	int result=0;  
	if (fabs(pow(10,3) - power_of_ten(3))< 0.05)
	{
	printf("success for exponent=3\n");
	}
	else
	{
	printf("failure for exponent=3\n");
	result=1;
	}
	if(fabs(pow(10,0)-power_of_ten(0))<0.05)
	{
	printf("success for exponent=0\n");
	}
	else
	{
	printf("failed for exponent=0\n");
	result=1;
	}
	if(fabs(pow(10,-3)-power_of_ten(-3))<0.05)
	{
	printf("success for exponent=-3\n");
	}
	else
	{
	printf("failure for exponent=-3\n");
	result=1;
	}
	return result;
}


/*--------------------------------------------------------------- */
/* EX.5 */

int flip_integer(int num) /* Great!!*/
{
   	int flipped , remainder,sign; /* Can initialized in the same row of decleration*/
   	flipped=0;
   	sign=1;
   	if(num<0)
   	{
      	num= num*(-1);
      	sign=sign*(-1);
   	}
   	while(num > 0)
   	{
      	remainder=num%10;
      	flipped=flipped*10+remainder;
      	num/=10;
   	}
   	return flipped*(sign);
}

int test_flip_integer()
{
	int result=0;
	if(10545==flip_integer(54501))
	{
	printf("success for num=54541\n");
	}
	else
	{
	printf("failed for num =54541\n");
	result=1;
	}

	if(4321 == flip_integer(12340))
	{
	printf("success for num=12340\n");
	}
	else
	{
	printf("failed for num=12340\n");
	result=1;
	}
	if(321==flip_integer(12300))
	{
	printf("success for num=12300\n");
	}
	else
	{
	printf("failed for num=12300\n");
	result=1;
	}
	if(-531 == flip_integer(-135))
	{
	printf("success for num=-135\n");
	}
	else
	{
	printf("failed for num =-135\n");
	result=1;
	}
	return result;
}
 

/* -----------------------------------------------------------*/

/*Ex.6 */
void swap(int* a, int* b) /* Great!!*/
{
   	int temp;
   	temp= *a;
   	*a = *b;
   	*b=temp;
}

int TestSwap() /* Great!!*/
{
	int a,b;
	int result =0;
	a=1;
	b=3;
	swap(&a,&b);
	if (1==b && 3==a)
	{
	printf("success for a=1 and b=3\n");
	}
	else
	{
	printf("failed for a=1 and b=3\n");
	result=1;
	}
	a=-5;
	b=-20;
	swap(&a,&b);
	if(-5==b && -20==a)
	{
	printf("success for a= -5 and b= -20\n");
	}
	else
	{
	printf("failed for a= -5 and b= -20\\n");
	result=1;
	}
	a=0;
	b=8;
	swap(&a,&b);
	if(0==b && 8==a)
	{
	printf("success for a=0 and b=8\n");
	}
	else
	{
	printf("failed for a=0 and b=8\n");
	result=1;
	}
	return result;
}
/* ----------------------------------------------------------------------------------------------------------------------------- */


