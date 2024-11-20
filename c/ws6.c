/***************************************
* Autor : Natty
* Reviewr : Hadar
* Date : 17 / 11 / 2024
* Last update: 20 / 11 / 2024
*****************************************/
#include <stdio.h> /* printf, puts */
#include <math.h>  /* pow. Compile with -lm flag-> gd -g ws6.c -lm -o ws6 */
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert */

/*************** typedef and structure declaration *************************/

/***************End of typedef and structure declaration ******************/

/***************************function declaration**************************/

long Pow2(unsigned int x, unsigned int y);
static void TestPow2(void);

int CheckPowerOf2(unsigned int n);
int CheckPowerOf2Loop(unsigned int n);
static void TestCheckPowerOf2(void);

int Add1(int n);
static void TestAdd1(void);

unsigned int CheckIf3BitSet( unsigned int number);
void Count3Bit(unsigned int *arr, size_t arr_length);
static void TestCount3Bit(void);

unsigned char ByteMirrorLoop( unsigned char number );
unsigned char ByteMirrorLut( unsigned char number );
static void TestByteMirror(void);

int Bits2AND6On(unsigned char number);
static void TestBits2AND6On(void);

int Bits2OR6On(unsigned char number);
static void TestBits2OR6On(void);

unsigned char Bits3rd5thSwap(unsigned char number);
static void TestBits3rd5thSwap(void);

unsigned int NumDivBy16WoRem(unsigned int number);
static void TestNumDivBy16WoRem(void);

void SwapWOTempVar ( int* x, int* y);
static void TestSwapWOTempVar(void);

int CountBitLoop(int n);
int CountBitLut(int n);
static void TestCountBit(void);

int CountFloatBits(float input);
int CountBitChar(char n);
static void TestCountFloatBits(void);

/********************End of function declaration**************************/

int main (void)
{
  
  puts("=====================================================");
  puts("'TestPow2()'");
  TestPow2();
  puts("=====================================================");
  
  puts("'TestCheckPowerOf2()'");
  TestCheckPowerOf2();
  puts("=====================================================");
  
  puts("'TestAdd1()'");
  TestAdd1();
  puts("=====================================================");
  
  puts("'TestCount3Bit()'");
  TestCount3Bit();
  puts("=====================================================");
  
  puts("'TestByteMirror()'");
  TestByteMirror();
  puts("=====================================================");
  
  puts("'TestBits2AND6On()'");
  TestBits2AND6On();
  puts("=====================================================");
  
  puts("'TestBits2OR6On()'");
  TestBits2OR6On();
  puts("=====================================================");
  
  puts("'TestBits3rd5thSwap()'");
  TestBits3rd5thSwap();
  puts("=====================================================");
  
  puts("'TestNumDivBy16WoRem()'");
  TestNumDivBy16WoRem();
  puts("=====================================================");
  
  puts("'TestSwapWOTempVar()'");
  TestSwapWOTempVar();
  puts("=====================================================");
  
  puts("'TestCountBit()'");
  TestCountBit();
  puts("=====================================================");
  
  puts("'TestCountFloatBits()'");
  TestCountFloatBits();
  puts("=====================================================");
  
  return 0;
}

/*********Pow2 function: 1st qeustion ********/

long Pow2(unsigned int x, unsigned int y)
{
    long result = 1;
    
    
      result = result << y;       
    
    return (x * result);
}

/*********TestPow2 function: 1st qeustion ********/

static void TestPow2(void)
{
   unsigned int i = 0;
  
   for ( i = 0; i < 6 ; ++i)
   {
         printf(" 2*(2^%u) = x*(2^y) = %ld \n" , i, Pow2(2, i));
         if( (long)(2*pow(2, i)) != Pow2(2, i) )
        {
            puts("Pow2() Function failed");
            return;
        }
   }
   puts("Pow2() Function work great");  
   return;       
}


