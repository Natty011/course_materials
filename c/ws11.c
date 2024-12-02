/***************************************
* Author : Natty
* Reviewer : Natan
* Date : 01 / 12 / 2024
* Last update: 01 / 12 / 2024
*****************************************/

#include <stdio.h> /* puts */
#include <stdlib.h> /* size_t, atoi */
#include <string.h> 
#include <ctype.h> /* tolower, isalpha */
#include <stdint.h> /*uint64_t, uint16_t */

#define ASCI_NUM 129

#define CHECKENDIAN ( (uint8_t)(0x1234) == 52 )


/***************************function declaration**************************/



char* ItoaUpTo36Base(int n, char* str, int base);
char* Itoa10Base(int num, char* str);
void ReverseStr(char* str);
static void TestItoaUpTo36Base(void);

int Atoi10Base(const char *nptr);
const char* WhiteSpacesSkip(const char *nptr);
static void TestAtoiUpTo36Base(void);
int AtoiUpTo36Base(const char *str, int base);

void PrintOnly2ArrayChar(char* s1, char* s2, char* s3,\
                          size_t len1, size_t len2, size_t len3);
static void FillLatterInHist(char* s, int* hist, size_t len);
static void TestPrintOnly2ArrayChar(void);
void CheckEndian(void);
static void TestCheckEndian(void);
/***************************End of function declaration******************/

int main ()
{

  puts("=====================================================");
  puts("'TestItoaUpTo36Base()'");
  TestItoaUpTo36Base();
  puts("=====================================================");
  
  puts("'TestAtoiUpTo36Base()'");
  TestAtoiUpTo36Base();
  puts("=====================================================");
  
  puts("'TestPrintOnly2ArrayChar()'");
  TestPrintOnly2ArrayChar();
  puts("=====================================================");

  puts("'CheckEndian()'");
  CheckEndian();
  puts("=====================================================");
      
  puts("'TestCheckEndianMacro()'");
  TestCheckEndian();
  puts("=====================================================");
  
return 0;
}

static void TestItoaUpTo36Base(void)
{
	char str[100] = { 0 };
    printf("Number: %d\nBase: %d\tConverted String: %s\n",
          -1750, 10, Itoa10Base(-1750, str));
          
    printf("Base: %d\t\tConverted String: %s\n", 2,
           ItoaUpTo36Base(-1750, str, 2));
           
    printf("Base: %d\t\tConverted String: %s\n", 8,
           ItoaUpTo36Base(-1750, str, 8));
           
    printf("Base: %d\tConverted String: %s\n", 16,
           ItoaUpTo36Base(-1750, str, 16));
           

}