/*********CheckPowerOf2 function: 2st qeustion w/o loop ********/
int CheckPowerOf2(unsigned int n)
{
    /* if a number is a power of 2 then the MSB is 1,
        and the others bits are zeros. so one less is a number with on's
         except the MSB whitch is zero. so the result of the multiplication 
         is zero number */
    if ( n == 0) return 0;
    return(n & (n -1)) == 0 ;
 
}

/*********CheckPowerOf2 function: 2st qeustion with loop ********/
int CheckPowerOf2Loop(unsigned int n)
{

    if ( n == 0) return 0; 
    while ( ( n % 2 ) == 0 )
    {
         n = n >> 1; /* Divide by 2 an unsigned integer number  */
    }
     
   /* If a number is an even and has 2 divisors (itself and 1) only, then 
       the number is a power of 2  */ 
   return n == 1; 
}

/*********TestCheckPowerOf2 function: 2st qeustion ********/
/* Test with & w/o loop */
  
static void TestCheckPowerOf2(void)
{
   unsigned int i = 0;
   int result = 0;
    /*n is Power of 2 */
   result = CheckPowerOf2(Pow2(1, i)) == CheckPowerOf2Loop(Pow2(1, i));
   printf(" for n = %ld the result is %d \n" ,  Pow2(1, i), result);
    /*n is not Power of 2 */
   result = CheckPowerOf2(3) == CheckPowerOf2Loop(3);
   printf(" for n = 3 the result is %d \n" , !result);

   for ( i = 0; i < 6 ; ++i)
   { 
      puts("********************************");  
     /*  n is Power of 2 */
      result = CheckPowerOf2(Pow2(2, i)) == CheckPowerOf2Loop(Pow2(2, i));
      printf(" for n = %ld the result is %d \n" ,  Pow2(2, i), result); 
      
      /*n is not Power of 2 */
      result = CheckPowerOf2(Pow2(6, i)) == CheckPowerOf2Loop(Pow2(6, i));
      printf(" for n = %ld the result is %d \n" ,  Pow2(6, i), !result); 
        if( !result )
        {
            puts("CheckPowerOf2() / CheckPowerOf2Loop() Function failed");
            return;
        }
   }
   puts("CheckPowerOf2() & CheckPowerOf2Loop() Functions work great");
}


/*********Add1 functiom: 3st qeustion ********/ 
/* Check if n is an odd or even number, if an even then add the carry
    to the lsb. if n is an odd ( lsb is '1'), there will be a reminder if we'll
    add it to the lsb. so the reminder/carry will be add to the first '0' that 
    we get from the rightmost of the number n */ 

int Add1(int n)
{
   /* Add this carry adder to the n,
       both of them may change if we'll get into the loop
       */
    int CarryAdder = 1; /* 0x 00 00 00 01 */
   
    /* Don't enter to loop if the first rightmost of n is '0' bit */
    while ( n & CarryAdder)  /* Check if n is an even or odd */
    {
        n = n ^ CarryAdder; /* reset the rightmost bits of n from '1' to '0' */
        
        /* multiple by 2, to check the state of the next bit of n */
        CarryAdder = CarryAdder << 1; 
    }
    
    /* Add the carry to the first rightmost of n that is '0' bit*/
    n = n ^ CarryAdder; 

    return n;
}

/*********TestAdd1 function: 3rd qeustion ********/ 
static void TestAdd1(void)
{
    int i = 0;
    for ( i = -3; i < 4 ; ++i)
    { 
        printf(" for n = %d the result is %d \n" ,  i, Add1(i));
         if( (i + 1) != Add1(i))
        {
            puts("Add1() Function failed");
            return;
        }
   }
   puts("Add1() Function work great");  
   return;
    
}

/***CheckIf3BitSet function: An auxilery function for the 4th qeustion**/ 
/* Counts the '1' of an unsigned int number,
   return 1 if the number has 3 bits that are '1' ON, otherwise retrun 0 */

unsigned int CheckIf3BitSet( unsigned int number)
{
    unsigned int count = 0;
    unsigned int bit = 1; /* 0x 00 00 00 01 */
    
    for ( bit = bit << 31; bit > 0; bit = bit >> 1 )
    {
        count += ((number & bit) != 0);
        if (count > 3)
        {
            return 0;
        }
    }
    
    return (count == 3); /* count can be less than 3 */ 
}

/*********Count3Bit function: 4th qeustion ********/ 
/* Prints the numbers in the array that have exactly  3 bits of '1' ON */
void Count3Bit(unsigned int *arr, size_t arr_length)
{
    size_t i = 0;
    
    for ( i = 0; i < arr_length ; ++i )
    {
        if ( CheckIf3BitSet( arr[i] ) )
        {
            printf("The number = %u has excatly 3 bits ON('1')\n", arr[i]);
        }
    }
    return;
}

/*********TestCount3Bit function: 4th qeustion ********/ 
static void TestCount3Bit(void)
{
    unsigned int arr1[] = { 0, 1, 2, 3, 4, 5, 6, 7};
    unsigned int arr2[] = { 8, 9, 10, 11, 12, 13, 14, 15};
    
    printf(" For the array: { 0, 1, 2, 3, 4, 5, 6, 7}\n");
    Count3Bit(arr1, 8);
    
    printf(" For the array: { 8, 9, 10, 11, 12, 13, 14, 15}\n");
    Count3Bit(arr2, 8);
    
    return;       
}

/*********ByteMirrorLoop function: 5th qeustion with loop ********/ 

unsigned char ByteMirrorLoop( unsigned char number )
{
    int i = 0;
    unsigned char result = 0;
    unsigned char carry = 1;
 /*Saving the state of each number's bit and push the result to left*/   
    for ( i = 0; i < 8; ++i)
    {
     result = result << 1; /* left shift */
     result = result | (number & carry);
     number = number >> 1; /* right shift */
    } 
    return result;
    
}

/*********ByteMirrorLoop function: 5th qeustion w/o loop ********/ 
/* Using LUT to reverse/mirror nibble */
/* Example: number = 7 -> Binary = 0111 -> Reverse: 1110 -> HEXA: 0xE */ 
/* The Table includes representation of reverse/mirror numbers in hexadecimal */

unsigned char ByteMirrorLut( unsigned char number )
{
    unsigned char result = 0;
    /* Shifting the nibbles to get each nibble separately */

    unsigned char REVERSE_NUMBER_TABLE[16] = 
    {
        0x0, 0x8, 0x4, 0xC, /* [0...3]*/
        0x2, 0xA, 0x6, 0xE, /* [4...7]*/
        0x1, 0x9, 0x5, 0xD, /* [8...11]*/
        0x3, 0xB, 0x7, 0xF, /* [12...15]*/
    };

   unsigned char LsbNibble = number << 4; 
   unsigned char MsbNibble = number >> 4;

    /* Sum the 2 nibbles after the reversinng*/
    result = (REVERSE_NUMBER_TABLE[(((LsbNibble) & 0xF0)>>4) & 0xF]<<4) |
              REVERSE_NUMBER_TABLE[(MsbNibble) & 0xF];
    return result;
}
/*********TestByteMirror function: 5th qeustion w & w/o loop ********/
/* Test & Compare the results of the 2 implementation functions:
   ByteMirrorLoop & ByteMirrorLut */ 

static void TestByteMirror(void)
{
    unsigned char arr[] = {255, 128, 1, 0, 2, 64, 10, 80};
    unsigned int len_arr = 8;
    unsigned int i = 0;
    for ( i = 0; i < len_arr ; ++i)
    {
    puts("********************************");
    printf(" the ByteMirrorLoop(%d) is %d\n",arr[i], ByteMirrorLoop(arr[i]));
    printf(" the ByteMirrorLut(%d) is %d\n",arr[i], ByteMirrorLut(arr[i]));
    if( ByteMirrorLoop(arr[i]) !=  ByteMirrorLut(arr[i]))
        {
         printf("ByteMirrorLoop(%u) / ByteMirrorLut(%u) failed",arr[i], arr[i]);
         return;
        }
    }
   puts("the ByteMirrorLoop() & ByteMirrorLut() Functions work great");
   return;
}