/****************** ItoaUpTo36Base function definition *******************/
/* 
   DESCRIPTION: Converts an integer value to a null-terminated string
                using the specified base and stores the result in the
                array given by str parameter.

   RETURN VALUE: A pointer to the resulting null-terminated string,
                  same as parameter str.
                  
    NOTE: 1) If base is 10 and value is negative, the resulting string is
            preceded with a minus sign (-). With any other base,
            value is always considered unsigned.   
         
          2) Numerical base used to represent the value as a string,
             between 2 and 36, where 10 means decimal base,
             16 hexadecimal, 8 octal, and 2 binary.

*/
char* ItoaUpTo36Base(int n, char* str, int base)
{
	int i = 0;
	int remainder = 0;
	
	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (  (base > 36) || (base < 2) )
	{
	   puts("Invalid base value");
	   return str;
	}
	if( n <= 0 )
	{
		if ( n == 0)
		{
			str[i++] = '0';
			str[i] = '\0';
			return str; 
		}
		else if ((n < 0) && ( base == 10) )
		{
			return Itoa10Base( n, str);
		}
		
		else
		{
			n = -n;
		}
	}
	/* The base isn't 10 */
	while( n )
	{
		remainder = n % base;
		str[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		n = n / base;
	}
	
	str[i] = '\0'; 
	ReverseStr(str);
	return str;	
}
/********************* Itoa10Base function definition *********************/
/* 
   DESCRIPTION: Converts an integer value of base 10 to a null-terminated 
                string and stores the result in the array
                given by str parameter.
                 
   RETURN VALUE: A pointer to the resulting null-terminated string,
                  same as parameter str.
  
*/
char* Itoa10Base(int n, char* str)
{
	int i = 0;
	int sign = 1;
	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	if( n <= 0 )
	{
		if ( n == 0)
		{
			str[i++] = '0';
			str[i] = '\0';
			return str; 
		}
		else
		{
			n = -n;
			sign = -1;
		}
	}
	
	while( n )
	{
		str[i++] = n % 10 + '0';
		n = n / 10;
	}
	
	if(sign == -1 )
	{
		str[i++] = '-';
	}
	str[i] = '\0'; 

	ReverseStr(str);

	return str;
}

/* An auxilary function to reverse a string*/
void ReverseStr(char* str)
{

	char temp = 0;
	int low = 0;
	int high = strlen(str) - 1 ;

	while( low < high )
	{
		temp = str[low];
		str[low] = str[high];
		str[high] = temp;
		low++;
		high--;
	}
	
}

/********************* Atoi function definition *********************/
/* 

   DESCRIPTION: The  Atoi() function  converts the initial portion
                 of the string pointed to by nptr to int.
                 
   RETURN VALUE: The converted value or 0 on error.
 
   NOTE: 1) errno  is  not set on error so there is no way to distinguish
            between 0 as an error and as the converted value. 
         2) No checks for overflow or underflow are done.
            Only base-10 input can be converted.
*/

int Atoi10Base(const char *nptr)
{
	int num = 0;
	int sign = 1;
	
	nptr = WhiteSpacesSkip(nptr);
	if( *nptr == '-')
	{
		sign = -1;
		++nptr;
	}

	while( ('0' <= *nptr ) && ( *nptr <='9' ))
	{
		num = num*10 + *nptr - '0';
		++nptr;
	}

	return ( sign * num );

}

const char* WhiteSpacesSkip(const char *nptr)
{
	while(( *nptr == 32) || ((*nptr >= 9) && (*nptr <=13 )))
	{
		++nptr;
	} 
	return nptr;
}

static void TestAtoiUpTo36Base(void)
{
	char* str = "   -98105   "; 
    char* str1 = "   ff2   "; 
    char* str2 = "12"; 
    char* str3 = " 10010110";
    printf(" str = -98105 , str1 =ff2, str2 = 12, str3 = 10010110 \n ");
	printf(" Atoi10Base( str) = %d \n ", Atoi10Base(str));
	printf(" AtoiUpTo36Base( str1, 16)  = %d \n ",  AtoiUpTo36Base( str1, 16) );
	printf(" AtoiUpTo36Base( str, 10)  = %d \n ",  AtoiUpTo36Base( str, 10) );
	printf(" AtoiUpTo36Base( str2, 10)  = %d \n ",  AtoiUpTo36Base( str2, 8) );
	printf(" AtoiUpTo36Base( str3, 2)  = %d \n ",  AtoiUpTo36Base( str3, 2) );
	return;
}
/****************** AtoiUpTo36Base function definition *******************/
/* 
   DESCRIPTION: The AtoiUpTo36Base() function converts the initial 
                part of the string in str to an integer value
                 according to the given base, which must be between
                 2 and 36 inclusive.
       
   RETURN VALUE:  The  AtoiUpTo36Base() function returns the result
                  of the conversion in decimal integer, unless the
                  value would underflow or overflow. 
        
    NOTE: 1) If base is 10 and value is negative, the resulting string is
            preceded with a minus sign (-). With any other base,
            value is always considered unsigned.   
          2) errno  is  not set on error so there is no way to distinguish
             between 0 as an error and as the converted value. 
             
          3) No checks for overflow or underflow are done.
   
*/

int AtoiUpTo36Base(const char *str, int base)
{
	int dig = 0;
	int num = 0;
	if(NULL == str )
	{
		puts("str is a null pointer");
		exit(EXIT_FAILURE);
	}
	if (  (base > 36) || (base < 2) )
	{
	   puts("Invalid base value");
	   return 0;
	}
	str = WhiteSpacesSkip(str);
	if ( ( base == 10) )
		{
			return Atoi10Base( str );
		}
		
	while( (('0' <= *str ) && ( *str <='9' ) )||
	       (('a' <= *str ) && ( *str <='z' ) ) ||
	       (('A' <= *str ) && ( *str <='Z' )  ) )
	{      
		dig = ( *str > '9' ) ? tolower(*str) - 'a' +10 : *str - '0'; 
		num = num*base + dig ;
		++str;
	}
	
	return num;
}

/* TestPrintOnly2ArrayChar function */ 
static void TestPrintOnly2ArrayChar(void)
{
	char s1[] = "abBa63Tt&f@swWWW";
	char s2[] = "abbtBBBaT963&f@swWW";
	char s3[] = "aa963&f@sT";
	printf("s1 = %s, s2 = %s, s3 = %s", s1, s2, s3);
	PrintOnly2ArrayChar(s1, s2, s3, strlen(s1), strlen(s2), strlen(s3)  );
	return;

}
/**************** PrintOnly2ArrayChar function *************/
/* 
   DESCRIPTION: The PrOccOf2ArrOnly() function prints the occurance of 
                letters that apear only in array of s1 and s2 but not 
                in s3.

*/
void PrintOnly2ArrayChar(char* s1, char* s2, char* s3,\
                          size_t len1, size_t len2, size_t len3)
{
	int hist1[ASCI_NUM] = { 0 };
    int hist2[ASCI_NUM] = { 0 };
    int hist3[ASCI_NUM] = { 0 };
    int hist_to_print[ASCI_NUM] = { 0 };
    int i = 0;
    
    FillLatterInHist( s1, hist1, len1);
    FillLatterInHist( s2, hist2, len2);
    FillLatterInHist( s3, hist3, len3);

	for ( i = 65 ; i <= 122 ; ++i )
	{
		if( hist1[i] && hist2[i] && !hist3[i] )
		{
			hist_to_print[i] = (int)hist1[i];
		}
	
		
	}
	puts("\n-----------------------------------------------------------------");
	puts("The latters that both appear only in the 1st and 2nd array:");

	printf("{");
	for ( i = 65 ; i <= 122 ; ++i )
	{   if ( hist_to_print[i] )
	    {
			printf("%c ", hist_to_print[i]);

		}
	}
	puts("}");
	return;
}

/* An auxilary function that fill the histograma with
   the asci value of each later */

static void FillLatterInHist(char* s, int* hist, size_t len)
{
	size_t i = 0;
	
    while( i < len )
    {
    	if( isalpha( s[i] ) )
    	{
    		hist[(int)s[i]] = s[i];
    		++i;
    	}

    	else
    	{
    		++i;
    	}
    }
    return;
}

/* CheckEndian Function */
    /* Print the results as if it arrange in 
      the different and widest variable in the union */
void CheckEndian(void)
{
union
{
      	uint64_t u64;
        uint16_t arr[4];
} x;

/*  this is a little endian  */
	x.arr[0] = 0x1122;     /* Lowest-address byte */
    x.arr[1] = 0x3344;
    x.arr[2] = 0x5566;
    x.arr[3] = 0x7788;     /* Highest-address byte */

    if( (uint8_t)x.u64 == 0x22 )
    {
    	puts("It's a little Endian");
    }
    
    else if( (uint8_t)x.u64 == 0x88 )
    {
        puts("It's a Big Endian");
    }
     
    printf("x.u64 = %#lx\n", x.u64);       
    printf("x.arr[0] = %#x\n", x.arr[0]);
    printf("(uint8_t)x.u64 = %#x\n", (uint8_t)x.u64); 
    
    return;
}
/***** Test Macro CHECKENDIAN ****/

static void TestCheckEndian(void)
{
	if (CHECKENDIAN == 1)
	{
	    puts("It's a little Endian");
	}
	
	else
	{
	    puts("It's a Big Endian");
	}
	return;
}