/*********Bits2AND6On function: 6th qeustion, section 1 ********/ 

int Bits2AND6On(unsigned char number)
{
   /* Saving 6th bit state-> Index 6 */
   unsigned char MsbNibble6Bit = number & 0x40;
   /* Saving 2nd bit state-> Index 2*/ 
   unsigned char LsbNibble2Bit = number  & 0x04; 

   return (MsbNibble6Bit + LsbNibble2Bit) == 68 ; 
   
}

/*********TestBits2AND6On function: 6th qeustion, section 1 ********/ 
static void TestBits2AND6On(void)
{
    unsigned char arr[] = {4, 64, 68, 0, 36,0x33, 255,
                           254, 127, 0xBB, 0xBF, 0XFB};
    unsigned int i = 0;
    for ( i = 0; i < 12 ; ++i)
    {
      
      if(Bits2AND6On(arr[i]))
      {
          puts("**********************************************************");
          printf(" The 2nd & 6th bits of %u are sets to '1'\n", arr[i]);
          continue; 

      }
   printf("At least One of the 2nd or 6th bit of %u are sets to '0'\n", arr[i]); 
    }
    return;
}

/*********Bits2OR6On function: 6th qeustion, section 2 ********/ 
/* Check if at least 1 bit of a number is on in the 2nd or 6th place */

int Bits2OR6On(unsigned char number)
{
   /* Saving 6th bit state-> Index 6 */
   unsigned char MsbNibble6Bit = number & 0x40;
   /* Saving 2nd bit state-> Index 2*/ 
   unsigned char LsbNibble2Bit = number  & 0x04; 

   return (MsbNibble6Bit ^ LsbNibble2Bit) ; 
   
}

/*********TestBits2OR6On function: 6th qeustion, section 2 ********/ 
static void TestBits2OR6On(void)
{
    unsigned char arr[] = {4, 64, 68, 0, 0x0B, 36,0x33, 255,
                           254, 127, 0xBB, 0xBF, 0XFB};
    unsigned int i = 0;
    for ( i = 0; i < 13 ; ++i)
    {
      
      if(Bits2OR6On(arr[i]))
      {
          printf("At least One of the 2nd or 6th bit of %u are '1'\n", arr[i]); 
          continue; 

      }
    puts("**********************************************************");  
    printf("Both 2nd or 6th bit of %u are sets to '0'\n", arr[i]); 
    puts("**********************************************************");  
    }
    return;
}

/*********Bits3rd5thSwap function: 6th qeustion, section 3 ********/
/* Swap 3rd & 5th bits of a number */
/* The idea is to use the expression XOR( XOR(X,Y),X) == Y and vise versa*/
 
unsigned char Bits3rd5thSwap(unsigned char number)
{
    
    unsigned char bit3rd = number & 0x08; /*  Save 3rd bit only */
    unsigned char bit5th = number & 0x20; /*  Save 5th bit only */
    unsigned char bit35 = bit5th | bit3rd; /* Save both */
    
    /*Shifting the posotions of th 3rd->5th and 5th->3rd bits and adding each*/
    unsigned char bitshift35pos = (bit5th >> 2) | (bit3rd << 2); 
    
    /* XOR(3rd,5th) at each position:a.k.a 3rd and 5th */
    unsigned char bitXor35 = bit35 ^ bitshift35pos; 
    
    /* Now use the expression in the description of the function */
    number = number ^ bitXor35; 
    return number;
}

/*********TestBits3rd5thSwap function: 6th qeustion, section 3 ********/ 
static void TestBits3rd5thSwap(void)
{
    unsigned char arr[] = {0, 0x28, 0x01, 0x20, 0x08, 0xFF, 0x24, 0x18};
    unsigned int num = 0;                 
    unsigned int i = 0;
    for ( i = 0; i < 8 ; ++i)
    {
      num = Bits3rd5thSwap(arr[i]);
      printf("The 3rd & 5th bit swaped of %u result in %u\n", arr[i],num ); 
      puts("**********************************************************");  
    }
    
    return; 
}

/********* NumDivBy16WoRem function: 7th qeustion ********/ 
/* Return the closest smaller number of the input that divide by 0x10==16
    wo a remainder */
    
unsigned int NumDivBy16WoRem(unsigned int number)
{
    
    if ( !number ) return 0; /* zero divide by 0x10 w/o remainder */ 
    while( number > 0xF)
    {
    /* It is like modulo 0x10 =16, and in bitewise is number&(divider-1)*/
        if(!(number & (0xF))) /* If there is not a reminder */
        {
            return number;
        }
        
        number = ~number + (number<<1); /* Decrement the number by 1 */
    
    }
    /* the number is in range [1...15] -> divider of 0x10 with reminder*/
    return 1; 
}

/********* TestNumDivBy16WoRem function: 7th qeustion ********/ 

static void TestNumDivBy16WoRem(void)
{
    unsigned int arr[] = {0, 1, 2, 4, 8, 0xF, 0x10, 0x11, 0x016,
                          0x0101, 0x0111, 0xCD, 0xFFFF};
    
    unsigned int n = 0;                  
    unsigned int i = 0;
    for ( i = 0; i < 13 ; ++i)
    {
      n = NumDivBy16WoRem( arr[i] );
      if ( n != 1 )
     { 
       printf("The small closest of %u which is divided by 16 is %u\n",arr[i],n); 
       puts("**********************************************************");  
       continue;
     }
       
       printf("The number %u is less than the divisor\n", arr[i]); 
     }
     return;
}
/********* SwapWOTempVar function: 8th qeustion ********/ 
/* Swap 2 numbers using bitewise and without the Temporary variable */
/* The idea based on the following eqaution: XOR( XOR(X,Y),X) == Y */

void SwapWOTempVar( int* x, int* y)
{
    assert(x);
    assert(y);
    *x = *x ^ *y; /*  *p = xor(*x, *y) */
    *y = *x ^ *y; /*    *t = *x = xor(*p, *y) the original x assign to y  */
    
   /* *y = xor(*t, *p)  x is now in y, so we can using the first xor to 
      restore the *y and assign it to *x */
    *x = *x ^ *y; 
    return;
}
 
 /********* TestSwapWOTempVar function: 8th qeustion ********/ 
static void TestSwapWOTempVar(void)
{
  int a = 86, b = -51;
  int c = a, d = b;
  
   SwapWOTempVar(&a, &b);
   
   if ((c == b) && (d == a))
    {
       puts("'SwapWOTempVar()' Function works great");
    }
    else
	{
      puts("'SwapWOTempVar()' Function failed");
    }
}
 
/********* CountBitLoop function: 9th qeustion with loop ********/ 
 
int CountBitLoop(int n)
{
    int count = 0;
    while(n)
    {
     count += (( n & 0x80000000) == 0x80000000);
     n = n << 1;
    }
    return count;
}

/********* CountBitLut function: 9th qeustion with LUT ********/ 
/* Counting by multiplying each MSB niblle with the number */
int CountBitLut(int n)
{
    int LsbNibble = 0xF;
    int count = 0;
  
    /* Puting in each cell the number of bits in each niblle from 0x0->0xF*/
    int COUNT_BITS_TABLE[16] = 
    {
        0x0, 0x1, 0x1, 0x2, /* [0...3]*/
        0x1, 0x2, 0x2, 0x3, /* [4...7]*/
        0x1, 0x2, 0x2, 0x3, /* [8...11]*/
        0x2, 0x3, 0x3, 0x4, /* [12...15]*/
    };
    
    count += COUNT_BITS_TABLE[ (n & LsbNibble)]; /* 1 */
    count += COUNT_BITS_TABLE[ ((n>>4) & LsbNibble) ] ; /* 2 */
    count += COUNT_BITS_TABLE[ ((n>>8) & LsbNibble) ] ; /* 3 */
    count += COUNT_BITS_TABLE[ ((n>>12) & LsbNibble) ] ; /* 4 */
    count += COUNT_BITS_TABLE[ ((n>>16) & LsbNibble) ] ; /* 5 */
    count += COUNT_BITS_TABLE[ ((n>>20) & LsbNibble) ] ; /* 6 */
    count += COUNT_BITS_TABLE[ ((n>>24) & LsbNibble) ] ; /* 7 */
    count += COUNT_BITS_TABLE[ ((n>>28) & LsbNibble) ] ; /* 8 */
    
    return count;
}


 /********* TestCountBit function: 9th qeustion ********/ 
 /* Test the resultS of the 2 function of 9th qeustion 
    by comparing and printing their results */

static void TestCountBit(void)
{
    int arr[] = {-1, 0, 1, 2, 5, 13, 0xF, 0x10, 0x0FF0, 0xF00F,
                 0xF0, 0xFF, 0xFFF,0x80000000, 0xFFFFFFFE};
     int CntLoop = 0, CntLut = 0;            
                          
    int i = 0;
    for ( i = 0; i < 15 ; ++i)
    {   CntLoop = CountBitLoop(arr[i]);
        CntLut = CountBitLut(arr[i]);
        
        printf("Loop: The number %d has %d bits sets \n", arr[i], CntLoop); 
        printf("Lut: The number %d has %d bits sets \n", arr[i], CntLut); 
        puts("********************************************");  
    }
     return;
}
/***************** 10th qeustion  *********************************/ 

/********* CountCountBitChar function: 10th qeustion  ********/ 
/* An auxilary function to count byte of float type variable */

 
int CountBitChar(char n)
{
    char LsbNibble = 0xF;
    int count = 0;
  
    /* Puting in each cell the number of bits in each nibble from 0x0->0xF*/
    int COUNT_BITS_TABLE[16] = 
    {
        0x0, 0x1, 0x1, 0x2, /* [0...3]*/
        0x1, 0x2, 0x2, 0x3, /* [4...7]*/
        0x1, 0x2, 0x2, 0x3, /* [8...11]*/
        0x2, 0x3, 0x3, 0x4, /* [12...15]*/
    };
    
    count += COUNT_BITS_TABLE[ (n & LsbNibble)]; /* 1 */
    count += COUNT_BITS_TABLE[ ((n>>4) & LsbNibble) ] ; /* 2 */
    
    return count;
}
/********* CountFloatBits function: 10th qeustion  ********/ 
int CountFloatBits(float input)
{
    unsigned int i = 0;
    /* Store the bytes' number of a float */
    unsigned int n = sizeof(float)/sizeof(char);
    
    /* Typecast the address of the input to char pointer*/
    char* ptr = (char*)(&input); 
    
    int count = 0;

    
    for (i = 0 ; i < n; ++i)
    {
        count += CountBitChar(*ptr);
        ptr++;
    }
    return count;
}
    
    
 /********* TestCountFloatBits function: 10th qeustion ********/ 
 /* Test the resultS of function of 10th qeustion 
    by printing its results */

static void TestCountFloatBits(void)
{
    int Cnt = 0;
    int i = 0;
                
    float arr[] = {-0.0, 0.0, 0.15625, 1.0, -1.0, 1.25,
                    0.625, -0.625, 1.5, 1.125, -1.5};
                           
    for ( i = 0; i < 11 ; ++i)
    {  
        Cnt = CountFloatBits(arr[i]);
        printf("The number %f has %d bits sets \n", arr[i], Cnt); 
        puts("********************************************");  
    }
     return;
}
 





